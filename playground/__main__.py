import imgui
from imgui.integrations.glfw import GlfwRenderer
from datetime import datetime

from typing import TYPE_CHECKING
if TYPE_CHECKING:
    import pyimgui as imgui

import glfw
import OpenGL.GL as gl
import os, sys

from playground import backend
from playground.IconsFontAwesome6 import IconsFontAwesome6 as Icons
from playground.IconsFontAwesome6Brands import IconsFontAwesome6Brands as IconBrands

if sys.platform == 'darwin':
    DPI_SCALE = 2
    WINDOW_WIDTH, WINDOW_HEIGHT = 720+100, 400+100
else:
    DPI_SCALE = 1
    WINDOW_WIDTH, WINDOW_HEIGHT = 1440, 800

def get_file_time(path):
    if not os.path.exists(path):
        return None
    t = os.path.getmtime(path)
    t = datetime.fromtimestamp(t).strftime("%Y-%m-%d %H:%M:%S")
    return t

class ProjectView:
    def __init__(self):
        self.task = None
        glyph_ranges = imgui.get_io().fonts.get_glyph_ranges_chinese()

        self.default_font = self.load_font(24, glyph_ranges, with_source_code_pro=False)
        self.source_font = self.load_font(24, glyph_ranges, with_source_code_pro=True)

        imgui.get_io().delta_time = 1 / 30
        
        self.root = None

        self._selected_file = None
        self._selected_content = None

        if len(sys.argv) > 1:
            ok = self.open_project(sys.argv[-1])
        else:
            ok = False
        if not ok:
            self.open_project(backend.config.project)

        # start threading task
        self.threading_task = backend.ThreadingTask()
    
    def load_font(self, size, glyph_ranges, with_source_code_pro=True):
        if with_source_code_pro:
            imgui.get_io().fonts.add_font_from_file_ttf(
                "template/carrotlib/assets/SourceCodePro-Medium.otf",
                size,
                glyph_ranges=glyph_ranges
            )
            next_font_config = imgui.FontConfig(merge_mode=True)
        else:
            next_font_config = None

        if sys.platform == 'win32':
            SYSTEM_FONT_PATH = "C:\\Windows\\Fonts\\msyh.ttc"
        elif sys.platform == 'darwin':
            SYSTEM_FONT_PATH = "/System/Library/Fonts/STHeiti Light.ttc"
        else:
            raise NotImplementedError
        
        sys_font = imgui.get_io().fonts.add_font_from_file_ttf(
            SYSTEM_FONT_PATH,
            size,
            font_config=next_font_config,
            glyph_ranges=glyph_ranges
        )

        if with_source_code_pro:
            return sys_font

        icon_min, icon_max = Icons.ICON_MIN, Icons.ICON_MAX
        imgui.get_io().fonts.add_font_from_file_ttf(
            f"playground/assets/fonts/{Icons.FONT_ICON_FILE_NAME_FAR}",
            size,
            font_config=imgui.FontConfig(merge_mode=True),
            glyph_ranges=imgui.core.GlyphRanges([icon_min, icon_max, 0])
        )
        icon_min, icon_max = IconBrands.ICON_MIN, IconBrands.ICON_MAX
        return imgui.get_io().fonts.add_font_from_file_ttf(
            f"playground/assets/fonts/{IconBrands.FONT_ICON_FILE_NAME_FAB}",
            size,
            font_config=imgui.FontConfig(merge_mode=True),
            glyph_ranges=imgui.core.GlyphRanges([icon_min, icon_max, 0])
        )

    def poll_task(self):
        if self.task is not None:
            try:
                next(self.task)
            except StopIteration:
                self.task = None

    def start_task(self, task):
        if task is None:
            return
        if self.task is not None:
            print("[WARNING]", "Another task is running, please wait...")
            return
        self.task = task

    @property
    def selected_file(self):
        return self._selected_file
    
    @property
    def selected_content(self):
        return self._selected_content
    
    @selected_file.setter
    def selected_file(self, value: str):
        self._selected_file = value
        if value:
            try:
                with open(self.selected_file_abspath, "rt", encoding='utf-8') as f:
                    # get file size
                    f.seek(0, os.SEEK_END)
                    filesize = f.tell()
                    f.seek(0)
                    if filesize > 500 * 1024:      # 500 KB
                        self._selected_content = None
                    else:
                        self._selected_content = f.read()
            except Exception as e:
                self._selected_content = None
        glfw.set_window_title(
            glfw.get_current_context(),
            f"CarrotLib🥕 Playground - {os.path.basename(self.root)} - {self.selected_file}"
        )

    def open_project(self, root: str):
        if not root or not os.path.exists(root):
            print("[ERROR]", f"Invalid project path: {root}")
            return False
        main_path = os.path.join(root, "main.py")
        if not os.path.exists(main_path):
            print("[ERROR]", f"Unable to find main.py in project: {root}")
            return False
        self.root = root
        self.selected_file = 'main.py'
        print("[INFO]", f"Open project: {root}")
        return True

    @property
    def root_abspath(self):
        if not self.root:
            return None
        return os.path.abspath(self.root)
    
    @property
    def selected_file_abspath(self):
        if not self.selected_file:
            return None
        return os.path.join(self.root_abspath, self.selected_file)
    
    def render_console(self):
        with imgui.font(self.source_font):
            input_bg_color = (44/255, 40/255, 52/255, 1.0)
            imgui.push_style_color(imgui.COLOR_FRAME_BACKGROUND, *input_bg_color)

            for line in backend.get_logs():
                if line.startswith("[ERROR]"):
                    color = (1.0, 0.5, 0.0, 1.0)
                elif line.startswith("[WARNING]"):
                    color = (1.0, 1.0, 0.0, 1.0)
                else:
                    color = (1.0, 1.0, 1.0, 1.0)

                imgui.push_style_color(imgui.COLOR_TEXT, *color)
                imgui.push_text_wrap_pos(0)
                imgui.text(line)
                imgui.pop_text_wrap_pos()
                imgui.pop_style_color()

            imgui.text("")
            
            if self.task is not None:
                imgui.set_scroll_here_y(1.0)
            imgui.pop_style_color()

    def render_file_hierarchy(self, root: str):
        # use recursive function to render file hierarchy
        flags = imgui.TREE_NODE_SPAN_AVAILABLE_WIDTH
        for item in os.listdir(root):
            item_path = os.path.join(root, item)
            if os.path.isdir(item_path):
                if imgui.tree_node(item, flags=flags):
                    self.render_file_hierarchy(item_path)
                    imgui.tree_pop()
            else:
                imgui.tree_node(item, flags=imgui.TREE_NODE_LEAF | imgui.TREE_NODE_NO_TREE_PUSH_ON_OPEN | flags)
                if imgui.is_item_clicked(0):
                    self.selected_file = os.path.relpath(item_path, self.root)

    def render_text_editor(self):
        input_bg_color = (44/255, 40/255, 52/255, 1.0)
        input_fg_color = (171/255, 178/255, 191/255, 1.0)
        imgui.push_style_color(imgui.COLOR_FRAME_BACKGROUND, *input_bg_color)
        imgui.push_style_color(imgui.COLOR_TEXT, *input_fg_color)
        if self.selected_file:
            flags = imgui.INPUT_TEXT_READ_ONLY
            if self.selected_content is None:
                buffer = "[Unsupported File]"
            else:
                buffer = self.selected_content
            width, height = imgui.get_window_size()
            with imgui.font(self.source_font):
                buffer = imgui.input_text_multiline(
                    "##source",
                    buffer,
                    width=width,
                    height=height,
                    flags=flags
                )
        imgui.pop_style_color(count=2)

    def render(self):
        # -------------------------- #
        window_width, window_height = imgui.get_window_size()
        window_height *= 0.96
        window_width *= 0.96

        # two column with splitter, drag to resize width
        imgui.begin_child("L", width=window_width * 0.25, height=window_height)

        full_width = imgui.get_window_width()
        if imgui.button(f"{Icons.ICON_FOLDER} New Project", width=full_width):
            if not os.path.exists("projects"):
                os.mkdir("projects")
            path = backend.open_directory("Select an Empty Directory", "projects")
            if path:
                if len(os.listdir(path)) != 0:
                    print("[ERROR]", "The directory is not empty.")
                else:
                    backend.new_project(path)
                    self.open_project(path)
        if imgui.button(f"{Icons.ICON_FOLDER_OPEN} Open Project", width=full_width):
            path = backend.open_directory("Select a Directory", "examples")
            if path:
                self.open_project(path)
        imgui.spacing()

        if self.root:
            with imgui.font(self.source_font):
                self.render_file_hierarchy(self.root)

        imgui.end_child()

        ######################################################################################
        imgui.same_line()

        imgui.begin_child("R", width=window_width * 0.75, height=window_height, border=True)

        imgui.begin_tab_bar("TabBar")

        with imgui.begin_tab_item("   Control Panel   ") as tab:
            if tab.selected:
                framework_compile_time = get_file_time(backend.FRAMEWORK_EXE_PATH)
                imgui.text(f"Framework compiled at: {framework_compile_time}")
                imgui.text(f"Project: {self.root}")
                imgui.text(f"Selected: {self.selected_file}")

                imgui.spacing()

                changed, use_precompile = imgui.checkbox("Enable Precompile", backend.config.use_precompile)
                if changed:
                    backend.config.use_precompile = use_precompile
                imgui.same_line(spacing=16)
                changed, use_playground_console = imgui.checkbox("Enable Console", backend.config.use_playground_console)
                if changed:
                    backend.config.use_playground_console = use_playground_console
                    print("[INFO]", "Restart the playground to take effect.")

                imgui.spacing()

                imgui.separator()
                imgui.text(f"Connected Devices：{len(self.threading_task.devices)}")
                for device in self.threading_task.devices:
                    imgui.spacing()
                    if isinstance(device, backend.IOSDevice):
                        imgui.text(f"{IconBrands.ICON_APPLE} {device.title}")
                    elif isinstance(device, backend.AndroidDevice):
                        imgui.text(f"{IconBrands.ICON_ANDROID} {device.title}")
                    imgui.same_line(spacing=32/DPI_SCALE)

                    if imgui.small_button(f"{Icons.ICON_CIRCLE_PLAY} Run"):
                        project_view.start_task(device.install_and_run(self.root_abspath))
                    imgui.same_line(spacing=16/DPI_SCALE)
                    if imgui.small_button(f"{Icons.ICON_CIRCLE_PLAY} Build & Run"):
                        f = isinstance(device, backend.AndroidDevice) and backend.build_android or backend.build_ios
                        project_view.start_task(backend.SeqTask(
                            f(self.root_abspath, open_dir=False),
                            device.install_and_run(self.root_abspath)
                        ))
                imgui.spacing()
                imgui.separator()

                imgui.columns(4, border=False)
                column_width = imgui.get_column_width()
                
                if imgui.button(f"{Icons.ICON_C} Compile Framework", width=column_width):
                    project_view.start_task(backend.compile_framework())
                imgui.next_column()
                if imgui.button(f"{Icons.ICON_T} Sync Template", width=column_width):
                    backend.sync_project_template(self.root_abspath)
                # ------------------------- #
                imgui.next_column()

                current_task = backend.TaskCommand.instance
                if current_task is None:
                    imgui.push_style_var(imgui.STYLE_ALPHA, 0.5)
                    imgui.button(f"{Icons.ICON_CIRCLE_STOP} Stop Task", width=column_width)
                    imgui.pop_style_var()
                else:
                    if imgui.button(f"{Icons.ICON_CIRCLE_STOP} Stop Task", width=column_width):
                        current_task.kill()
                imgui.next_column()
                ...
                imgui.next_column()
                if imgui.button(f"{Icons.ICON_V} Open in VSCode", width=column_width):
                    list(backend.start_vscode(self.selected_file_abspath, self.root_abspath))
                imgui.next_column()
                if imgui.button(f"{Icons.ICON_CIRCLE_PLAY} Run Project", width=column_width):
                    project_view.start_task(backend.run_project(self.root_abspath))
                imgui.next_column()
                if imgui.button(f"{Icons.ICON_TRASH_CAN} Clean Project", width=column_width):
                    backend.clean_build_dir(self.root_abspath)
                imgui.next_column()
                if imgui.button(f"{Icons.ICON_FILE_EXCEL} Build Excel", width=column_width):
                    backend.build_excel(self.root_abspath)
                # ------------------------- #
                imgui.next_column()
                if imgui.button(f"{IconBrands.ICON_WINDOWS} Build Desktop", width=column_width):
                    backend.build_win32(self.root_abspath)
                imgui.next_column()
                if imgui.button(f"{IconBrands.ICON_ANDROID} Build Android", width=column_width):
                    project_view.start_task(backend.build_android(self.root_abspath))
                imgui.next_column()
                if sys.platform != 'darwin':
                    imgui.push_style_var(imgui.STYLE_ALPHA, 0.5)
                    imgui.button(f"{IconBrands.ICON_APPLE} Build iOS", width=column_width)
                    imgui.pop_style_var()
                else:
                    if imgui.button(f"{IconBrands.ICON_APPLE} Build iOS", width=column_width):
                        project_view.start_task(backend.build_ios(self.root_abspath))
                imgui.next_column()
                if imgui.button(f"{IconBrands.ICON_CHROME} Build Web", width=column_width):
                    project_view.start_task(backend.build_web(self.root_abspath))
                imgui.next_column()
                # ------------------------- #

                imgui.columns(1)

                # scroll area
                imgui.begin_child("Console", flags=imgui.WINDOW_NO_BACKGROUND, border=True)
                imgui.push_style_var(imgui.STYLE_FRAME_PADDING, (10/DPI_SCALE, 10/DPI_SCALE))
                self.render_console()
                imgui.pop_style_var()
                imgui.end_child()

        with imgui.begin_tab_item("    File    ") as tab:
            if tab.selected:
                # scroll area
                imgui.begin_child("FileContent", flags=imgui.WINDOW_NO_BACKGROUND)
                imgui.push_style_var(imgui.STYLE_FRAME_PADDING, (10/DPI_SCALE, 10/DPI_SCALE))
                self.render_text_editor()
                imgui.pop_style_var()
                imgui.end_child()

        imgui.end_tab_bar()

        imgui.end_child()


if __name__ == "__main__":
    assert glfw.init()

    # use opengl 330 core
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 3)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 3)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)

    if sys.platform == 'darwin':
        # https://github.com/ocornut/imgui/pull/229/files
        glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, gl.GL_TRUE)

    # Create a windowed mode window and its OpenGL context
    window = glfw.create_window(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "CarrotLib🥕 Playground", None, None
    )

    if not window:
        print("[ERROR]", "Failed to create window")
        glfw.terminate()
        exit(1)

    # Make the window's context current
    glfw.make_context_current(window)

    # Setup Dear ImGui context
    imgui.create_context()
    impl = GlfwRenderer(window)

    imgui.get_io().font_global_scale = 1.0 / DPI_SCALE

    project_view = ProjectView()
    impl.refresh_font_texture()

    # Main loop
    while not glfw.window_should_close(window):
        project_view.poll_task()
        glfw.poll_events()
        impl.process_inputs()

        imgui.new_frame()

        with imgui.font(project_view.default_font):
            imgui.push_style_var(imgui.STYLE_FRAME_PADDING, (0, 10/DPI_SCALE))
            imgui.set_next_window_position(0, 0)
            window_size = glfw.get_window_size(window)
            imgui.set_next_window_size(window_size[0], window_size[1])
            imgui.begin("playground", flags=imgui.WINDOW_NO_DECORATION | imgui.WINDOW_NO_BACKGROUND)
            project_view.render()
            imgui.end()
            imgui.pop_style_var()

        gl.glClearColor(33/255, 37/255, 43/255, 1.0)
        gl.glClear(gl.GL_COLOR_BUFFER_BIT)

        imgui.render()
        impl.render(imgui.get_draw_data())

        glfw.swap_buffers(window)

    # Cleanup
    current_task = backend.TaskCommand.instance
    if current_task is not None:
        current_task.kill()
    project_view.threading_task.dispose()
    impl.shutdown()
    glfw.terminate()

    backend.config.project = project_view.root_abspath
    backend.config.save()

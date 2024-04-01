import os
import shutil
import json

from .framework import FRAMEWORK_EXE_PATH, FRAMEWORK_BUILD_DIR, is_framework_compiled
from .base import cmd, TaskCommand

project_pyright_config = {
    "stubPath": os.path.abspath("template/typings"),
    "extraPaths": [ os.path.abspath("3rd/pocketpy/include/typings")],
    "reportMissingModuleSource": "none",
    "pythonVersion": "3.10"
}

def sync_project_template(project: str):
    if not os.path.exists(project):
        print(f"{project} 不存在")
        return
    for td in ['carrotlib']:
        path = os.path.join(project, td)
        if os.path.exists(path):
            shutil.rmtree(path, ignore_errors=False)
        shutil.copytree(os.path.join('template', td), path)
    # create pyrightconfig.json
    with open(os.path.join(project, "pyrightconfig.json"), "wt", encoding='utf-8') as f:
        f.write(json.dumps(project_pyright_config, indent=4))
    # create .gitignore
    with open(os.path.join(project, ".gitignore"), "wt", encoding='utf-8') as f:
        f.write('__pycache__/\n')
        f.write('build/\n')
        f.write('.vscode/\n')
        f.write('carrotlib/\n')
        f.write('*.DS_Store\n')
        f.write('pyrightconfig.json\n')
                
    print(f"{project} 模板同步完成")

def new_project(root: str):
    assert len(os.listdir(root)) == 0
    sync_project_template(root)
    # create main.py
    with open(os.path.join(root, "main.py"), "wt", encoding='utf-8') as f:
        f.write("""import carrotlib as cl
from linalg import vec2

class MyGame(cl.Game):
    def on_ready(self):
        super().on_ready()

        label = cl.controls.Label()
        label.text = "Hello, world"
        label.font_size = 100
        label.color = cl.Colors.Black
        label.position = vec2(640, 360)

    @property
    def design_size(self):
        return (1280, 720)
""")

def run_project(path: str):
    if not is_framework_compiled():
        print("框架未编译，请先编译框架")
        return
    if not os.path.exists(os.path.join(path, "carrotlib")):
        sync_project_template(path)
    return TaskCommand([FRAMEWORK_EXE_PATH, path], cwd=FRAMEWORK_BUILD_DIR)
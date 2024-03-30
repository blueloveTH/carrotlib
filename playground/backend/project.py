import os
import shutil

from .framework import FRAMEWORK_EXE_PATH, FRAMEWORK_BUILD_DIR, is_framework_compiled
from .base import cmd

project_pyright_config = {
    "stubPath": os.path.abspath("template/typings"),
    "extraPaths": [os.path.abspath("template"), os.path.abspath("3rd/pocketpy/include/typings")],
    "reportMissingModuleSource": "none",
    "pythonVersion": "3.10"
}

def sync_project_template(project: str):
    project_path = os.path.join("projects", project)
    if not os.path.exists(project_path):
        print(f"{project} 不存在")
        return
    for td in ['carrotlib']:
        path = os.path.join(project, td)
        if os.path.exists(path):
            shutil.rmtree(path, ignore_errors=False)
        shutil.copytree(os.path.join('template', td), path)
    print(f"{project} 模板同步完成")

def new_project(name: str):
    project_path = os.path.join("projects", name)
    if os.path.exists(project_path):
        print(f"项目 {name} 已存在")
        return
    os.makedirs(project_path)
    sync_project_template(name)

def run_project(path: str):
    assert is_framework_compiled()
    cmd([FRAMEWORK_EXE_PATH, path], cwd=FRAMEWORK_BUILD_DIR)
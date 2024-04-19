import os
import sys
import shutil

from .base import TaskCommand
from .config import config

assert sys.platform in ["win32", "linux", "darwin"]

if sys.platform == "win32":
    FRAMEWORK_EXE_PATH = os.path.abspath("build/win32/Release/Game.exe")
else:
    FRAMEWORK_EXE_PATH = os.path.abspath(f"build/{sys.platform}/Game")

FRAMEWORK_BUILD_DIR = os.path.abspath(f"build/{sys.platform}")

def compile_framework():
    if not os.path.exists("3rd/pocketpy/CMakelists.txt"):
        print("[INFO]", "Updating submodules")
        task = TaskCommand(["git", "submodule", "update", "--init", "--recursive"])
        yield from task
        if task.returncode != 0:
            return

    shutil.rmtree(FRAMEWORK_BUILD_DIR, ignore_errors=True)
    os.makedirs(FRAMEWORK_BUILD_DIR, exist_ok=True)
    if config.use_release_build:
        build_type = '-DCMAKE_BUILD_TYPE=Release'
    else:
        build_type = '-DCMAKE_BUILD_TYPE=Debug'
    task = TaskCommand(["cmake", "../..", build_type], cwd=FRAMEWORK_BUILD_DIR)
    yield from task
    if task.returncode != 0:
        return
    task = TaskCommand(["cmake", "--build", ".", "--config", "Release"], cwd=FRAMEWORK_BUILD_DIR)
    yield from task
    if task.returncode != 0:
        return
    assert is_framework_compiled()
    if config.use_release_build:
        with open(os.path.join(FRAMEWORK_BUILD_DIR, "this_is_a_release_build"), "w") as f:
            f.write("")

def is_framework_compiled():
    return os.path.exists(FRAMEWORK_EXE_PATH)

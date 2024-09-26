import subprocess
import os
import sys

if not os.path.exists("subprojects"):
    os.mkdir("subprojects")
    print(f"Installing wrap: fmt")
    subprocess.run(f"meson wrap install fmt", shell=True)


def meson_build():
    command = "meson setup".split(" ")
    command.extend(sys.argv[1:])
    command.append("build")
    return " ".join(command)


subprocess.run(meson_build(), shell=True)

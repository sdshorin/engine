import sys
import platform
import os

print('..Building')

ldflags = ""
cppflags = "-std=c++0x"

# scons --debug_build --use_asan
AddOption(
    '--debug_build',
    dest='debug', 
    default=False,
    action='store_true', 
    help='add debug symbols, don\'t use -03',
)



def linux_get_lib_dir(libs_pathes, name, pkg):
    for library, path in libs_pathes:
        # print(library, name)
        if library.find(name) != -1:
            return os.path.dirname(path)
    exep = f"Please, install {name} with command 'sudo apt-get install -y {pkg}'"
    raise FileNotFoundError(exep) # need to instal lib

def linux_get_installed_libs():
    output = os.popen('ldconfig -p').read()
    libs_arr = []
    for line in output.splitlines():
        if line.find("=>") == -1:
            continue
        library, path = line.split("=>")
        library = library.strip("\t ").split()[0]
        path = path.strip("\t ")
        if not library.endswith("so"):
            continue
        libs_arr.append([library, path])
    return libs_arr
    # print(output)

def linux_get_lib_headers(lib_name: str):
    output = os.popen(f"dpkg -L {lib_name.lower()}").read()
    return output.split("-I")[-1].strip() 

def linux_get_pkg_headers(lib_name: str, lib_pkg: str):
    output = os.popen(f"dpkg -L {lib_pkg.lower()}").read()
    for line in output.splitlines():
        if line.endswith(".hpp") and line.find(f"/{lib_name}/") != -1:
            return line.split(f"/{lib_name}/")[0] + f"/{lib_name}/"
    print(output)
    exep = f"Please, install {lib_name} with command 'sudo apt-get install -y {lib_pkg}'"
    raise FileNotFoundError(exep) # need to instal lib
    # return output.split("-I")[-1].strip() 





if GetOption("debug"):
    cppflags += " -g"
else:
    cppflags += " -O2"

if sys.platform == "darwin":
    # Support only MacOS with arm processor
    # MacOS uses a different library path
    assert(platform.processor() == "arm")
    env=Environment(
        CPPPATH=["/opt/homebrew/include"],
        LIBPATH=['/opt/homebrew/lib'],
        )
    env.Replace(LINK='clang++')
    ldflags += '-stdlib=libc++'
elif sys.platform.startswith("linux"):
    libs = linux_get_installed_libs()
    lib_pathes = []
    lib_headers = []
    for libname, pkg in [["SDL2", "libsdl2-dev"]]:
        path = linux_get_lib_dir(libs, "lib" + libname, pkg)
        if not path in lib_pathes:
            lib_pathes.append(path)
            print(path)
        lib_headers.append(linux_get_lib_headers(libname))
    for libname, pkg in [["glm", "libglm-dev"]]:
        lib_headers.append(linux_get_pkg_headers(libname, pkg))
    print(f"lib_pathes: {lib_pathes}")
    print(f"lib_headers: {lib_headers}")
    env=Environment(
        CPPPATH=lib_headers,
        LIBPATH=lib_pathes,
        )
else:
    # TODO: add Environment for other OS
    # add SDL2 and glm library for others platforms
    assert(False)

env["CXXFLAGS"] = cppflags
env["LINKFLAGS"] = ldflags

env.Append(CPPPATH='src/core')
env.Append(CPPPATH='src/objects')
env.Append(CPPPATH='src/render/cpu_render')
env.Append(CPPPATH='src/render/core')
env.Program('CPURender', Glob('src/**/*.cpp') + Glob('src/**/**/*.cpp'), LIBS=["SDL2"]) 


import sys
import platform

print('..Building')

ldflags = '-stdlib=libc++'
cppflags = "-std=c++0x"

# scons --debug_build --use_asan
AddOption(
    '--debug_build',
    dest='debug', 
    default=False,
    action='store_true', 
    help='add debug symbols, don\'t use -03',
)
AddOption(
    '--use_asan',
    dest='use_asan', 
    default=False,
    action='store_true', 
    help='add address sanitizer',
)


if GetOption("debug"):
    cppflags += " -g"
else:
    cppflags += " -O2"

if GetOption("use_asan"):
    ldflags += " -fsanitize=address"
    cppflags += " -fsanitize=address"

if sys.platform == "darwin":
    # Support only MacOS with arm processor
    # MacOS uses a different library path
    assert(platform.processor() == "arm")
    env=Environment(
        CPPPATH=["/opt/homebrew/include"],
        LIBPATH=['/opt/homebrew/lib'],
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
env.Replace(LINK='clang++')
env.Program('CPURender', Glob('src/**/*.cpp') + Glob('src/**/**/*.cpp'), LIBS=["SDL2"]) 


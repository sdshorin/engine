print('..Building')

# USE_ASAN = False
# args.Add('debug', 'Build a debug binary', '')

ldflags = '-stdlib=libc++'
cppflags = "-std=c++0x"
# AddOption("debug")
# if GetOption("debug")
if True:
    cppflags += " -g"
else:
    cppflags += " -O2"

# if USE_ASAN:
    # ldflags += " -fsanitize=address"
    # cppflags += " -fsanitize=address"

env=Environment(
    CPPPATH=["/opt/homebrew/include"],
    LIBPATH=['/opt/homebrew/lib'],
    CXXFLAGS=cppflags,
    LINKFLAGS=ldflags
    )


env.Append(CPPPATH='src/core')
env.Append(CPPPATH='src/objects')
env.Append(CPPPATH='src/render/cpu_render')
env.Append(CPPPATH='src/render/core')
env.Replace(LINK='clang++')
env.Program('CPURender', Glob('src/**/*.cpp') + Glob('src/**/**/*.cpp'), LIBS=["SDL2"]) 


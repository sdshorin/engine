print('..Building')

env=Environment(
    CPPPATH=["/opt/homebrew/include"],
    LIBPATH=['/opt/homebrew/lib'],
    CXXFLAGS="-std=c++0x -g"
    )

env.Append(CPPPATH='src/core')
env.Append(CPPPATH='src/objects')
env.Append(CPPPATH='src/render/cpu_render')
env.Append(CPPPATH='src/render/core')

env.Program('CPURender', Glob('src/**/*.cpp') + Glob('src/**/**/*.cpp'), LIBS=["SDL2"]) 


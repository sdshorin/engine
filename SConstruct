print('..Building')

env=Environment(
    CPPPATH=["/opt/homebrew/include"],
    LIBPATH=['/opt/homebrew/lib'],
    CXXFLAGS="-std=c++0x -g"
    )

env.Program('CPURender', Glob('*.cpp'), LIBS=["SDL2"]) 


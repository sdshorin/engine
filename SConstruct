print('..Building World')

env=Environment(
    # CPPPATH='/usr/include/boost/',
    # CPPDEFINES=[],
    
    # LIBS=[],
    # CPPPATH=["/opt/homebrew/Cellar/glm/0.9.9.8/include", "/opt/homebrew/Cellar/sdl2/2.26.1/include)"],
    CPPPATH=["/opt/homebrew/include"],
    LIBPATH=['/opt/homebrew/lib'],
#     LDFLAGS=-L/opt/homebrew/lib
# CPPFLAGS=-I/opt/homebrew/include
    CXXFLAGS="-std=c++0x -g"
    )

env.Program('CPURender', Glob('*.cpp'), LIBS=["SDL2"]) 
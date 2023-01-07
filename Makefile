
SRC = main.cpp VisualServer.cpp
FLAGS =  -std=c++20
GRAPHIC_FLAGS = -framework OpenGl -framework Cocoa -I/usr/local/Cellar/glfw/3.3.2/include -lglfw3 -framework CoreVideo -framework IOKit -lSOIL

all:
	g++ $(FLAGS) $(GRAPHIC_FLAGS) $(SRC)





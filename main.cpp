#include "engine.hpp"
#include "Triangle.hpp"

int main() {
	Engine* engine = new Engine;
	engine->visual_server = new VisualServer;

	// GraphicSettings *settings = new GraphicSettings;
	engine->visual_server->InitGraphic();

	engine->root->add_child(new Triangle);

	engine->Run();

}
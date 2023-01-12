#include "engine.hpp"
#include "Triangle.hpp"
#include "Mesh.hpp"

int main() {
	Mesh mesh;
	// mesh.load_obj_file("objects/test.obj");
	mesh.load_obj_file("objects/cube.obj");
	Engine* engine = new Engine;
	engine->visual_server = new VisualServer;

	// GraphicSettings *settings = new GraphicSettings;
	engine->visual_server->InitGraphic();

	// engine->root->add_child(new Triangle);
	engine->root->add_child(&mesh);

	engine->Run();

}

















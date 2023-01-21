#include "engine.hpp"
#include "Triangle.hpp"
#include "Mesh.hpp"

int main() {
	std::srand(std::time(nullptr));

	Engine& engine = Engine::getInstance();
	engine.visual_server = new VisualServer;

	// GraphicSettings *settings = new GraphicSettings;
	engine.visual_server->InitGraphic();

	// MeshResource res("objects/cube.obj");
	MeshResource res("objects/teapot.obj");
	// MeshResource res("objects/test.obj");
	Mesh mesh(res);
	// engine->root->add_child(new Triangle);
	engine.root.add_child(&mesh);

	engine.Run();

}

















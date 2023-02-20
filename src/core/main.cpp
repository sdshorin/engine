#include "engine.hpp"
#include "Triangle.hpp"
#include "Mesh.hpp"
#include "RotationNode.hpp"
#include <memory>

int main() {
	std::srand(std::time(nullptr));

	Engine& engine = Engine::getInstance();
	engine.visual_server = new VisualServer;

	// GraphicSettings *settings = new GraphicSettings;
	engine.visual_server->InitGraphic();

	MeshResource cube_res("objects/cube.obj");
	MeshResource teapot_res("objects/teapot.obj");
	// MeshResource res("objects/test.obj");
	std::shared_ptr<TreeObject> cube1 = std::make_shared<MeshObject> (cube_res);
	std::shared_ptr<TreeObject> cube2 = std::make_shared<MeshObject> (cube_res);
	std::shared_ptr<TreeObject> cube3 = std::make_shared<MeshObject> (cube_res);
	std::shared_ptr<TreeObject> cube4 = std::make_shared<MeshObject> (cube_res);
	std::shared_ptr<TreeObject> cube5 = std::make_shared<MeshObject> (cube_res);
	std::shared_ptr<TreeObject> cube6 = std::make_shared<MeshObject> (cube_res);
	
	cube1->move(glm::vec3(2.5, 0.0, 0.0));
	cube2->move(glm::vec3(-2.5, 0.0, 0.0));
	cube3->move(glm::vec3(0, 2.5, 0.0));
	cube4->move(glm::vec3(0, -2.5, 0.0));
	cube5->move(glm::vec3(0, 0, 2.5));
	cube6->move(glm::vec3(0, 0, -2.5));

	std::shared_ptr<TreeObject> teapot = std::make_shared<MeshObject>(teapot_res);


	std::shared_ptr<TreeObject> rotated_node1 = std::make_shared<RotationNode>(glm::vec3(0.0, 0, 1));
	rotated_node1->add_child(cube1);
	rotated_node1->add_child(cube2);
	rotated_node1->add_child(cube3);
	rotated_node1->add_child(cube4);
	rotated_node1->add_child(cube5);
	rotated_node1->add_child(cube6);

	std::shared_ptr<TreeObject> rotated_node2 = std::make_shared<RotationNode>(glm::vec3(0.0, 1, 1), 0.5);
	rotated_node2->add_child(rotated_node1);
	rotated_node2->move(glm::vec3(0, 1.0, 0.0));

	engine.root.add_child(rotated_node2);




	std::shared_ptr<TreeObject> rotated_node_teapot = std::make_shared<RotationNode>(glm::vec3(0.0, 0, 1), 0.6);
	std::shared_ptr<TreeObject> rotated_node_teapot2 = std::make_shared<RotationNode>(glm::vec3(0.0, 1, 0), 0.3);
	rotated_node_teapot->add_child(rotated_node_teapot2);
	rotated_node_teapot2->add_child(teapot);
	teapot->move(glm::vec3(0.0, -1.0, 0.0));

	engine.root.add_child(rotated_node_teapot);

	engine.Run();

}

















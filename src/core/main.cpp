
#if __linux__
#include <memory>
#include <ctime>
#endif

#include "MeshScript.hpp"
#include "RotationScript.hpp"
// #include "Triangle.hpp"
#include "engine.hpp"
#include "Node.hpp"
#include "EmptyScript.hpp"

#define create_node(arg) std::make_unique<eng::Node>(arg);

using NodeRef = std::unique_ptr<eng::Node>;

int main() {
    std::srand(std::time(nullptr));

    eng::Engine& engine = eng::Engine::getInstance();
    engine.visual_server = new eng::VisualServer;

    // GraphicSettings *settings = new GraphicSettings;
    engine.visual_server->InitGraphic();

    eng::MeshResource cube_res("objects/cube.obj");
    eng::MeshResource teapot_res("objects/teapot.obj");

    NodeRef rotated_node_cube_1 = create_node(eng::RotationScript(glm::vec3(0.0, 0, 1)));
    std::vector<glm::vec3> offsets({{2.5, 0.0, 0.0},
                                    {-2.5, 0.0, 0.0},
                                    {0, 2.5, 0.0},
                                    {0, -2.5, 0.0},
                                    {0, 0, 2.5},
                                    {0, 0, -2.5},
    });
    for (int i = 0; i < offsets.size(); ++i) {
        NodeRef cube = create_node(eng::MeshScript(cube_res));
        cube->move(offsets[i]);
        rotated_node_cube_1->add_child(std::move(cube));

    }

    NodeRef rotated_node_cube_2 = create_node(eng::RotationScript(glm::vec3(0.0, 1, 1), 0.5));
    rotated_node_cube_2->add_child(std::move(rotated_node_cube_1));
    rotated_node_cube_2->move(glm::vec3(0, 1.0, 0.0));

    engine.root.add_child(std::move(rotated_node_cube_2));


    NodeRef teapot = create_node(eng::MeshScript(teapot_res));
    teapot->move(glm::vec3(0.0, -1.0, 0.0));
    NodeRef rotated_node_teapot_1 = create_node(eng::RotationScript(glm::vec3(0.0, 0, 1), 0.6));
    NodeRef rotated_node_teapot_2 = create_node(eng::RotationScript(glm::vec3(0.0, 1, 0), 0.3));
    rotated_node_teapot_2->add_child(std::move(teapot));
    rotated_node_teapot_1->add_child(std::move(rotated_node_teapot_2));
    engine.root.add_child(std::move(rotated_node_teapot_1));


    engine.Run();
}

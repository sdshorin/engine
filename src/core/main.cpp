
#if __linux__
#include <memory>
#include <ctime>
#endif

#include "MeshScript.hpp"
#include "RotationScript.hpp"
#include "SqueezeScript.hpp"

#include "engine.hpp"
#include "Node.hpp"
#include "EmptyScript.hpp"
#include "ProjectSettings.hpp"

#define create_node(arg) std::make_unique<eng::Node>(arg);

using NodeRef = std::unique_ptr<eng::Node>;



void add_dynamic_scene(eng::Engine& engine, eng::ResourceRef cube_res, eng::ResourceRef teapot_res) {
    NodeRef rotated_node_cube_1 = create_node(eng::RotationScript(glm::vec3(0.0, 0, 1)));
    std::vector<glm::vec3> offsets({{4.0, 0.0, 0.0},
                                    {-4.0, 0.0, 0.0},
                                    {0, 4.0, 0.0},
                                    {0, -4.0, 0.0},
                                    {0, 0, 4.0},
                                    {0, 0, -4.0},
    });
    for (int i = 0; i < offsets.size(); ++i) {
        if (i < 2) {
            NodeRef little_teapot = create_node(eng::MeshScript(teapot_res));
            little_teapot->move(offsets[i] * 4.0f);
            little_teapot->scale({0.25, 0.25, 0.25});
            rotated_node_cube_1->add_child(std::move(little_teapot));
            continue;
        }
        NodeRef cube = create_node(eng::MeshScript(cube_res));
        cube->move(offsets[i]);
        rotated_node_cube_1->add_child(std::move(cube));

    }


    NodeRef rotated_node_cube_2 = create_node(eng::RotationScript(glm::vec3(0.0, 1, 1), 0.5));

    rotated_node_cube_2->add_child(std::move(rotated_node_cube_1));
    rotated_node_cube_2->move(glm::vec3(0, 1.0, 0.0));

    engine.root.add_child(std::move(rotated_node_cube_2));


    NodeRef teapot = create_node(eng::MeshScript(teapot_res));
    NodeRef squeeze = create_node(eng::SqueezeScript({0.5, 0.5, 0.5}, 1));

    teapot->move(glm::vec3(0.0, -1.0, 0.0));
    NodeRef rotated_node_teapot_1 = create_node(eng::RotationScript(glm::vec3(0.0, 0, 1), 0.6));
    rotated_node_teapot_1->move(glm::vec3(1.0, 0.0, 0.0));
    NodeRef rotated_node_teapot_2 = create_node(eng::RotationScript(glm::vec3(0.0, 1, 0), 0.3));
    squeeze->add_child(std::move(teapot));
    rotated_node_teapot_2->add_child(std::move(squeeze));
    rotated_node_teapot_1->add_child(std::move(rotated_node_teapot_2));
    engine.root.add_child(std::move(rotated_node_teapot_1));
}


void add_static_scene(eng::Engine& engine, eng::ResourceRef cube_res, eng::ResourceRef teapot_res) {
    NodeRef teapot = create_node(eng::MeshScript(teapot_res));
    engine.root.add_child(std::move(teapot));
}


int main() {
    time_t seed = std::time(nullptr);
    std::cout << "Init with seed: " << seed << "\n";
    std::srand(seed);
    
    eng::ProjectSettings settings;
    eng::Engine engine(settings);

    engine.visual_server.InitGraphic();

    eng::ResourceRef cube_res = engine.load_resource("objects/cube.obj");
    eng::ResourceRef teapot_res = engine.load_resource("objects/teapot.obj");

    add_dynamic_scene(engine, cube_res, teapot_res);
    // add_static_scene(engine, cube_res, teapot_res);


    engine.Run();
}

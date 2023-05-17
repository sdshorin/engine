
#include "CPUVisualStorage.hpp"

namespace cpu_render {


CPUVisualStorage::CPUVisualStorage(eng::MeshResource& res) {

    load_pos(res.triangles);
    load_colour(res.colours);
}

void CPUVisualStorage::load_pos(const std::vector<glm::vec4>& positions) {
    if (data.size() < positions.size()) {
        data.resize(positions.size());
    }
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].pos = positions[i];
    }
}

void CPUVisualStorage::load_colour(const std::vector<glm::vec3>& colours) {
    if (data.size() < colours.size()) {
        data.resize(colours.size());
    }
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].colour = colours[i];
    }
}

}   // namespace cpu_render


#include "CPUVisualStorage.hpp"

void CPUVisualStorage::load_pos(const std::vector<glm::vec4>& positions) {
    if (data.size() < positions.size()) {
        data.resize(positions.size());
    }
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].pos = positions[i];
    }
}

void CPUVisualStorage::load_colour(const std::vector<glm::ivec3>& colours) {
    if (data.size() < colours.size()) {
        data.resize(colours.size());
    }
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].colour = colours[i];
    }
}

void CPUVisualStorage::load_uv(const std::vector<glm::vec2>& uv) {
    if (data.size() < uv.size()) {
        data.resize(uv.size());
    }
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].uv = uv[i];
    }
}

void CPUVisualStorage::load_norm(const std::vector<glm::vec3>& norms) {
    if (data.size() < norms.size()) {
        data.resize(norms.size());
    }
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].norm = norms[i];
    }
}


void CPUVisualStorage::commit() {

}


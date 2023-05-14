
#include "EmptyScript.hpp"

namespace eng {

void EmptyScript::process(float delta) {
}

void EmptyScript::draw(eng::VisualServer* server) const {
}

void EmptyScript::set_owner(eng::Node* owner_in) {
    owner = owner_in;
}

}   // namespace eng

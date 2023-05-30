
#include "EmptyScript.hpp"

namespace scripts {

void EmptyScript::process(float delta) {
}

void EmptyScript::draw(eng::VisualServer* server) const {
}

void EmptyScript::set_owner(eng::Node* owner_in) {
    owner = owner_in;
}

}   // namespace scripts

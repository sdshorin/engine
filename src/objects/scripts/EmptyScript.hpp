# pragma once
#include <VisualServer.h>
#include "Node.hpp"

class EmptyScript {
public:
    void process(float delta);
    void draw(eng::VisualServer* server) const;
    void set_owner(eng::Node* owner);
};



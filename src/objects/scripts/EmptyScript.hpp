# pragma once
#include <VisualServer.h>
#include "Node.hpp"

namespace eng {

class EmptyScript {
protected:
    Node* owner;
public:
    virtual void process(float delta);
    virtual void draw(eng::VisualServer* server) const;
    virtual void set_owner(eng::Node* owner);
};

}   // namespace eng

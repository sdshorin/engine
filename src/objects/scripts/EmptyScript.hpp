# pragma once
#include <VisualServer.h>
#include "Node.hpp"

namespace scripts {

class EmptyScript {
protected:
    eng::Node* owner;
public:
    virtual void process(float delta);
    virtual void draw(eng::VisualServer* server) const;
    virtual void set_owner(eng::Node* owner);
};

}   // namespace scripts

#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "VisualServer.h"

namespace eng {
class Node;
}

class AnyScript
{
public:
    template <typename T>
    AnyScript(T x) : ptr(new Content<T>(std::move(x))) {}

    AnyScript(const AnyScript &from) : ptr(from.ptr->copy_()) {}
    AnyScript(AnyScript &&) noexcept = default;

    AnyScript &operator=(const AnyScript &x) {
        AnyScript tmp(x);
        *this = std::move(tmp);
        return *this;
    }
    AnyScript &operator=(AnyScript &&) noexcept = default;


    void process(float delta) {
        ptr->process(delta);
    }

    void draw(eng::VisualServer* server) const {
        ptr->draw(server);
    }

    void set_owner(eng::Node* owner) {
        ptr->set_owner(owner);
    }

private:
    struct BaseContent {
        virtual ~BaseContent() = default;
        virtual BaseContent *copy_() const = 0;

        virtual void process(float delta) = 0;
        virtual void draw(eng::VisualServer* server) const = 0;
        virtual void set_owner(eng::Node* owner) = 0;
    };

    template <typename T>
    struct Content : BaseContent {
        Content(T x) : object(std::move(x)) {}
        BaseContent *copy_() const { return new Content(*this); }
        Content(const Content &) noexcept = default;

        void process(float delta) {
            object.process(delta);
        }

        void draw(eng::VisualServer* server) const {
            object.draw(server);
        }
        void set_owner(eng::Node* owner) {
            object.set_owner(owner);
        }

        T object;
    };

    std::unique_ptr<BaseContent> ptr;
};


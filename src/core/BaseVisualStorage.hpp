#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace eng {


class BaseVisualStorage {
   public:


    virtual ~BaseVisualStorage() = default;
};

using ResourceRef = std::shared_ptr<const BaseVisualStorage>;

}   // namespace eng

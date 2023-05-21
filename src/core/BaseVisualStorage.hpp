#pragma once
#include <glm/glm.hpp>
#include <vector>

#if __linux__
#include <memory>
#endif

namespace eng {


class BaseVisualStorage {
   public:


    virtual ~BaseVisualStorage() = default;
};

using ResourceRef = std::shared_ptr<const BaseVisualStorage>;

}   // namespace eng

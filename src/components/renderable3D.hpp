#pragma once

#include "components/transform.hpp"

namespace nith
{
    struct Renderable3D
    {
        mat4 modelMatrix;

        void updateModelMatrix(const Transform& transform)
        {
            mat4 model(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::eulerAngleXYZ(transform.rotation.x,
                transform.rotation.y, transform.rotation.z);
            model = glm::scale(model, transform.scale);
            modelMatrix = model;
        }
    };
}
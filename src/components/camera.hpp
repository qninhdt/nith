#pragma once

#include "window.hpp"
#include "components/transform.hpp"

namespace nith
{
    struct Camera
    {
        static constexpr v3 XAxisVector = { 1, 0, 0 };
        static constexpr v3 YAxisVector = { 0, 1, 0 };
        static constexpr v3 ZAxisVector = { 0, 0, 1 };

        f32 aspect;
        f32 fov;
        f32 zoom;
        f32 near;
        f32 far;
        v3 forwardVector;
        v3 rightVector;
        v3 upVector;
        mat4 projectionMatrix;
        mat4 viewMatrix;
        Window* window;

        // shit
        f32 speed;
        f32 sensitive;

        void updateViewMatrix(const Transform& transform)
        {
            const v3 direction = transform.getDirection();
            viewMatrix = glm::lookAt(transform.position, transform.position + direction,
                YAxisVector);

            rightVector = glm::normalize(glm::cross(direction, YAxisVector));
            forwardVector = glm::normalize(glm::cross(YAxisVector, rightVector));
        }

        void updateProjectionMatrix()
        {
            projectionMatrix = glm::perspective(fov, aspect, near, far);
        }
    };
}
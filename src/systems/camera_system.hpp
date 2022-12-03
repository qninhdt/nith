#pragma once

#include "components/transform.hpp"
#include "components/camera.hpp"
#include "window.hpp"
#include "gl/shader.hpp"

namespace nith
{
    class CameraSystem
    {
    public:
        static void Init();
        static entt::entity CreateCamera(Window& window,
            const f32& aspect, const f32& fov, const f32& near, const f32& far);
        static void Update(const float& deltaTime);

        static void Active(const entt::entity& camera);
    };
}
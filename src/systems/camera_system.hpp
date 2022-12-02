#pragma once

#include "components/transform.hpp"
#include "components/camera.hpp"
#include "window.hpp"

namespace nith
{
    class CameraSystem
    {
    public:
        static void Init(entt::registry& registry);
        static entt::entity CreateCamera(entt::registry& registry, Window& window,
            const f32& aspect, const f32& fov, const f32& near, const f32& far);
        static void Update(entt::registry& registry, const float& deltaTime);

    };
}
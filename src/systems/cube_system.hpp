#pragma once

namespace nith
{
    class CubeSystem
    {
    public:
        static entt::entity CreateCube(entt::registry& registry, const v3& position,
            const v3 rotation, const v3& color);
        static void Render(entt::registry& registry, entt::entity cameraEntity, const f32& deltaTime);
    };
}
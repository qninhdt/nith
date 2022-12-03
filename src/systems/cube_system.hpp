#pragma once

namespace nith
{
    class CubeSystem
    {
    public:
        static entt::entity CreateCube(const v3& position,
            const v3 rotation, const v3& color);
        static void Render(entt::entity cameraEntity, const f32& deltaTime);
    };
}
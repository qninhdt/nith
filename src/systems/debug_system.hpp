#pragma once

namespace nith
{
    class DebugSystem
    {
    public:
        static void Render(entt::registry& registry, const f32& deltaTime);
    };
}
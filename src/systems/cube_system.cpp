#include "systems/cube_system.hpp"
#include "components/transform.hpp"
#include "components/cube.hpp"
#include "components/cube_renderer.hpp"
#include "components/camera.hpp"

namespace nith
{
    entt::entity CubeSystem::CreateCube(entt::registry& registry, const v3& position,
        const v3 rotation, const v3& color)
    {
        auto entity = registry.create();
        auto& transform = registry.emplace<Transform>(entity);
        auto& cube = registry.emplace<Cube>(entity);
        auto& cubeRenderer = registry.emplace<CubeRenderer>(entity);

        cube.color = color;

        transform.position = position;
        transform.rotation = rotation;

        return entity;
    }

    void CubeSystem::Render(entt::registry& registry, entt::entity cameraEntity, const f32& deltaTime)
    {
        auto& camera = registry.get<Camera>(cameraEntity);



        auto view = registry.view<Cube, CubeRenderer, Transform>();
        for (auto [entity, cube, cubeEntity, transform] : view.each())
        {

        }

    }
}
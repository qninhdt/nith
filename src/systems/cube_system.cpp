#include "systems/cube_system.hpp"
#include "loaders/shader_loader.hpp"
#include "components/transform.hpp"
#include "components/cube.hpp"
#include "components/cube_renderer.hpp"
#include "components/camera.hpp"
#include "components/renderable3D.hpp"
#include "components/debug/transform_debug.hpp"

namespace nith
{
    entt::entity CubeSystem::CreateCube(entt::registry& registry, const v3& position,
        const v3 rotation, const v3& color)
    {
        auto entity = registry.create();
        auto& transform = registry.emplace<Transform>(entity);
        auto& cube = registry.emplace<Cube>(entity);
        auto& cubeRenderer = registry.emplace<CubeRenderer>(entity);
        auto& renderable3D = registry.emplace<Renderable3D>(entity);
        registry.emplace<TransformDebug>(entity);

        cube.color = color;

        transform.position = position;
        transform.rotation = rotation;

        cubeRenderer.mesh = new CubeMesh();

        renderable3D.updateModelMatrix(transform);

        return entity;
    }

    void CubeSystem::Render(entt::registry& registry, entt::entity cameraEntity, const f32& deltaTime)
    {
        auto& camera = registry.get<Camera>(cameraEntity);
        auto& shader = ShaderLoader::Get("cube");

        shader.use();

        shader.setMat4(shader.getUniformLocation("projection"), camera.projectionMatrix);
        shader.setMat4(shader.getUniformLocation("view"), camera.viewMatrix);

        auto view = registry.view<Cube, CubeRenderer, Renderable3D, Transform>();
        for (auto [entity, cube, cubeRenderer, renderable3D, transform] : view.each())
        {
            shader.setMat4(shader.getUniformLocation("model"), renderable3D.modelMatrix);
            cubeRenderer.mesh->render();
        }
    }
}
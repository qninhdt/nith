#include "systems/cube_system.hpp"
#include "systems/camera_system.hpp"
#include "loaders/shader_loader.hpp"
#include "components/transform.hpp"
#include "components/cube.hpp"
#include "components/cube_renderer.hpp"
#include "components/camera.hpp"
#include "components/renderable3D.hpp"
#include "components/debug/transform_debug.hpp"
#include "registry.hpp"

namespace nith
{
    entt::entity CubeSystem::CreateCube(const v3& position,
        const v3 rotation, const v3& color)
    {
        auto entity = Registry.create();
        auto& transform = Registry.emplace<Transform>(entity);
        auto& cube = Registry.emplace<Cube>(entity);
        auto& cubeRenderer = Registry.emplace<CubeRenderer>(entity);
        auto& renderable3D = Registry.emplace<Renderable3D>(entity);
        Registry.emplace<TransformDebug>(entity);

        cube.color = color;

        transform.position = position;
        transform.rotation = rotation;

        cubeRenderer.mesh = new CubeMesh();

        renderable3D.updateModelMatrix(transform);

        return entity;
    }

    void CubeSystem::Render(entt::entity cameraEntity, const f32& deltaTime)
    {
        auto& camera = Registry.get<Camera>(cameraEntity);
        auto& shader = ShaderLoader::Get("cube");

        shader.use();
        CameraSystem::Active(cameraEntity);

        auto view = Registry.view<Cube, CubeRenderer, Renderable3D, Transform>();
        for (auto [entity, cube, cubeRenderer, renderable3D, transform] : view.each())
        {
            shader.setMat4(shader.getUniformLocation(gl::ShaderUniform::MODEL),
                renderable3D.modelMatrix);
            cubeRenderer.mesh->render();
        }
    }
}
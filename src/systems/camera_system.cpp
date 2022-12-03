#include "systems/camera_system.hpp"
#include "io/input.hpp"
#include "window_event.hpp"
#include "registry.hpp"
#include "gl/shader.hpp"

namespace nith
{
    void CameraSystem::Init()
    {
        auto& dispatcher = io::Input::GetEventDispatcher();
        dispatcher.addEventListener<io::MouseMovedEvent>(
            [&](const io::MouseMovedEvent& event)
            {
                double deltaX = event.getMouseDeltaX();
                double deltaY = event.getMouseDeltaY();
   
                auto view = Registry.view<Camera, Transform>();
                for (auto [entity, camera, transform] : view.each())
                {
                    if (!camera.window->isShowCursor()) {
                        transform.rotation.x -= deltaY * camera.sensitive;
                        transform.rotation.y -= deltaX * camera.sensitive;
                        if (transform.rotation.x > +3.14 / 2) transform.rotation.x = +3.14 / 2;
                        if (transform.rotation.x < -3.14 / 2) transform.rotation.x = -3.14 / 2;
                        camera.updateViewMatrix(transform);
                    }
                }
            }
        );

    }

    entt::entity CameraSystem::CreateCamera(Window& window,
        const f32& aspect, const f32& fov, const f32& near, const f32& far)
    {
        auto entity = Registry.create();
        auto& camera = Registry.emplace<Camera>(entity);
        auto& transform = Registry.emplace<Transform>(entity);

        transform.rotation.y = 3.14f;
        camera.aspect = aspect;
        camera.fov = fov;
        camera.near = near;
        camera.far = far;
        camera.window = &window;

        camera.speed = 10;
        camera.sensitive = 0.005;
        
        camera.updateProjectionMatrix();
        camera.updateViewMatrix(transform);

        camera.window->addEventListener<WindowResizedEvent>(
            [&](const WindowResizedEvent& event)
            {
                camera.aspect = 1.0f * event.getWidth() / event.getHeight();
                camera.updateProjectionMatrix();
            }
        );

        return entity;
    }

    void CameraSystem::Update(const float& deltaTime)
    {
        auto view = Registry.view<Camera, Transform>();
        for (auto [entity, camera, transform] : view.each())
        {
            if (io::Input::IsKeyPressed(io::KeyCode::W))
                transform.position += camera.forwardVector * camera.speed * deltaTime;
            if (io::Input::IsKeyPressed(io::KeyCode::S))
                transform.position -= camera.forwardVector * camera.speed * deltaTime;
            if (io::Input::IsKeyPressed(io::KeyCode::D))
                transform.position += camera.rightVector * camera.speed * deltaTime;
            if (io::Input::IsKeyPressed(io::KeyCode::A))
                transform.position -= camera.rightVector * camera.speed * deltaTime;
            if (io::Input::IsKeyPressed(io::KeyCode::Space))
                transform.position += Camera::YAxisVector * camera.speed * deltaTime;
            if (io::Input::IsKeyPressed(io::KeyCode::LeftShift))
                transform.position -= Camera::YAxisVector * camera.speed * deltaTime;

            // TODO: only update 
            camera.updateViewMatrix(transform);
        }
    }

    void CameraSystem::Active(const entt::entity& cameraEntity)
    {
        auto& shader = gl::Shader::GetCurrentShader();
        auto& camera = Registry.get<Camera>(cameraEntity);

        shader.setMat4(shader.getUniformLocation(gl::ShaderUniform::PROJECTION),
            camera.projectionMatrix);

        shader.setMat4(shader.getUniformLocation(gl::ShaderUniform::VIEW),
            camera.viewMatrix);
    }
}
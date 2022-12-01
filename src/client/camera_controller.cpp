#include "client/camera_controller.hpp"
#include "client/io/input.hpp"
#include "client/application.hpp"

namespace nith
{
    void CameraController::connect(Camera* camera)
    {
        m_camera = camera;

        auto& dispatcher = io::Input::GetEventDispatcher();

        dispatcher.addEventListener<io::MouseMovedEvent>(
            [&](const io::MouseMovedEvent& event)
            {
                double pitch = m_camera->getPitch();
                double yaw = m_camera->getYaw();
                double deltaX = event.getMouseDeltaX();
                double deltaY = event.getMouseDeltaY();

                yaw += deltaX * m_sensitive;
                pitch -= deltaY * m_sensitive;

                m_camera->setOrientation(pitch, yaw);
                m_camera->updateViewMatrix();
            }
        );
    }

    void CameraController::update()
    {
        v3 position = m_camera->getPostion();

        if (io::Input::IsKeyPressed(io::KeyCode::W))
        {
            position += m_camera->getLookVector() * m_speed * Application::GetDeltaTime();
        }
        if (io::Input::IsKeyPressed(io::KeyCode::S))
        {
            position -= m_camera->getLookVector() * m_speed * Application::GetDeltaTime();
        }
        if (io::Input::IsKeyPressed(io::KeyCode::D))
        {
            position += m_camera->getRightVector() * m_speed * Application::GetDeltaTime();
        }
        if (io::Input::IsKeyPressed(io::KeyCode::A))
        {
            position -= m_camera->getRightVector() * m_speed * Application::GetDeltaTime();
        }
        if (io::Input::IsKeyPressed(io::KeyCode::Space))
        {
            position += Camera::YAxisVector * m_speed * Application::GetDeltaTime();
        }
        if (io::Input::IsKeyPressed(io::KeyCode::LeftShift))
        {
            position -= Camera::YAxisVector * m_speed * Application::GetDeltaTime();
        }

        m_camera->setPosition(position);
        m_camera->updateViewMatrix();
    }
}
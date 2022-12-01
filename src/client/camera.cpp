#include "client/camera.hpp"

namespace nith
{
    const v3 Camera::XAxisVector(1, 0, 0);
    const v3 Camera::YAxisVector(0, 1, 0);
    const v3 Camera::ZAxisVector(0, 0, 1);

    Camera::Camera(const f32& aspect, const f32& near, const f32& far):
        m_aspect(aspect),
        m_near(near),
        m_far(far),
        m_direction(0, 0, -1),
        m_position(0, 0, 0),
        m_upVector(0, 1, 0),
        m_lookVector(0, 0, -1),
        m_rightVector(1, 0, 0)
    {
        update_orientation();
    }

    void Camera::updateViewMatrix()
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_direction,
            YAxisVector);
        m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void Camera::updateProjectionViewMatrix()
    {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void Camera::update_direction()
    {
        m_direction.x = cos(m_yaw) * cos(m_pitch);
        m_direction.y = sin(m_pitch);
        m_direction.z = sin(m_yaw) * cos(m_pitch);

        update_vectors();
    }

    void Camera::update_orientation()
    {
        m_pitch = asin(m_direction.y);
        m_yaw = atan2(m_direction.z, m_direction.x);
        update_vectors();
    }

    void Camera::update_vectors()
    {
        m_rightVector = glm::normalize(glm::cross(m_direction, YAxisVector));
        m_lookVector = -glm::normalize(glm::cross(m_rightVector, YAxisVector));
    }
}
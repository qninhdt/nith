#include "client/renderer/perspective_camera.hpp"

namespace nith
{
    const v3 PerspectiveCamera::XAxisVector(1, 0, 0);
    const v3 PerspectiveCamera::YAxisVector(0, 1, 0);
    const v3 PerspectiveCamera::ZAxisVector(0, 0, 1);

    PerspectiveCamera::PerspectiveCamera(const f32& fov, const f32& aspect,
        const f32& near, const f32& far):
        m_fov(fov),
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
        updateProjectionViewMatrix();
    }

    void PerspectiveCamera::updateProjectionMatrix()
    {
        m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_near, m_far);
        m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void PerspectiveCamera::updateViewMatrix()
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_direction,
            YAxisVector);
        m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void PerspectiveCamera::updateProjectionViewMatrix()
    {
        updateProjectionMatrix();
        updateViewMatrix();
    }

    void PerspectiveCamera::update_direction()
    {
        m_direction.x = cos(m_yaw) * cos(m_pitch);
        m_direction.y = sin(m_pitch);
        m_direction.z = sin(m_yaw) * cos(m_pitch);

        update_vectors();
    }

    void PerspectiveCamera::update_orientation()
    {
        m_pitch = asin(m_direction.y);
        m_yaw = atan2(m_direction.z, m_direction.x);
        update_vectors();
    }

    void PerspectiveCamera::update_vectors()
    {
        m_rightVector = glm::normalize(glm::cross(m_direction, YAxisVector));
        m_lookVector = -glm::normalize(glm::cross(m_rightVector, YAxisVector));
    }
}
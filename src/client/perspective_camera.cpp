#include "client/perspective_camera.hpp"

namespace nith
{
    PerspectiveCamera::PerspectiveCamera(const f32& fov, const f32& aspect,
        const f32& near, const f32& far):
        m_fov(fov),
        Camera(aspect, near, far)
    {
        updateProjectionViewMatrix();
    }

    void PerspectiveCamera::updateProjectionMatrix()
    {
        m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_near, m_far);
        m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    }
}
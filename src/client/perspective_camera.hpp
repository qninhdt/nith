#pragma once

#include "client/camera.hpp"

namespace nith
{
    class PerspectiveCamera : public Camera
    {
    public:

        PerspectiveCamera(const f32& fov, const f32& aspect,
            const f32& near, const f32& far);

        f32 getFov() const { return m_fov; }
        f32 setFov(const f32& fov) { m_fov = fov; }

        void updateProjectionMatrix();
        
    private:
        f32 m_fov;
    };
}
#pragma once

#include "client/camera.hpp"

namespace nith
{
    class CameraController
    {
    public:
        CameraController(const f32& speed, const f32& sensitive):
            m_speed(speed),
            m_sensitive(sensitive),
            m_camera(nullptr)
        {}

        void connect(Camera* camera);
        void update();

    private:
        Camera* m_camera;
        f32 m_speed;
        f32 m_sensitive;
    };
}
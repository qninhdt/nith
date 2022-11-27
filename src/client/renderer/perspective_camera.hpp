#pragma once

namespace nith
{
    class PerspectiveCamera
    {
    public:

        static const v3 XAxisVector;
        static const v3 YAxisVector;
        static const v3 ZAxisVector;

        PerspectiveCamera(const f32& fov, const f32& aspect,
            const f32& near, const f32& far);

        const v3& getPostion() const { return m_position; }
        const v3& getDirection() const { return m_direction; }
        const mat4& getProjectionMaxtrix() const { return m_projectionMatrix; }
        const mat4& getViewMaxtrix() const { return m_viewMatrix; }
        const mat4& getProjectionViewMaxtrix() const { return m_projectionViewMatrix; }
        f32 getAspect() const { return m_aspect; }
        f32 getYaw() const { return m_yaw; }
        f32 getPitch() const { return m_pitch; }
        f32 getFov() const { return m_fov; }

        void setPosition(const v3& position) { m_position = position; }
        f32 setAspect(const f32& aspect) { m_aspect = aspect; }
        f32 setYaw(const f32& yaw) { m_yaw = yaw; updateDirection(); }
        f32 setPitch(const f32& pitch) { m_pitch = pitch; updateDirection(); }
        
        f32 setOrientation(const f32& pitch, const f32& yaw) 
        {
            m_pitch = std::min(std::max(pitch, -89.0f), +89.0f);
            m_yaw = yaw;

            updateDirection();
        }

        f32 setFov(const f32& fov) { m_fov = fov; }

        void updateProjectionMatrix();
        void updateViewMatrix();
        void updateProjectionViewMatrix();
        
    private:

        void updateDirection();

        v3 m_position;
        v3 m_direction;
        f32 m_yaw;
        f32 m_pitch;
        f32 m_aspect;
        f32 m_fov;
        f32 m_near;
        f32 m_far;
        f32 m_zoom;
        v3 m_upVector;
        v3 m_lookVector;
        v3 m_rightVector;
        mat4 m_projectionMatrix;
        mat4 m_viewMatrix;
        mat4 m_projectionViewMatrix;
    };
}
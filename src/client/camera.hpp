#pragma once

namespace nith
{
    class Camera
    {
    public:

        static const v3 XAxisVector;
        static const v3 YAxisVector;
        static const v3 ZAxisVector;

        Camera(const f32& aspect, const f32& near, const f32& far);

        const v3& getPostion() const { return m_position; }
        const v3& getDirection() const { return m_direction; }
        const mat4& getProjectionMaxtrix() const { return m_projectionMatrix; }
        const mat4& getViewMaxtrix() const { return m_viewMatrix; }
        const mat4& getProjectionViewMaxtrix() const { return m_projectionViewMatrix; }
        f32 getAspect() const { return m_aspect; }
        f32 getYaw() const { return m_yaw; }
        f32 getPitch() const { return m_pitch; }

        void setPosition(const v3& position) { m_position = position; }
        f32 setAspect(const f32& aspect) { m_aspect = aspect; }
        f32 setYaw(const f32& yaw) { m_yaw = yaw; update_direction(); }
        f32 setPitch(const f32& pitch) { m_pitch = pitch; update_direction(); }

        void setOrientation(const f32& pitch, const f32& yaw)
        {
            m_pitch = std::min(std::max(pitch, -3.14f / 2), +3.14f / 2);
            m_yaw = yaw;

            update_direction();
        }

        void setDirection(const v3& direction) {
            m_direction = glm::normalize(direction);
            update_orientation();
        }

        virtual void updateProjectionMatrix() = 0;
        void updateViewMatrix();
        void updateProjectionViewMatrix();

    protected:

        void update_direction();

        void update_orientation();

        void update_vectors();

        v3 m_position;
        v3 m_direction;
        f32 m_yaw;
        f32 m_pitch;
        f32 m_aspect;
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
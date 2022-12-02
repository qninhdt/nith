#pragma once

namespace nith
{
    class Object
    {
    public:
        Object() {}

        const v3& getPostion() const { return m_position; }
        const v3& getRotation() const { return m_rotation; }
        const v3& getDirection();

        void setPosition(const v3& position) { m_position = position; }
        void setRotation(const v3& rotation) { rotation = rotation; }
        void setDirection(const v3& direction);

    private:
        v3 m_position;
        v3 m_rotation;
    };
}
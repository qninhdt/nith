#pragma once

namespace nith
{
    struct Transform
    {
        v3 position = { 0, 0, 0 };
        v3 rotation = { 0, 0, 0 };
        v3 scale = { 1,1,1 };

        v3 getDirection() const
        {
            return {
                sin(rotation.y) * cos(rotation.x),
                sin(rotation.x),
                cos(rotation.y) * cos(rotation.x),
            };
        }

        void setDirection(const v3& direction)
        {
            rotation.x = asin(direction.y);
            rotation.y = atan2(direction.x, direction.z);
        }
    };
}
#pragma once

namespace nith
{
    class DebugObject
    {
    public:
        DebugObject():
            debugName("")
        {}

        std::string debugName;

        virtual void toString(std::ostream& output) const = 0;
    };
}

inline std::ostream& operator<< (std::ostream& output, const nith::DebugObject& object)
{
    object.toString(output);
    return output;
}
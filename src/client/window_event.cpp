#include "client/window_event.hpp"
#include "client/window.hpp"

namespace nith
{
    void WindowClosedEvent::toString(std::ostream& output) const
    {
        output << "WindowClosedEvent {}";
    }

    void WindowResizedEvent::toString(std::ostream& output) const
    {
        output << "WindowResizedEvent { width = " << m_width << ", height = " << m_height << " }";
    }

    void WindowMovedEvent::toString(std::ostream& output) const
    {
        output << "WindowMovedEvent { posX = " << m_posX << ", posY = " << m_posY << " }";
    }
}
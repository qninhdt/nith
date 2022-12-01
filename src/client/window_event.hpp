#pragma once

#include "event.hpp"

namespace nith
{
    class Window;

    enum class WindowEventType
    {
        None = 0,
        WindowResized,
        WindowMoved,
        WindowClosed,
        WindowFocused,
        WindowLostFocused
    };

    class WindowEvent : public Event<WindowEventType>
    {
    public:
        inline const Window& getWindow() const
        {
            return m_window;
        }
    protected:
        WindowEvent(const WindowEventType& eventType, Window& window):
            Event(eventType),
            m_window(window)
        {}
    private:
        Window& m_window;
    };

    class WindowClosedEvent : public WindowEvent
    {
    public:
        WindowClosedEvent(Window& window):
            WindowEvent(WindowEventType::WindowClosed, window)
        {}

        void toString(std::ostream& output) const override;

        NITH_EVENT_CLASS(WindowEventType, WindowClosed)
    };

    class WindowResizedEvent : public WindowEvent
    {
    public:
        WindowResizedEvent(Window& window, u32 width, u32 height):
            WindowEvent(WindowEventType::WindowResized, window),
            m_width(width),
            m_height(height)
        {}

        inline u32 getWidth() const
        {
            return m_width;
        }

        inline u32 getHeight() const
        {
            return m_height;
        }

        void toString(std::ostream& output) const override;

        NITH_EVENT_CLASS(WindowEventType, WindowResized)

    private:
        u32 m_width, m_height;
    };

    class WindowMovedEvent : public WindowEvent
    {
    public:
        WindowMovedEvent(Window& window, u32 posX, u32 posY) :
            WindowEvent(WindowEventType::WindowMoved, window),
            m_posX(posX),
            m_posY(posY)
        {}

        inline u32 getPosX() const
        {
            return m_posX;
        }

        inline u32 getPosY() const
        {
            return m_posY;
        }

        void toString(std::ostream& output) const override;

        NITH_EVENT_CLASS(WindowEventType, WindowMoved)

    private:
        u32 m_posX, m_posY;
    };

    using WindowEventDispatcher = EventDispatcher<WindowEventType>;
}
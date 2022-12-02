#pragma once

#include "event.hpp"
#include "io/input_defs.hpp"

namespace nith::io
{
    enum class InputEventType
    {
        None = 0,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseMoved,
        MouseClicked
    };

    class InputEvent : public Event<InputEventType>
    {
    public:
        InputEvent(const InputEventType& type):
            Event(type)
        {}
    };

    class MouseEvent : public InputEvent
    {
    public:
        MouseEvent(const InputEventType& type, const f32& mouseX, const f32& mouseY) :
            InputEvent(type),
            m_mouseX(mouseX),
            m_mouseY(mouseY)
        {}

        f32 getMouseX() const { return m_mouseX; }
        f32 getMouseY() const { return m_mouseY; }
    private:
        f32 m_mouseX;
        f32 m_mouseY;
    };

    class KeyEvent : public InputEvent
    {
    public:
        KeyEvent(const InputEventType& type, const KeyCode& keyCode):
            InputEvent(type),
            m_keyCode(keyCode)
        {}

        KeyCode getKeyCode() const { return m_keyCode; }
    private:
        KeyCode m_keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode& keyCode, const bool& isRepeat):
            KeyEvent(InputEventType::KeyPressed, keyCode),
            m_isRepeat(isRepeat)
        {}

        bool isRepeat() const { return m_isRepeat; }

        NITH_EVENT_CLASS(InputEventType, KeyPressed)
    private:
        bool m_isRepeat;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode& keyCode) :
            KeyEvent(InputEventType::KeyReleased, keyCode)
        {}

        NITH_EVENT_CLASS(InputEventType, KeyReleased)
    };

    class MouseMovedEvent : public MouseEvent
    {
    public:
        MouseMovedEvent(const f32& mouseX, const f32& mouseY,
            const f32& mouseDeltaX, const f32& mouseDeltaY):
            MouseEvent(InputEventType::MouseMoved, mouseX, mouseY),
            m_mouseDeltaX(mouseDeltaX),
            m_mouseDeltaY(mouseDeltaY)
        {}

        f32 getMouseDeltaX() const { return m_mouseDeltaX; }
        f32 getMouseDeltaY() const { return m_mouseDeltaY; }

        NITH_EVENT_CLASS(InputEventType, MouseMoved)
    private:
        f32 m_mouseDeltaX;
        f32 m_mouseDeltaY;
    };

    using InputEventDispatcher = EventDispatcher<InputEventType>;
}
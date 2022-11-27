#pragma once

#include "event.hpp"
#include "client/io/input_defs.hpp"

namespace nith::io
{
    enum class InputEventType
    {
        None = 0,
        KeyPressed,
        KeyReleased,
        KeyTyped,
    };

    class InputEvent : public Event<InputEventType>
    {
    public:
        InputEvent(const InputEventType& type):
            Event(type)
        {}
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

        void toString(std::ostream& output) const
        {
            output << "KeyPressedEvent { keyCode = " << (u32) getKeyCode() << " isRepeat = " << (m_isRepeat ? "true" : "false") << " }";
        }

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

        void toString(std::ostream& output) const
        {
            output << "KeyReleasedEvent { keyCode = " << (u32)getKeyCode() << " }";
        }

        NITH_EVENT_CLASS(InputEventType, KeyReleased)
    };

    using InputEventDispatcher = EventDispatcher<InputEventType>;
}
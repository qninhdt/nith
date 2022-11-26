#pragma once

namespace nith
{
    template<typename E>
    class Event: public DebugObject
    {
    public:
        Event(const E& eventType):
            m_eventType(eventType)
        {}

        virtual E getEventType() const = 0;
        virtual std::string getName() const = 0;
    private:
        E m_eventType;
    };

#define NITH_EVENT_CLASS(enum_type, type) \
    static inline enum_type GetStaticEventType() { return enum_type::type; }\
    virtual enum_type getEventType() const override { return GetStaticEventType(); }\
	virtual std::string getName() const override { return #type; }

    template<typename EE, typename E>
    class EventDispatcher
    {
    public:
        template<typename T>
        void addEventListener(std::function<void(const T&)> callback)
        {
            m_dispatcher.appendListener(T::GetStaticEventType(),
                [=](const E& event) { callback((T&)event); });
        }

        template<typename T>
        void dispatchEvent(const T& event)
        {
            m_dispatcher.dispatch(T::GetStaticEventType(), event);
        }

    private:
         eventpp::EventDispatcher<EE, void(const E&)> m_dispatcher;
    };
}
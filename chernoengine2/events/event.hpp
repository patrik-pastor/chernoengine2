//
// Created by shepherd on 8.3.23.
//

#ifndef CHERNOENGINE2_EVENT_HPP
#define CHERNOENGINE2_EVENT_HPP

#include <string>

#include <chernoengine2/core/core.hpp>

namespace chernoengine2 {

enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory {
    NONE = 1,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                                                                EventType GetEventType() const override { return GetStaticType(); } \
                                                                const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return category; }

class Event {
public:
    virtual ~Event() = default;

    virtual const char *GetName() const = 0;

    virtual EventType GetEventType() const = 0;

    virtual int GetCategoryFlags() const = 0;

    virtual std::string ToString() const;

    bool IsInCategory(EventCategory category) const;

    bool handled_ = false;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) {
    return os << e.ToString();
}

class EventDispatcher {
public:
    explicit EventDispatcher(Event &event);

    template<typename T, typename F>
    bool Dispatch(const F &func) {
        if (event_.GetEventType() == T::GetStaticType()) {
            event_.handled_ |= func(static_cast<T &>(event_));
            return true;
        }
        return false;
    }

private:
    Event &event_;
};

} // chernoengine2

#endif //CHERNOENGINE2_EVENT_HPP

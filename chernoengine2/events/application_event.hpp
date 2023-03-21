//
// Created by shepherd on 8.3.23.
//

#ifndef CHERNOENGINE2_APPLICATION_EVENT_HPP
#define CHERNOENGINE2_APPLICATION_EVENT_HPP

#include <chernoengine2/events/event.hpp>

namespace chernoengine2 {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(int width, int height);

    int GetWidth() const;

    int GetHeight() const;

    std::string ToString() const override;

    EVENT_CLASS_TYPE(WindowResize);

    EVENT_CLASS_CATEGORY(EventCategoryApplication)

private:
    int width_, height_;
};

class WindowCloseEvent : public Event {
public:
    EVENT_CLASS_TYPE(WindowClose);

    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

} // chernoengine2

#endif //CHERNOENGINE2_APPLICATION_EVENT_HPP

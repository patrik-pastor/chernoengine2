//
// Created by shepherd on 8.3.23.
//

#include <chernoengine2/events/event.hpp>

namespace chernoengine2 {

bool Event::IsInCategory(EventCategory category) const {
    return GetCategoryFlags() & category;
}

std::string Event::ToString() const {
    return GetName();
}

EventDispatcher::EventDispatcher(Event &event) : event_(event) {}

} // chernoengine2
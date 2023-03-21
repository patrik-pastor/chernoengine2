//
// Created by shepherd on 8.3.23.
//

#include <chernoengine2/events/mouse_event.hpp>

#include <sstream>

namespace chernoengine2 {

int MouseButtonEvent::GetMouseButton() const {
    return button_;
}

MouseButtonEvent::MouseButtonEvent(int button) : button_(button) {}

MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

std::string MouseButtonPressedEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << button_ << '\n';
    return ss.str();
}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

std::string MouseButtonReleasedEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << button_ << '\n';
    return ss.str();
}

MouseScrolledEvent::MouseScrolledEvent(double xoffset, double yoffset) : xoffset_(xoffset), yoffset_(yoffset) {}

double MouseScrolledEvent::GetXoffset() const {
    return xoffset_;
}

double MouseScrolledEvent::GetYoffset() const {
    return yoffset_;
}

std::string MouseScrolledEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << GetXoffset() << ", " << GetYoffset() << '\n';
    return ss.str();
}

MouseMovedEvent::MouseMovedEvent(double xpos, double ypos) : xpos(xpos), ypos(ypos) {}

double MouseMovedEvent::GetXpos() const {
    return xpos;
}

double MouseMovedEvent::GetYpos() const {
    return ypos;
}

std::string MouseMovedEvent::ToString() const {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << GetXpos() << ", " << GetYpos() << '\n';
    return ss.str();
}

} // chernoengine2
//
// Created by shepherd on 8.3.23.
//

#include <chernoengine2/events/application_event.hpp>

#include <sstream>

namespace chernoengine2 {

WindowResizeEvent::WindowResizeEvent(int width, int height) : width_(width), height_(height) {}

std::string WindowResizeEvent::ToString() const {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << width_ << ", " << height_;
    return ss.str();
}

int WindowResizeEvent::GetWidth() const {
    return width_;
}

int WindowResizeEvent::GetHeight() const {
    return height_;
}

} // chernoengine2
//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/core/window.hpp>
#include <chernoengine2/core/linux_window.hpp>

namespace chernoengine2 {

WindowProps::WindowProps(const std::string& title, int width, int height) : title(title), width(width),
                                                                            height(height) {}

Window *Window::Create(const WindowProps& props) {
    return new LinuxWindow(props);
}

} // chernoengine2
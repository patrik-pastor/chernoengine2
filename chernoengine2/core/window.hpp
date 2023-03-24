//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_WINDOW_HPP
#define CHERNOENGINE2_WINDOW_HPP

#include <string>
#include <functional>

#include <chernoengine2/events/event.hpp>

namespace chernoengine2 {

struct WindowProps {
    std::string title;
    int width;
    int height;

    explicit WindowProps(const std::string& title = "chernoengine2", int width = 1600, int height = 900);
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    static Window *Create(const WindowProps& props = WindowProps());

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual int GetWidth() const = 0;

    virtual int GetHeight() const = 0;

    virtual void SetVSync(bool enabled) = 0;

    virtual void *GetNativeWindow() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
};

} // chernoengine2

#endif //CHERNOENGINE2_WINDOW_HPP

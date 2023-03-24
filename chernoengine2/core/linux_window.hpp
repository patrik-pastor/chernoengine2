//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_LINUX_WINDOW_HPP
#define CHERNOENGINE2_LINUX_WINDOW_HPP

#include <chernoengine2/core/window.hpp>
#include <chernoengine2/renderer/graphics_context.hpp>

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace chernoengine2 {

class LinuxWindow : public Window {
public:
    explicit LinuxWindow(const WindowProps& props);

    ~LinuxWindow() override = default;

    void OnUpdate() override;

    int GetWidth() const override;

    int GetHeight() const override;

    void SetVSync(bool enabled) override;

    void *GetNativeWindow() const override;

    void SetEventCallback(const EventCallbackFn& callback) override;
private:
    GLFWwindow *window_;
    GraphicsContext *context_;
    struct WindowData {
        std::string title;
        int width;
        int height;
        bool vsync;
        EventCallbackFn event_callback;
    } data_;
};

} // chernoengine2

#endif //CHERNOENGINE2_LINUX_WINDOW_HPP

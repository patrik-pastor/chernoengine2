//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_APPLICATION_HPP
#define CHERNOENGINE2_APPLICATION_HPP

#include <chernoengine2/core/window.hpp>
#include <chernoengine2/events/event.hpp>
#include <chernoengine2/events/application_event.hpp>
#include <chernoengine2/core/layer_stack.hpp>
#include <chernoengine2/renderer/shader.hpp>
#include <chernoengine2/renderer/buffer.hpp>
#include <chernoengine2/imgui/imgui_layer.hpp>

namespace chernoengine2 {

class Application {
public:
    Application();

    void Run();

    void OnEvent(Event& e);

    bool IsRunning() const;

    void SetRunning(bool running);

    void PushLayer(Layer *layer);

    void PushOverlay(Layer *layer);

    static Application& GetInstance();

    Window &GetWindow() const;

private:
    static Application *application_instance_;

    bool OnWindowClose(WindowCloseEvent& e);

    Window *window_;
    bool running_ = true;
    LayerStack layer_stack_;
    ImguiLayer *imgui_layer_;

    uint32_t va_;
    std::unique_ptr<Shader> shader_;
    VertexBuffer *vb_;
    IndexBuffer *ib_;
};

} // chernoengine2

#endif //CHERNOENGINE2_APPLICATION_HPP

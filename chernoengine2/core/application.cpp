//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/core/application.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

Application *Application::application_instance_ = nullptr;

Application::Application(){
    PROFILE_FUNCTION();
    INIT_LOG();

    if (application_instance_ != nullptr) {
        LOG_CORE_CRITICAL("Application already exists!");
    }
    application_instance_ = this;

    window_ = Window::Create();
    window_->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();

    imgui_layer_ = new ImguiLayer();
    PushOverlay(imgui_layer_);
}

void Application::Run() {
    PROFILE_FUNCTION();

    while (IsRunning()) {
        float time = glfwGetTime();
        float delta_time = time - last_time_;
        last_time_ = time;

        {
            PROFILE_SCOPE("LayerStack OnUpdate");
            for (Layer *layer: layer_stack_) {
                layer->OnUpdate(delta_time);
            }
        }

        imgui_layer_->Begin();
        {
            PROFILE_SCOPE("LayerStack OnImGuiRenderer");
            for (Layer *layer: layer_stack_)
                layer->OnImguiRender();
        }
        imgui_layer_->End();

        window_->OnUpdate();
    }
}

void Application::OnEvent(Event& e) {
    PROFILE_FUNCTION();

    LOG_CORE_INFO(e.ToString());
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = layer_stack_.end(); it != layer_stack_.begin();) {
        (*--it)->OnEvent(e);
        if (e.handled_) {
            break;
        }
    }
}

bool Application::IsRunning() const {
    return running_;
}

void Application::SetRunning(bool running) {
    running_ = running;
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    SetRunning(false);
    return true;
}

void Application::PushLayer(Layer *layer) {
    PROFILE_FUNCTION();

    layer_stack_.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
    PROFILE_FUNCTION();

    layer_stack_.PushOverlay(layer);
    layer->OnAttach();
}

Application& Application::GetInstance() {
    return *application_instance_;
}

Window& Application::GetWindow() const {
    return *window_;
}

} // chernoengine2
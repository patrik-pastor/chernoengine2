//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/core/application.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/shader.hpp>
#include <memory>

namespace chernoengine2 {

Application *Application::application_instance_ = nullptr;

Application::Application() {
    Log::Init();

    if (application_instance_ != nullptr) {
        LOG_CORE_CRITICAL("Application already exists!");
    }
    application_instance_ = this;

    window_ = Window::Create();
    window_->SetEventCallback(BIND_EVENT_FN(OnEvent));

    glGenVertexArrays(1, &va_);
    glBindVertexArray(va_);

    glGenBuffers(1, &vb_);
    glBindBuffer(GL_ARRAY_BUFFER, vb_);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &ib_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);

    int indices[] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader_ = std::make_unique<Shader>("GLSL/main.vs", "GLSL/main.fs");
}

void Application::Run() {
    while (IsRunning()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_->Bind();
        glBindVertexArray(va_);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        for(Layer *layer : layer_stack_){
            layer->OnUpdate();
        }

        window_->OnUpdate();
    }
}

void Application::OnEvent(Event& e) {
    LOG_CORE_INFO(e.ToString());
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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
    layer_stack_.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
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
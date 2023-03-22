//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/core/application.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/shader.hpp>
#include <chernoengine2/opengl/opengl_buffer.hpp>
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

    imgui_layer_ = new ImguiLayer;
    PushOverlay(imgui_layer_);

    glGenVertexArrays(1, &va_);
    glBindVertexArray(va_);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    vb_ = VertexBuffer::Create(vertices, sizeof(vertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    int indices[] = {0, 1, 2};
    ib_ = IndexBuffer::Create(indices, 3);

    shader_ = std::make_unique<Shader>("GLSL/main.shader");
}

void Application::Run() {
    while (IsRunning()) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_->Bind();
        glBindVertexArray(va_);
        glDrawElements(GL_TRIANGLES, ib_->GetCount(), GL_UNSIGNED_INT, nullptr);

        for (Layer *layer: layer_stack_) {
            layer->OnUpdate();
        }

        imgui_layer_->Begin();
        for (Layer *layer: layer_stack_)
            layer->OnImguiRender();
        imgui_layer_->End();

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
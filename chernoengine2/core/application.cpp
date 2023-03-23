//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/core/application.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/renderer.hpp>

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

    va_ = VertexArray::Create();

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    vb_ = VertexBuffer::Create(vertices, sizeof(vertices));
    {
        BufferLayout layout = {
                {"a_pos",   ShaderDataType::Float3},
                {"a_color", ShaderDataType::Float4}
        };
        vb_->SetLayout(layout);
    }
    va_->AddVertexBuffer(vb_);

    int indices[] = {0, 1, 2};
    ib_ = IndexBuffer::Create(indices, 3);
    va_->SetIndexBuffer(ib_);

    shader_ = new Shader("GLSL/main.shader");
}

void Application::Run() {
    while (IsRunning()) {

        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        RenderCommand::Clear();

        shader_->Bind();
        Renderer::Submit(va_);

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
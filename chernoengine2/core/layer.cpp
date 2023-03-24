//
// Created by shepherd on 9.3.23.
//

#include <chernoengine2/core/layer.hpp>

#include <chernoengine2/core/core.hpp>
#include <chernoengine2/core/key_codes.hpp>
#include <chernoengine2/core/log.hpp>
#include <chernoengine2/core/input.hpp>
#include <chernoengine2/events/key_event.hpp>

namespace chernoengine2 {

Layer::Layer(const std::string& name) : name_(name) {}

FirstExample::FirstExample() :
        Layer("FirstExample"),
        camera_(-2.0f, 2.0f, -2.0f, 2.0f),
        camera_position_(0.0f) {
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

void FirstExample::OnUpdate() {
    if (Input::IsKeyPressed(KEY_LEFT)) {
        camera_position_.x -= camera_move_speed_;
    } else if (Input::IsKeyPressed(KEY_RIGHT)) {
        camera_position_.x += camera_move_speed_;
    }
    if (Input::IsKeyPressed(KEY_UP)) {
        camera_position_.y += camera_move_speed_;
    } else if (Input::IsKeyPressed(KEY_DOWN)) {
        camera_position_.y -= camera_move_speed_;
    }
    if(Input::IsKeyPressed(KEY_A)){
        camera_rotation_ += camera_rotation_speed_;
    }
    if(Input::IsKeyPressed(KEY_D)){
        camera_rotation_ -= camera_rotation_speed_;
    }

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    camera_.SetPosition(camera_position_);
    camera_.SetRotation(camera_rotation_);

    Renderer::BeginScene(camera_);
    Renderer::Submit(shader_, va_);
    Renderer::EndScene();
}

} // chernoengine22
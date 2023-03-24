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

    // TRIANGLE
    triangle_va_ = VertexArray::Create();
    float triangle_vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    triangle_vb_ = VertexBuffer::Create(triangle_vertices, sizeof(triangle_vertices));
    BufferLayout layout = {
            {"a_pos",   ShaderDataType::Float3},
            {"a_color", ShaderDataType::Float4}
    };
    triangle_vb_->SetLayout(layout);
    triangle_va_->AddVertexBuffer(triangle_vb_);
    int triangle_indices[] = {0, 1, 2};
    triangle_ib_ = IndexBuffer::Create(triangle_indices, 3);
    triangle_va_->SetIndexBuffer(triangle_ib_);
    triangle_shader_ = new Shader("GLSL/triangle.shader");

    //SQUARE
    square_va_ = VertexArray::Create();
    float square_vertices[] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f
    };
    square_vb_ = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
    square_vb_->SetLayout({
                                  {"a_pos", ShaderDataType::Float3}
                          });
    square_va_->AddVertexBuffer(square_vb_);
    int square_indices[] = {0, 1, 2, 2, 3, 0};
    square_ib_ = IndexBuffer::Create(square_indices, 6);
    square_va_->SetIndexBuffer(square_ib_);
    square_shader_ = new Shader("GLSL/square.shader");

}

void FirstExample::OnUpdate(float delta_time) {
    if (Input::IsKeyPressed(KEY_LEFT)) {
        camera_position_.x -= camera_move_speed_ * delta_time;
    } else if (Input::IsKeyPressed(KEY_RIGHT)) {
        camera_position_.x += camera_move_speed_ * delta_time;
    }
    if (Input::IsKeyPressed(KEY_UP)) {
        camera_position_.y += camera_move_speed_ * delta_time;
    } else if (Input::IsKeyPressed(KEY_DOWN)) {
        camera_position_.y -= camera_move_speed_ * delta_time;
    }
    if (Input::IsKeyPressed(KEY_A)) {
        camera_rotation_ += camera_rotation_speed_ * delta_time;
    }
    if (Input::IsKeyPressed(KEY_D)) {
        camera_rotation_ -= camera_rotation_speed_ * delta_time;
    }

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    camera_.SetPosition(camera_position_);
    camera_.SetRotation(camera_rotation_);

    Renderer::BeginScene(camera_);
    Renderer::Submit(square_shader_, square_va_);
    Renderer::Submit(triangle_shader_, triangle_va_);
    Renderer::EndScene();
}

} // chernoengine22
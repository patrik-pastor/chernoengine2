//
// Created by shepherd on 29.3.23.
//

#include <chernoengine2/main/example_layers/second_example.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace chernoengine2 {

SecondExample::SecondExample() :
        camera_controller_(1280.0f / 720.0f) {}

void SecondExample::OnAttach() {
    square_va_ = VertexArray::Create();
    float square_vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
    };
    Ref<VertexBuffer> square_vb = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
    square_vb->SetLayout({
                                 {"a_pos", ShaderDataType::Float3},
                         });
    square_va_->AddVertexBuffer(square_vb);
    int square_indices[] = {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> square_ib = IndexBuffer::Create(square_indices, 6);
    square_va_->SetIndexBuffer(square_ib);
    square_shader_ = Shader::Create("GLSL/2e_square.glsl");
}

void SecondExample::OnDetach() {
    Layer::OnDetach();
}

void SecondExample::OnUpdate(float delta_time) {
    // update
    camera_controller_.OnUpdate(delta_time);

    // renderer
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    Renderer::BeginScene(camera_controller_.GetCamera());

    square_shader_->Bind();
    square_shader_->SetVec3("u_color", square_color_);

    Renderer::Submit(square_shader_, square_va_);

    Renderer::EndScene();
}

void SecondExample::OnImguiRender() {
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));

    ImGui::End();
}

void SecondExample::OnEvent(Event& event) {
    camera_controller_.OnEvent(event);
}


} // chernoengine2
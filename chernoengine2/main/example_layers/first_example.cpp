//
// Created by shepherd on 29.3.23.
//

#include <chernoengine2/main/example_layers/first_example.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace chernoengine2 {

FirstExample::FirstExample() :
        Layer("FirstExample"),
        camera_controller_(1280.0f / 720.0f, false),
        square_color_(0.2f, 0.3f, 0.8f) {

//    // TRIANGLE
//    triangle_va_ = VertexArray::Create();
//    float triangle_vertices[] = {
//            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
//    };
//    Ref<VertexBuffer> triangle_vb = VertexBuffer::Create(triangle_vertices, sizeof(triangle_vertices));
//    BufferLayout layout = {
//            {"a_pos",   ShaderDataType::Float3},
//            {"a_color", ShaderDataType::Float4}
//    };
//    triangle_vb->SetLayout(layout);
//    triangle_va_->AddVertexBuffer(triangle_vb);
//    int triangle_indices[] = {0, 1, 2};
//    Ref<IndexBuffer> triangle_ib = IndexBuffer::Create(triangle_indices, 3);
//    triangle_va_->SetIndexBuffer(triangle_ib);
//    triangle_shader_ = Shader::Create("GLSL/1e_triangle.glsl");

    // SQUARE
    square_va_ = VertexArray::Create();
    float square_vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };
    Ref<VertexBuffer> square_vb = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
    square_vb->SetLayout({
                                 {"a_pos", ShaderDataType::Float3},
                                 {"a_texcoord", ShaderDataType::Float2}
                         });
    square_va_->AddVertexBuffer(square_vb);
    int square_indices[] = {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> square_ib = IndexBuffer::Create(square_indices, 6);
    square_va_->SetIndexBuffer(square_ib);
    square_shader_ = Shader::Create("GLSL/1e_square.glsl");

    // TEXTURES
    chessboard_shader_ = Shader::Create("GLSL/1e_texture.glsl");
    chessboard_shader_->Bind();
    chessboard_shader_->SetInt("u_texture", 0);
    chessboard_texture_ = Texture2D::Create("textures/checkerboard.png");

    chernologo_texture_ = Texture2D::Create("textures/chernologo.png");
}

void FirstExample::OnUpdate(float delta_time) {

    // update
    camera_controller_.OnUpdate(delta_time);

    // render
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    Renderer::BeginScene(camera_controller_.GetCamera());

    square_shader_->Bind();
    square_shader_->SetVec3("u_color", square_color_);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Renderer::Submit(square_shader_, square_va_, transform);
        }
    }

    chessboard_texture_->Bind();
    Renderer::Submit(chessboard_shader_, square_va_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    chernologo_texture_->Bind();
    Renderer::Submit(chessboard_shader_, square_va_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Renderer::EndScene();
}

void FirstExample::OnImguiRender() {
    ImGui::Begin("Settings");

    ImGui::ColorEdit3("Square Color", glm::value_ptr(square_color_));

    ImGui::End();
}

void FirstExample::OnEvent(Event& event) {
    camera_controller_.OnEvent(event);
}

} // chernoengine2
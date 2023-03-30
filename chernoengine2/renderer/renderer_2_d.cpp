//
// Created by shepherd on 30.3.23.
//

#include <chernoengine2/renderer/renderer_2_d.hpp>

#include <chernoengine2/core/core.hpp>
#include <chernoengine2/renderer/vertex_array.hpp>
#include <chernoengine2/renderer/shader.hpp>
#include <chernoengine2/renderer/render_command.hpp>

namespace chernoengine2 {

struct Renderer2DStorage {
    Ref<VertexArray> quad_va;
    Ref<Shader> flat_color_shader;
};

static Renderer2DStorage *data;

void Renderer2D::Init() {
    data = new Renderer2DStorage;
    data->quad_va = VertexArray::Create();
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
    data->quad_va->AddVertexBuffer(square_vb);
    int square_indices[] = {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> square_ib = IndexBuffer::Create(square_indices, 6);
    data->quad_va->SetIndexBuffer(square_ib);
    data->flat_color_shader = Shader::Create("GLSL/2e_flat_color.glsl");
}

void Renderer2D::Shutdown() {
    delete data;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
    data->flat_color_shader->Bind();
    data->flat_color_shader->SetMat4("u_view_projection", camera.GetViewProjectionMatrix());
    data->flat_color_shader->SetMat4("u_transform", glm::mat4(1.0f));
}

void Renderer2D::EndScene() {

}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    data->flat_color_shader->Bind();
    data->flat_color_shader->SetVec4("u_color", color);
    data->quad_va->Bind();
    RenderCommand::DrawIndexed(data->quad_va);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}


} // chernoengine2
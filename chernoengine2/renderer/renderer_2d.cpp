//
// Created by shepherd on 30.3.23.
//

#include <chernoengine2/renderer/renderer_2d.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <chernoengine2/renderer/render_command.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

static Renderer2DStorage *data;

void Renderer2D::Init() {
    PROFILE_FUNCTION();

    data = new Renderer2DStorage;
    data->quad_va = VertexArray::Create();
    float square_vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };
    Ref<VertexBuffer> square_vb = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
    square_vb->SetLayout({
                                 {"a_pos",      ShaderDataType::Float3},
                                 {"a_texcoord", ShaderDataType::Float2}
                         });
    data->quad_va->AddVertexBuffer(square_vb);
    int square_indices[] = {0, 1, 2, 2, 3, 0};
    Ref<IndexBuffer> square_ib = IndexBuffer::Create(square_indices, 6);
    data->quad_va->SetIndexBuffer(square_ib);
    data->white_texture_ = Texture2D::Create(1, 1);
    uint32_t white_texture_data = 0xffffffff;
    data->white_texture_->SetData(&white_texture_data);

    data->texture_shader = Shader::Create("assets/GLSL/texture_and_color.glsl");
    data->texture_shader->Bind();
    data->texture_shader->SetInt("u_texture", 0);
}

void Renderer2D::Shutdown() {
    PROFILE_FUNCTION();

    delete data;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
    PROFILE_FUNCTION();

    data->texture_shader->Bind();
    data->texture_shader->SetMat4("u_view_projection", camera.GetViewProjectionMatrix());
}

void Renderer2D::EndScene() {
    PROFILE_FUNCTION();
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    PROFILE_FUNCTION();

    data->texture_shader->SetVec4("u_color", color);
    data->texture_shader->SetFloat("u_tiling_factor", 1.0f);
    data->white_texture_->Bind();
    glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    data->texture_shader->SetMat4("u_transform", transform);
    data->quad_va->Bind();
    RenderCommand::DrawIndexed(data->quad_va);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                          float tiling_factor, const glm::vec4& tint_color) {
    PROFILE_FUNCTION();

    data->texture_shader->SetVec4("u_color", tint_color);
    data->texture_shader->SetFloat("u_tiling_factor", tiling_factor);
    texture->Bind();
    glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    data->texture_shader->SetMat4("u_transform", transform);
    data->quad_va->Bind();
    RenderCommand::DrawIndexed(data->quad_va);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                          float tiling_factor, const glm::vec4& tint_color) {
    DrawQuad({position.x, position.y, 0.0f}, size, texture, tiling_factor, tint_color);
}

void
Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    PROFILE_FUNCTION();

    data->texture_shader->SetVec4("u_color", color);
    data->texture_shader->SetFloat("u_tiling_factor", 1.0f);
    data->white_texture_->Bind();
    glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    data->texture_shader->SetMat4("u_transform", transform);
    data->quad_va->Bind();
    RenderCommand::DrawIndexed(data->quad_va);
}

void
Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                 const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color) {
    PROFILE_FUNCTION();

    data->texture_shader->SetVec4("u_color", tint_color);
    data->texture_shader->SetFloat("u_tiling_factor", tiling_factor);
    texture->Bind();
    glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
            * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    data->texture_shader->SetMat4("u_transform", transform);
    data->quad_va->Bind();
    RenderCommand::DrawIndexed(data->quad_va);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                 const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color) {
    DrawRotatedQuad({position.x, position.y, 0}, size, rotation, texture, tiling_factor, tint_color);
}


} // chernoengine2
//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/renderer/renderer.hpp>

namespace chernoengine2 {

void Renderer::Init() {
    RenderCommand::Init();
}

Scope<Renderer::SceneData> Renderer::scene_data_ = CreateScope<Renderer::SceneData>();

RendererApi::Api Renderer::GetRendererApi() {
    return RendererApi::GetApi();
}

void Renderer::BeginScene(const OrthographicCamera& camera) {
    scene_data_->view_projection_matrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {

}

void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform) {
    shader->Bind();
    shader->SetMat4("u_view_projection", scene_data_->view_projection_matrix);
    shader->SetMat4("u_transform", transform);

    vertex_array->Bind();
    RenderCommand::DrawIndexed(vertex_array);
}

} // chernoengine2
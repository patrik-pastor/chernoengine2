//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/renderer/renderer.hpp>

namespace chernoengine2 {

Renderer::SceneData *Renderer::scene_data_ = new Renderer::SceneData;

RendererApi::Api Renderer::GetRendererApi() {
    return RendererApi::GetApi();
}

void Renderer::BeginScene(const OrthographicCamera& camera) {
    scene_data_->view_projection_matrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {

}

void Renderer::Submit(const Shader *shader, const VertexArray *vertex_array) {
    shader->Bind();
    shader->setMat4("u_view_projection", scene_data_->view_projection_matrix);

    vertex_array->Bind();
    RenderCommand::DrawIndexed(vertex_array);
}

} // chernoengine2
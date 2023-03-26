//
// Created by shepherd on 23.3.23.
//

#include <chernoengine2/renderer/render_command.hpp>
#include <chernoengine2/opengl/opengl_renderer_api.hpp>

namespace chernoengine2 {

Scope<RendererApi> RenderCommand::renderer_api_ = RendererApi::Create();

void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertex_array) {
    renderer_api_->DrawIndexed(vertex_array);
}

void RenderCommand::SetClearColor(const glm::vec4& color) {
    renderer_api_->SetClearColor(color);
}

void RenderCommand::Clear() {
    renderer_api_->Clear();
}

} // chernoengine2
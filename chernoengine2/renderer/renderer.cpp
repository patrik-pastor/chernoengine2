//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/renderer/renderer.hpp>

namespace chernoengine2 {

RendererApi::Api Renderer::GetRendererApi() {
    return RendererApi::GetApi();
}

void Renderer::BeginScene() {

}

void Renderer::EndScene() {

}

void Renderer::Submit(const VertexArray *vertex_array) {
    vertex_array->Bind();
    RenderCommand::DrawIndexed(vertex_array);
}

} // chernoengine2
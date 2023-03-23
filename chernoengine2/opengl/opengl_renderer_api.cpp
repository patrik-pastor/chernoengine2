//
// Created by shepherd on 23.3.23.
//

#include <chernoengine2/opengl/opengl_renderer_api.hpp>

#include <glad/glad.h>

namespace chernoengine2 {

void OpenglRendererApi::SetClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenglRendererApi::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRendererApi::DrawIndexed(const VertexArray *vertex_array) {
    glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

} // chernoengine2
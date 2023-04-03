//
// Created by shepherd on 23.3.23.
//

#include <chernoengine2/opengl/opengl_renderer_api.hpp>

#include <glad/glad.h>

#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

void OpenglRendererApi::Init() const {
    PROFILE_FUNCTION();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
}

void OpenglRendererApi::SetClearColor(const glm::vec4& color) {
    PROFILE_FUNCTION();

    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenglRendererApi::Clear() {
    PROFILE_FUNCTION();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRendererApi::DrawIndexed(const Ref<VertexArray>& vertex_array) {
    PROFILE_FUNCTION();

    glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}


} // chernoengine2
//
// Created by shepherd on 23.3.23.
//

#ifndef CHERNOENGINE2_OPENGL_RENDERER_API_HPP
#define CHERNOENGINE2_OPENGL_RENDERER_API_HPP

#include <chernoengine2/renderer/renderer_api.hpp>

namespace chernoengine2 {

class OpenglRendererApi : public RendererApi {
public:
    void SetClearColor(const glm::vec4& color) override;

    void Clear() override;

    void DrawIndexed(const Ref<VertexArray>& vertex_array) override;
};

} // chernoengine2

#endif //CHERNOENGINE2_OPENGL_RENDERER_API_HPP

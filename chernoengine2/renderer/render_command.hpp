//
// Created by shepherd on 23.3.23.
//

#ifndef CHERNOENGINE2_RENDER_COMMAND_HPP
#define CHERNOENGINE2_RENDER_COMMAND_HPP

#include <chernoengine2/core/core.hpp>
#include <chernoengine2/renderer/renderer_api.hpp>

#include <glm/glm.hpp>

namespace chernoengine2 {

class RenderCommand {
public:
    static void Init();

    static void DrawIndexed(const Ref<VertexArray>& vertex_array);

    static void SetClearColor(const glm::vec4& color);

    static void Clear();

private:
    static Scope<RendererApi> renderer_api_;
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDER_COMMAND_HPP

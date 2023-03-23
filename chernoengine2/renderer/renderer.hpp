//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_RENDERER_HPP
#define CHERNOENGINE2_RENDERER_HPP

#include <chernoengine2/renderer/render_command.hpp>

namespace chernoengine2 {

class Renderer {
public:
    static void BeginScene();

    static void EndScene();

    static void Submit(const VertexArray *vertex_array);

    static RendererApi::Api GetRendererApi();
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_HPP

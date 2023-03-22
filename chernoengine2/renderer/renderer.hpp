//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_RENDERER_HPP
#define CHERNOENGINE2_RENDERER_HPP

namespace chernoengine2 {

enum class RendererApi {
    NONE = 0, OPENGL = 1
};

class Renderer {
public:
    static RendererApi GetRendererApi();

private:
    static RendererApi renderer_api_;
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_HPP

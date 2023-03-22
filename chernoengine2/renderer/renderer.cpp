//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/renderer/renderer.hpp>

namespace chernoengine2 {

RendererApi Renderer::renderer_api_ = RendererApi::OPENGL;

RendererApi Renderer::GetRendererApi() {
    return renderer_api_;
}

} // chernoengine2
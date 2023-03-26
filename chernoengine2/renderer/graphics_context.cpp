//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/renderer/graphics_context.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/renderer/opengl_context.hpp>

namespace chernoengine2 {

Scope<GraphicsContext> GraphicsContext::Create(void *window) {
    switch (Renderer::GetRendererApi()) {
        case RendererApi::Api::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported!");
            return nullptr;
        case RendererApi::Api::OPENGL:
            return CreateScope<OpenglContext>(static_cast<GLFWwindow *>(window));
    }
    LOG_CORE_ERROR("unknown RendererApi");
    return nullptr;
}

} // chernoengine2
//
// Created by shepherd on 27.3.23.
//

#include <chernoengine2/renderer/texture.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/opengl/opengl_texture.hpp>

namespace chernoengine2 {

Ref<Texture2D> Texture2D::Create(const std::string& filepath) {
    switch (Renderer::GetRendererApi()) {
        case RendererApi::Api::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
            return nullptr;
        case RendererApi::Api::OPENGL:
            return CreateRef<OpenglTexture2D>(filepath);
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

Ref<Texture2D> Texture2D::Create(int width, int height) {
    switch (Renderer::GetRendererApi()) {
        case RendererApi::Api::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
            return nullptr;
        case RendererApi::Api::OPENGL:
            return CreateRef<OpenglTexture2D>(width, height);
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

} // chernoengine2
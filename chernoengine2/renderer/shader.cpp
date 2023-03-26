//
// Created by shepherd on 26.3.23.
//

#include <chernoengine2/renderer/shader.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/opengl/opengl_shader.hpp>

namespace chernoengine2 {

Ref<Shader> Shader::Create(const std::string& filepath) {
    switch(Renderer::GetRendererApi()){
        case RendererApi::Api::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
        case RendererApi::Api::OPENGL:
            return CreateRef<OpenglShader>(filepath);
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

} // chernoengine2
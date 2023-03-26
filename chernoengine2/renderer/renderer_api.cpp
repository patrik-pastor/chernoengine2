//
// Created by shepherd on 23.3.23.
//

#include <chernoengine2/renderer/renderer_api.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/opengl/opengl_renderer_api.hpp>

namespace chernoengine2 {

RendererApi::Api RendererApi::api_ = Api::OPENGL;

RendererApi::Api RendererApi::GetApi() {
    return api_;
}

Scope<RendererApi> RendererApi::Create() {
    switch(api_){
        case Api::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
            return nullptr;
        case Api::OPENGL:
            return CreateScope<OpenglRendererApi>();
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

} // chernoengine2
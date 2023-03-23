//
// Created by shepherd on 23.3.23.
//

#include <chernoengine2/renderer/renderer_api.hpp>

namespace chernoengine2 {

RendererApi::Api RendererApi::api_ = Api::OPENGL;

RendererApi::Api RendererApi::GetApi() {
    return api_;
}

} // chernoengine2
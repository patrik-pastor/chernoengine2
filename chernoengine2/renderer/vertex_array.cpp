//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/renderer/vertex_array.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/opengl/opengl_vertex_array.hpp>

namespace chernoengine2 {

VertexArray *VertexArray::Create() {
    switch(Renderer::GetRendererApi()){
        case RendererApi::Api::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
            return nullptr;
        case RendererApi::Api::OPENGL:
            return new OpenglVertexArray;
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

} // chernoengine2
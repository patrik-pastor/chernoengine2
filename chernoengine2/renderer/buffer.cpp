//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/renderer/buffer.hpp>
#include <chernoengine2/opengl/opengl_buffer.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/core/log.hpp>

namespace chernoengine2 {

VertexBuffer *VertexBuffer::Create(float *vertices, int size) {
    switch (Renderer::GetRendererApi()) {
        case RendererApi::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
        case RendererApi::OPENGL:
            return new OpenglVertexBuffer(vertices, size);
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

IndexBuffer *IndexBuffer::Create(int *indices, int count) {
    switch (Renderer::GetRendererApi()) {
        case RendererApi::NONE:
            LOG_CORE_ERROR("RendererApi::NONE is currently not supported");
        case RendererApi::OPENGL:
            return new OpenglIndexBuffer(indices, count);
    }
    LOG_CORE_ERROR("Unknown RendererApi");
    return nullptr;
}

} // chernoengine2
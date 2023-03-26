//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_VERTEX_ARRAY_HPP
#define CHERNOENGINE2_VERTEX_ARRAY_HPP

#include <chernoengine2/renderer/buffer.hpp>

namespace chernoengine2 {

class VertexArray {
public:
    static VertexArray *Create();

    virtual void Bind() const = 0;

    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const VertexBuffer *buffer) = 0;

    virtual void SetIndexBuffer(const IndexBuffer *buffer) = 0;

    virtual const std::vector<const VertexBuffer*> &GetVertexBuffers() const = 0;

    virtual const IndexBuffer *GetIndexBuffer() const = 0;
};

} // chernoengine2

#endif //CHERNOENGINE2_VERTEX_ARRAY_HPP

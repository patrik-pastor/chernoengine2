//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_VERTEX_ARRAY_HPP
#define CHERNOENGINE2_VERTEX_ARRAY_HPP

#include <chernoengine2/renderer/buffer.hpp>
#include <chernoengine2/core/core.hpp>

namespace chernoengine2 {

class VertexArray {
public:
    static Ref<VertexArray> Create();

    virtual void Bind() const = 0;

    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;

    virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

    virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;

    virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
};

} // chernoengine2

#endif //CHERNOENGINE2_VERTEX_ARRAY_HPP

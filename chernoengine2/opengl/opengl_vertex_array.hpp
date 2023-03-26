//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_OPENGL_VERTEX_ARRAY_HPP
#define CHERNOENGINE2_OPENGL_VERTEX_ARRAY_HPP

#include <chernoengine2/renderer/vertex_array.hpp>
#include <chernoengine2/renderer/buffer.hpp>

namespace chernoengine2 {

class OpenglVertexArray : public VertexArray {
public:
    OpenglVertexArray();

    virtual ~OpenglVertexArray();

    void Bind() const override;

    void Unbind() const override;

    void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;

    void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;

    const std::vector<Ref<VertexBuffer>> & GetVertexBuffers() const override;

    const Ref<IndexBuffer>& GetIndexBuffer() const override;

private:
    uint32_t renderer_id_;
    std::vector<Ref<VertexBuffer>> vertex_buffers_;
    Ref<IndexBuffer> index_buffer_;
};

} // chernoengine2

#endif //CHERNOENGINE2_OPENGL_VERTEX_ARRAY_HPP

//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_OPENGL_BUFFER_HPP
#define CHERNOENGINE2_OPENGL_BUFFER_HPP

#include <chernoengine2/renderer/buffer.hpp>

#include <stdint.h>

namespace chernoengine2 {

class OpenglVertexBuffer : public VertexBuffer {
public:
    OpenglVertexBuffer(float *vertices, int size);

    ~OpenglVertexBuffer() override;

    void Bind() const override;

    void UnBind() const override;

private:
    uint32_t renderer_id_;
};

class OpenglIndexBuffer : public IndexBuffer {
public:
    OpenglIndexBuffer(int *indices, int count);

    ~OpenglIndexBuffer() override = default;

    void Bind() const override;

    void Unbind() const override;

    int GetCount() const override;
private:
    uint32_t renderer_id_;
    int count_;
};

} // chernoengine2

#endif //CHERNOENGINE2_OPENGL_BUFFER_HPP

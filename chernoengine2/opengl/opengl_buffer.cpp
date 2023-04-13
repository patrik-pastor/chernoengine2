//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/opengl/opengl_buffer.hpp>

#include <glad/glad.h>

#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

OpenglVertexBuffer::OpenglVertexBuffer(float *vertices, int size) {
    PROFILE_FUNCTION();

    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenglVertexBuffer::OpenglVertexBuffer(int size) {
    PROFILE_FUNCTION();

    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);;
}

OpenglVertexBuffer::~OpenglVertexBuffer() {
    PROFILE_FUNCTION();

    glDeleteBuffers(1, &renderer_id_);
}

void OpenglVertexBuffer::Bind() const {
    PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
}

void OpenglVertexBuffer::UnBind() const {
    PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenglVertexBuffer::SetData(void *data, int size) const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenglVertexBuffer::SetLayout(const BufferLayout& layout) {
    layout_ = layout;
}

const BufferLayout& OpenglVertexBuffer::GetLayout() const {
    return layout_;
}

OpenglIndexBuffer::OpenglIndexBuffer(int *indices, int count) : count_(count) {
    PROFILE_FUNCTION();

    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}

void OpenglIndexBuffer::Bind() const {
    PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
}

void OpenglIndexBuffer::Unbind() const {
    PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int OpenglIndexBuffer::GetCount() const {
    return count_;
}

} // chernoengine2
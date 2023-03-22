//
// Created by shepherd on 22.3.23.
//

#include <chernoengine2/opengl/opengl_buffer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace chernoengine2 {

OpenglVertexBuffer::OpenglVertexBuffer(float *vertices, int size) {
    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenglVertexBuffer::~OpenglVertexBuffer() {
    glDeleteBuffers(1, &renderer_id_);
}

void OpenglVertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
}

void OpenglVertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenglVertexBuffer::SetLayout(const BufferLayout& layout) {
    layout_ = layout;
}

const BufferLayout& OpenglVertexBuffer::GetLayout() const {
    return layout_;
}

OpenglIndexBuffer::OpenglIndexBuffer(int *indices, int count) : count_(count) {
    glGenBuffers(1, &renderer_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}

void OpenglIndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
}

void OpenglIndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int OpenglIndexBuffer::GetCount() const {
    return count_;
}

} // chernoengine2
//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_BUFFER_HPP
#define CHERNOENGINE2_BUFFER_HPP

namespace chernoengine2 {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;

    virtual void UnBind() const = 0;

    static VertexBuffer *Create(float *vertices, int size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;

    virtual void Unbind() const = 0;

    virtual int GetCount() const = 0;

    static IndexBuffer *Create(int *indices, int count);
};

} // chernoengine2

#endif //CHERNOENGINE2_BUFFER_HPP

//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_BUFFER_HPP
#define CHERNOENGINE2_BUFFER_HPP

#include <string>
#include <vector>
#include <initializer_list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/core/core.hpp>

namespace chernoengine2 {

enum class ShaderDataType {
    None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

int ShaderDataTypeSize(ShaderDataType type);

int ElementComponentCount(ShaderDataType type);

GLenum ShaderDataTypeToOpenglBaseType(ShaderDataType type);

struct BufferElement {
    BufferElement(const std::string& name, ShaderDataType type, bool normalized = false);

    std::string name;
    ShaderDataType type;
    int offset;
    int size;
    bool normalized;
    int component_count;
};

class BufferLayout {
public:
    BufferLayout() = default;

    BufferLayout(const std::initializer_list<BufferElement>& elements);

    int GetStride() const;

    std::vector<BufferElement>::iterator begin();

    std::vector<BufferElement>::iterator end();

    std::vector<BufferElement>::const_iterator begin() const;

    std::vector<BufferElement>::const_iterator end() const;

private:
    void CalculateOffsetAndStride();

    std::vector<BufferElement> elements_;
    int stride_ = 0;
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;

    virtual void UnBind() const = 0;

    virtual void SetData(void *data, int size) const = 0;

    virtual void SetLayout(const BufferLayout& layout) = 0;

    virtual const BufferLayout& GetLayout() const = 0;

    static Ref<VertexBuffer> Create(float *vertices, int size);

    static Ref<VertexBuffer> Create(int size);
};

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;

    virtual void Unbind() const = 0;

    virtual int GetCount() const = 0;

    static Ref<IndexBuffer> Create(int *indices, int count);
};

} // chernoengine2

#endif //CHERNOENGINE2_BUFFER_HPP

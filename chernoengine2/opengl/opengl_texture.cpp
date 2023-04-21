//
// Created by shepherd on 27.3.23.
//

#include <chernoengine2/opengl/opengl_texture.hpp>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

uint32_t OpenglTexture2D::array_renderer_id_ = 0;

OpenglTexture2D::OpenglTexture2D(int width, int height): width_(width), height_(height) {
    PROFILE_FUNCTION();

    glGenTextures(1, &renderer_id_);
    glBindTexture(GL_TEXTURE_2D, renderer_id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    InitArray();
}

OpenglTexture2D::OpenglTexture2D(const std::string& filepath) {
    PROFILE_FUNCTION();

    stbi_set_flip_vertically_on_load(1);
    {
        PROFILE_SCOPE("stbi_load - OpenglTexture2D::OpenglTexture2D(const std::string&)");
        data_ = stbi_load(filepath.c_str(), &width_, &height_, nullptr, 4);
    }
    if (data_ == nullptr) {
        LOG_CORE_ERROR("Failed to load image");
    }

    glGenTextures(1, &renderer_id_);
    glBindTexture(GL_TEXTURE_2D, renderer_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    InitArray();
}


OpenglTexture2D::~OpenglTexture2D() {
    PROFILE_FUNCTION();

    glDeleteTextures(1, &renderer_id_);
}

void OpenglTexture2D::SetData(void *data) {
    PROFILE_FUNCTION();

    data_ = data;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}


int OpenglTexture2D::GetId() const {
    return renderer_id_;
}

int OpenglTexture2D::GetWidth() const {
    return width_;
}

int OpenglTexture2D::GetHeight() const {
    return height_;
}

void OpenglTexture2D::Bind(int slot) const {
    PROFILE_FUNCTION();

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, renderer_id_);
}

void OpenglTexture2D::BindToArray(int slot) const {
    if(data_ == nullptr){
        LOG_CORE_ERROR("no texture data loaded");
    }
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, slot, width_, height_, 1, GL_RGBA, GL_UNSIGNED_BYTE, data_);
}

bool OpenglTexture2D::operator==(const Texture& rhs) const {
    return renderer_id_ == rhs.GetId();
}

void OpenglTexture2D::InitArray() const {
    if(array_renderer_id_ == 0){
        glGenTextures(1, &array_renderer_id_);
        glBindTexture(GL_TEXTURE_2D_ARRAY, array_renderer_id_);
        int max_textures;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_textures);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width_, height_, max_textures, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}


} // chernoengine2
//
// Created by shepherd on 27.3.23.
//

#include <chernoengine2/opengl/opengl_texture.hpp>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

#include <chernoengine2/core/log.hpp>

namespace chernoengine2 {

OpenglTexture2D::OpenglTexture2D(int width, int height): width_(width), height_(height) {
    glGenTextures(1, &renderer_id_);
    glBindTexture(GL_TEXTURE_2D, renderer_id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

OpenglTexture2D::OpenglTexture2D(const std::string& filepath) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    uint8_t *data = stbi_load(filepath.c_str(), &width, &height, &channels, 4);
    if (data == nullptr) {
        LOG_CORE_ERROR("Failed to load image");
    }
    width_ = width;
    height_ = height;

    glGenTextures(1, &renderer_id_);
    glBindTexture(GL_TEXTURE_2D, renderer_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
}


OpenglTexture2D::~OpenglTexture2D() {
    glDeleteTextures(1, &renderer_id_);
}

void OpenglTexture2D::SetData(void *data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

int OpenglTexture2D::GetWidth() const {
    return width_;
}

int OpenglTexture2D::GetHeight() const {
    return height_;
}

void OpenglTexture2D::Bind(int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, renderer_id_);
}


} // chernoengine2
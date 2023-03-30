//
// Created by shepherd on 27.3.23.
//

#ifndef CHERNOENGINE2_OPENGL_TEXTURE_HPP
#define CHERNOENGINE2_OPENGL_TEXTURE_HPP

#include <string>

#include <chernoengine2/renderer/texture.hpp>

namespace chernoengine2 {

class OpenglTexture2D : public Texture2D {
public:
    OpenglTexture2D(int width, int height);

    OpenglTexture2D(const std::string& filepath);

    ~OpenglTexture2D() override;

    void SetData(void *data) override;

    int GetWidth() const override;

    int GetHeight() const override;

    void Bind(int slot) const override;

private:
    int width_;
    int height_;
    uint32_t renderer_id_;
};

} // chernoengine2

#endif //CHERNOENGINE2_OPENGL_TEXTURE_HPP

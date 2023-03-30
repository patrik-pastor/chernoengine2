//
// Created by shepherd on 27.3.23.
//

#ifndef CHERNOENGINE2_TEXTURE_HPP
#define CHERNOENGINE2_TEXTURE_HPP

#include <string>

#include <chernoengine2/core/core.hpp>

namespace chernoengine2 {

class Texture {
public:
    virtual ~Texture() = default;

    virtual int GetWidth() const = 0;

    virtual int GetHeight() const = 0;

    virtual void SetData(void *data) = 0;

    virtual void Bind(int slot = 0) const = 0;
};

class Texture2D : public Texture {
public:
    static Ref<Texture2D> Create(const std::string& filepath);

    static Ref<Texture2D> Create(int width, int height);
};

} // chernoengine2

#endif //CHERNOENGINE2_TEXTURE_HPP

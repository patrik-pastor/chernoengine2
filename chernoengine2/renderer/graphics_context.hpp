//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_GRAPHICS_CONTEXT_HPP
#define CHERNOENGINE2_GRAPHICS_CONTEXT_HPP

namespace chernoengine2 {

class GraphicsContext {
public:
    virtual ~GraphicsContext() = default;

    static GraphicsContext *Create(void *window);

    virtual void Init() = 0;

    virtual void SwapBuffers() = 0;
};

} // chernoengine2

#endif //CHERNOENGINE2_GRAPHICS_CONTEXT_HPP

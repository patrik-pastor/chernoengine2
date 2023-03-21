//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/renderer/graphics_context.hpp>
#include <chernoengine2/renderer/opengl_context.hpp>

namespace chernoengine2 {

GraphicsContext *GraphicsContext::Create(void *window) {
    return new OpenglContext(static_cast<GLFWwindow*>(window));
}

} // chernoengine2
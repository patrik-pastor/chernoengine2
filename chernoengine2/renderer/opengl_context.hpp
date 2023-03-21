//
// Created by shepherd on 20.3.23.
//

#ifndef CHERNOENGINE2_OPENGL_CONTEXT_HPP
#define CHERNOENGINE2_OPENGL_CONTEXT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/renderer/graphics_context.hpp>

namespace chernoengine2 {

class OpenglContext : public GraphicsContext {
public:
    explicit OpenglContext(GLFWwindow *window);

    void Init() override;

    void SwapBuffers() override;
private:
    GLFWwindow *window_;
};

} // chernoengine2

#endif //CHERNOENGINE2_OPENGL_CONTEXT_HPP

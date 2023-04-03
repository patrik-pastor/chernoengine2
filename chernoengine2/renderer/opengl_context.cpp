//
// Created by shepherd on 20.3.23.
//

#include <chernoengine2/renderer/opengl_context.hpp>

#include <chernoengine2/core/log.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

OpenglContext::OpenglContext(GLFWwindow *window) : window_(window) {}

void OpenglContext::Init() {
    PROFILE_FUNCTION();

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow *_, int width, int height) {
        glViewport(0, 0, width, height);
    });

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOG_CORE_CRITICAL("failed to initialize GLAD");
    } else {
        LOG_CORE_TRACE("gladLoadGLLoader");
    }

    LOG_CORE_INFO("OpenGL Info:");
    LOG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    LOG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    LOG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenglContext::SwapBuffers() {
    PROFILE_FUNCTION();

    glfwSwapBuffers(window_);
}

} // chernoengine2
//
// Created by shepherd on 23.3.23.
//

#include <chernoengine2/core/input.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/core/application.hpp>

namespace chernoengine2 {

bool Input::IsKeyPressed(int keycode) {
    auto *window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS;
}

} // chernoengine2
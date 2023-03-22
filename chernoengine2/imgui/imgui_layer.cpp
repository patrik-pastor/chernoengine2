//
// Created by shepherd on 21.3.23.
//

#include <chernoengine2/imgui/imgui_layer.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/core/application.hpp>

namespace chernoengine2 {

ImguiLayer::ImguiLayer() : Layer("ImguiLayer") {}

void ImguiLayer::OnAttach() {
    // 1.1 Imgui Context
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // 1.2 Imgui flags
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // 1.3 Imgui init for opengl
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImguiLayer::OnUpdate() {
    // 1.1 set window size for imgui
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::GetInstance();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    // 1.2 new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // 1.3 imgui demo window
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    // 1.4 imgui render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::OnEvent(Event& event) {
    Layer::OnEvent(event);
}


} // chernoengine2
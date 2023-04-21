//
// Created by shepherd on 29.3.23.
//

#include <chernoengine2/main/example_layers/second_example.hpp>

#include <iostream>
#include <chrono>

#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include <chernoengine2/renderer/renderer_2d.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

SecondExample::SecondExample() :
        camera_controller_(1280.0f / 720.0f) {}

void SecondExample::OnAttach() {
    PROFILE_FUNCTION();

    chessboard_texture_ = Texture2D::Create("assets/textures/checkerboard.png");
}

void SecondExample::OnDetach() {
    PROFILE_FUNCTION();

    Layer::OnDetach();
}

void SecondExample::OnUpdate(float delta_time) {
    PROFILE_FUNCTION();

    // update
    camera_controller_.OnUpdate(delta_time);

    // renderer
    {
        PROFILE_SCOPE("Renderer prepare");
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::Clear();
    }

    {
        PROFILE_SCOPE("Renderer draw");
        Renderer2D::BeginScene(camera_controller_.GetCamera());
//        Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
        Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        Renderer2D::DrawQuad({-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, chessboard_texture_, 10.0f);
//        Renderer2D::DrawQuad({-5.0f, -5.0f, 0.0f}, {1.0f, 1.0f}, chessboard_texture_, 20.0f);
        Renderer2D::EndScene();
    }
}

void SecondExample::OnImguiRender() {
    PROFILE_FUNCTION();

//    ImGui::Begin("Settings");
//    ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
//    ImGui::End();
}

void SecondExample::OnEvent(Event& event) {
    camera_controller_.OnEvent(event);
}


} // chernoengine2
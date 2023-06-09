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
        static float rotation = 0.0f;
        rotation += delta_time * 50.0f;

        PROFILE_SCOPE("Renderer draw");
        Renderer2D::BeginScene(camera_controller_.GetCamera());
        Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
        Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, chessboard_texture_, 10.0f);
        Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, chessboard_texture_, 20.0f);
//        Renderer2D::EndScene();
//
//        Renderer2D::BeginScene(camera_controller_.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f) {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) {
                glm::vec4 color(x + 5.0f / 10.0f, 0.4f, y + 5.0f / 10.0f, 0.5f);
                Renderer2D::DrawQuad({x, y}, {0.4f, 0.45f}, color);
            }
        }
        Renderer2D::EndScene();
    }
}

void SecondExample::OnImguiRender() {
    PROFILE_FUNCTION();

//    ImGui::Begin("Settings");

//    auto stats = Renderer2D::GetStats();
//    ImGui::Text("Renderer2D Stats:");
//    ImGui::Text("Draw Calls: %d", stats.draw_calls);
//    ImGui::Text("Quads: %d", stats.quad_count);
//    ImGui::Text("vertices: %d", stats.GetTotalVertexCount());
//    ImGui::Text("indices: %d", stats.GetTotalIndexCount());
//#include <stdio.h>
//    printf("Draw Calls: %d\n", stats.draw_calls);
//    printf("Quads: %d\n", stats.quad_count);
//    printf("vertices: %d\n", stats.GetTotalVertexCount());
//    printf("indices: %d\n", stats.GetTotalIndexCount());

//    ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
//    ImGui::End();
}

void SecondExample::OnEvent(Event& event) {
    camera_controller_.OnEvent(event);
}


} // chernoengine2
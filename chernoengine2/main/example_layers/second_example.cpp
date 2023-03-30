//
// Created by shepherd on 29.3.23.
//

#include <chernoengine2/main/example_layers/second_example.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include <chernoengine2/renderer/renderer_2_d.hpp>

namespace chernoengine2 {

SecondExample::SecondExample() :
        camera_controller_(1280.0f / 720.0f) {}

void SecondExample::OnAttach() {

}

void SecondExample::OnDetach() {
    Layer::OnDetach();
}

void SecondExample::OnUpdate(float delta_time) {
    // update
    camera_controller_.OnUpdate(delta_time);

    // renderer
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    Renderer2D::BeginScene(camera_controller_.GetCamera());

    Renderer2D::BeginScene(camera_controller_.GetCamera());
    Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Renderer2D::EndScene();
}

void SecondExample::OnImguiRender() {
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));

    ImGui::End();
}

void SecondExample::OnEvent(Event& event) {
    camera_controller_.OnEvent(event);
}


} // chernoengine2
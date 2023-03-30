//
// Created by shepherd on 29.3.23.
//

#ifndef CHERNOENGINE2_SECOND_EXAMPLE_HPP
#define CHERNOENGINE2_SECOND_EXAMPLE_HPP

#include <glm/glm.hpp>

#include <chernoengine2/core/layer.hpp>
#include <chernoengine2/renderer/orthographic_camera_controller.hpp>

namespace chernoengine2 {

class SecondExample : public Layer {
public:
    SecondExample();

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(float delta_time) override;

    void OnImguiRender() override;

    void OnEvent(Event& event) override;

private:
    OrthographicCameraController camera_controller_;

    Ref<Shader> square_shader_;
    Ref<VertexArray> square_va_;
    glm::vec4 square_color_ = {0.2f, 0.3f, 0.8f, 1.0};
};

} // chernoengine2

#endif //CHERNOENGINE2_SECOND_EXAMPLE_HPP

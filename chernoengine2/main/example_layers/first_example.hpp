//
// Created by shepherd on 29.3.23.
//

#ifndef CHERNOENGINE2_FIRST_EXAMPLE_HPP
#define CHERNOENGINE2_FIRST_EXAMPLE_HPP

#include <chernoengine2/core/layer.hpp>

namespace chernoengine2 {

class FirstExample : public Layer {
public:
    FirstExample();

    void OnUpdate(float delta_time) override;

    void OnImguiRender() override;

    void OnEvent(Event &event) override;

private:
//    Ref<Shader> triangle_shader_;
//    Ref<VertexArray> triangle_va_;

    Ref<Shader> square_shader_;
    Ref<VertexArray> square_va_;
    glm::vec3 square_color_;

    Ref<Shader> chessboard_shader_;
    Ref<Texture2D> chessboard_texture_;
    Ref<Texture2D> chernologo_texture_;

    OrthographicCameraController camera_controller_;
};

} // chernoengine2

#endif //CHERNOENGINE2_FIRST_EXAMPLE_HPP

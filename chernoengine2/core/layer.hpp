//
// Created by shepherd on 9.3.23.
//

#ifndef CHERNOENGINE2_LAYER_HPP
#define CHERNOENGINE2_LAYER_HPP

#include <string>

#include <glm/glm.hpp>

#include <chernoengine2/events/event.hpp>
#include <chernoengine2/events/key_event.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/renderer/orthographic_camera_controller.hpp>
#include <chernoengine2/renderer/texture.hpp>

namespace chernoengine2 {

class Layer {
public:
    explicit Layer(const std::string& name = "Layer");

    virtual ~Layer() = default;

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate(float delta_time) {}

    virtual void OnImguiRender() {}

    virtual void OnEvent(Event& event) {}

private:
    std::string name_;
};

class FirstExample : public Layer {
public:
    FirstExample();

    void OnUpdate(float delta_time) override;

    void OnImguiRender() override;

    void OnEvent(Event &event) override;

private:
    Ref<Shader> triangle_shader_;
    Ref<VertexArray> triangle_va_;

    Ref<Shader> square_shader_;
    Ref<VertexArray> square_va_;
    glm::vec3 square_color_;

    Ref<Shader> chessboard_shader_;
    Ref<Texture2D> chessboard_texture_;
    Ref<Texture2D> chernologo_texture_;

    OrthographicCameraController camera_controller_;
};

} // chernoengine22

#endif //CHERNOENGINE2_LAYER_HPP

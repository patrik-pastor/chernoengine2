//
// Created by shepherd on 9.3.23.
//

#ifndef CHERNOENGINE2_LAYER_HPP
#define CHERNOENGINE2_LAYER_HPP

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <chernoengine2/events/event.hpp>
#include <chernoengine2/renderer/renderer.hpp>
#include <chernoengine2/events/key_event.hpp>

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

private:
    Shader *shader_;
    VertexArray *va_;
    VertexBuffer *vb_;
    IndexBuffer *ib_;
    OrthographicCamera camera_;

    glm::vec3 camera_position_;
    float camera_move_speed_ = 5.0f;

    float camera_rotation_ = 0.0f;
    float camera_rotation_speed_ = 180.0f;
};

} // chernoengine22

#endif //CHERNOENGINE2_LAYER_HPP

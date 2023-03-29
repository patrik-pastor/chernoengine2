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

} // chernoengine22

#endif //CHERNOENGINE2_LAYER_HPP

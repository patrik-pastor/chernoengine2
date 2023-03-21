//
// Created by shepherd on 9.3.23.
//

#ifndef CHERNOENGINE2_LAYER_HPP
#define CHERNOENGINE2_LAYER_HPP

#include <memory>
#include <string>

#include <chernoengine2/events/event.hpp>

namespace chernoengine2 {

class Layer {
public:
    explicit Layer(const std::string& name = "Layer");

    virtual ~Layer() = default;

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate() {}

    virtual void OnImguiRender() {}

    virtual void OnEvent(Event& event) {}

private:
    std::string name_;
};

class ExampleLayer : public Layer {
public:
    ExampleLayer();
    void OnUpdate() override;

    void OnEvent(Event& event) override;
};

} // chernoengine22

#endif //CHERNOENGINE2_LAYER_HPP

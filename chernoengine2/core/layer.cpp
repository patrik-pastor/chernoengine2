//
// Created by shepherd on 9.3.23.
//

#include <chernoengine2/core/layer.hpp>

#include <chernoengine2/core/log.hpp>

namespace chernoengine2 {

Layer::Layer(const std::string& name) : name_(name) {}

ExampleLayer::ExampleLayer() : Layer("Example") {}

void ExampleLayer::OnUpdate() {
    LOG_APP_INFO("ExampleLayer::Update");
}

void ExampleLayer::OnEvent(Event& event) {
    LOG_APP_TRACE(event.ToString());
}

} // chernoengine22
//
// Created by shepherd on 29.3.23.
//

#ifndef CHERNOENGINE2_ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP
#define CHERNOENGINE2_ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP

#include <chernoengine2/renderer/orthographic_camera.hpp>
#include <chernoengine2/events/event.hpp>
#include <chernoengine2/events/mouse_event.hpp>
#include <chernoengine2/events/application_event.hpp>

namespace chernoengine2 {

class OrthographicCameraController {
public:
    explicit OrthographicCameraController(float aspect_ratio, bool rotation = false);

    void OnUpdate(float delta_time);

    void OnEvent(Event& event);

    bool OnMouseScrolled(MouseScrolledEvent& event);

    bool OnWindowResized(WindowResizeEvent& event);

    const OrthographicCamera& GetCamera() const;

private:
    float aspect_ratio_;
    float zoom_level_ = 1;
    OrthographicCamera camera_;
    bool rotation_;
    glm::vec3 camera_position_ = {0.0f, 0.0f, 0.0f};
    float camera_rotation_ = 0.0f;
    float camera_translation_speed_ = 5.0f;
    float camera_rotation_speed_ = 180.0f;
};

} // chernoengine2

#endif //CHERNOENGINE2_ORTHOGRAPHIC_CAMERA_CONTROLLER_HPP

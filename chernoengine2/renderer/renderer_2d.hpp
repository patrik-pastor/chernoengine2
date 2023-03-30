//
// Created by shepherd on 30.3.23.
//

#ifndef CHERNOENGINE2_RENDERER_2D_HPP
#define CHERNOENGINE2_RENDERER_2D_HPP

#include <glm/glm.hpp>

#include <chernoengine2/renderer/orthographic_camera.hpp>
#include <chernoengine2/renderer/texture.hpp>

namespace chernoengine2 {

class Renderer2D {
public:
    static void Init();

    static void Shutdown();

    static void BeginScene(const OrthographicCamera& camera);

    static void EndScene();

    // primitives
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_2D_HPP

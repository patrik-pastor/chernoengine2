//
// Created by shepherd on 30.3.23.
//

#ifndef CHERNOENGINE2_RENDERER_2D_HPP
#define CHERNOENGINE2_RENDERER_2D_HPP

#include <glm/glm.hpp>

#include <chernoengine2/renderer/orthographic_camera.hpp>
#include <chernoengine2/renderer/vertex_array.hpp>
#include <chernoengine2/renderer/shader.hpp>
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

    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                         float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                         float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

    static void
    DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

    static void
    DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

    static void
    DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture,
                    float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

    static void
    DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture,
                    float tiling_factor = 1.0, const glm::vec4& tint_color = glm::vec4(1.0f));
};

struct Renderer2DStorage {
    Ref<VertexArray> quad_va;
    Ref<Shader> texture_shader;
    Ref<Texture2D> white_texture_;
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_2D_HPP

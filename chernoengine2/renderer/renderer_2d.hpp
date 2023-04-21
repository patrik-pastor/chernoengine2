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

    static void Flush();

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

    struct Statistics {
        int draw_calls = 0;
        int quad_count = 0;

        int GetTotalVertexCount() const {
            return quad_count * 4;
        }

        int GetTotalIndexCount() const {
            return quad_count * 6;
        }
    };

    static void ResetStats();

    static Statistics GetStats();

private:
    static void StartBatch();

    static void NextBatch();
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_2D_HPP

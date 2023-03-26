//
// Created by shepherd on 22.3.23.
//

#ifndef CHERNOENGINE2_RENDERER_HPP
#define CHERNOENGINE2_RENDERER_HPP

#include <chernoengine2/core/core.hpp>
#include <chernoengine2/renderer/render_command.hpp>
#include <chernoengine2/renderer/shader.hpp>
#include <chernoengine2/renderer/orthographic_camera.hpp>

namespace chernoengine2 {

class Renderer {
public:
    static void BeginScene(const OrthographicCamera& camera);

    static void EndScene();

    static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));

    static RendererApi::Api GetRendererApi();

private:
    struct SceneData {
        glm::mat4 view_projection_matrix;
    };
    static Scope<SceneData> scene_data_;
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_HPP

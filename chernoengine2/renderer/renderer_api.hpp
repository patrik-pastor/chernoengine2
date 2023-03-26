//
// Created by shepherd on 23.3.23.
//

#ifndef CHERNOENGINE2_RENDERER_API_HPP
#define CHERNOENGINE2_RENDERER_API_HPP

#include <glm/glm.hpp>

#include <chernoengine2/core/core.hpp>
#include <chernoengine2/renderer/vertex_array.hpp>

namespace chernoengine2 {

class RendererApi {
public:
    enum class Api {
        NONE = 0, OPENGL = 1
    };

    virtual ~RendererApi() = default;

    virtual void SetClearColor(const glm::vec4& color) = 0;

    virtual void Clear() = 0;

    virtual void DrawIndexed(const Ref<VertexArray>& vertex_array) = 0;

    static Api GetApi();

    static Scope<RendererApi> Create();

private:
    static Api api_;
};

} // chernoengine2

#endif //CHERNOENGINE2_RENDERER_API_HPP

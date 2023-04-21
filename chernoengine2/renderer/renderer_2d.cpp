//
// Created by shepherd on 30.3.23.
//

#include <chernoengine2/renderer/renderer_2d.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <chernoengine2/renderer/render_command.hpp>
#include <chernoengine2/debug/instrumentor.hpp>

namespace chernoengine2 {

struct QuadVertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture_coordinates;
    float texture_index;
    float tiling_factor;
};

struct Renderer2DData {
    static const int max_quads = 10000;
    static const int max_vertices = max_quads * 4;
    static const int max_indices = max_quads * 6;
    static const int max_texture_slots = 32;

    Ref<VertexArray> quad_vertex_array;
    Ref<VertexBuffer> quad_vertex_buffer;
    Ref<Shader> texture_shader;
    Ref<Texture2D> white_texture_;

    int quad_index_count = 0;
    QuadVertex *quad_vertex_buffer_base = nullptr;
    QuadVertex *quad_vertex_buffer_ptr = nullptr;

    std::array<Ref<Texture2D>, max_texture_slots> textures;
    int texture_slot_index = 1;

    glm::vec4 quad_vertex_positions[4];

    Renderer2D::Statistics stats;
};

static Renderer2DData data;

void Renderer2D::Init() {
    PROFILE_FUNCTION();

    data.quad_vertex_array = VertexArray::Create();
    data.quad_vertex_buffer = VertexBuffer::Create(data.max_vertices * sizeof(QuadVertex));
    data.quad_vertex_buffer->SetLayout({
                                               {"a_pos",          ShaderDataType::Float3},
                                               {"a_color",        ShaderDataType::Float4},
                                               {"a_texcoord",     ShaderDataType::Float2},
                                               {"a_texindex",     ShaderDataType::Float},
                                               {"a_tilingfactor", ShaderDataType::Float}
                                       });
    data.quad_vertex_array->AddVertexBuffer(data.quad_vertex_buffer);
    data.quad_vertex_buffer_base = new QuadVertex[data.max_vertices];
    int *quad_indices = new int[data.max_indices];
    int offset = 0;
    for (int i = 0; i < data.max_indices; i += 6) {
        quad_indices[i + 0] = offset + 0;
        quad_indices[i + 1] = offset + 1;
        quad_indices[i + 2] = offset + 2;
        quad_indices[i + 3] = offset + 2;
        quad_indices[i + 4] = offset + 3;
        quad_indices[i + 5] = offset + 0;
        offset += 4;
    }
    Ref<IndexBuffer> quad_index_buffer = IndexBuffer::Create(quad_indices, data.max_indices);
    data.quad_vertex_array->SetIndexBuffer(quad_index_buffer);
    delete[] quad_indices;

//    data.white_texture_ = Texture2D::Create(1, 1);
//    uint32_t white_texture_data = 0xffffffff;
//    data.white_texture_->SetData(&white_texture_data);
    data.white_texture_ = Texture2D::Create("assets/textures/white.png");
    data.textures[0] = data.white_texture_;

    data.texture_shader = Shader::Create("assets/GLSL/2e_texture_batching.glsl");
    data.texture_shader->Bind();
    data.texture_shader->SetInt("u_texture", 0);

    data.quad_vertex_positions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    data.quad_vertex_positions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    data.quad_vertex_positions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    data.quad_vertex_positions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void Renderer2D::Shutdown() {
    PROFILE_FUNCTION();
}

void Renderer2D::BeginScene(const OrthographicCamera& camera) {
    PROFILE_FUNCTION();

    data.texture_shader->Bind();
    data.texture_shader->SetMat4("u_view_projection", camera.GetViewProjectionMatrix());

    StartBatch();
}

void Renderer2D::EndScene() {
    PROFILE_FUNCTION();

    Flush();
}

void Renderer2D::Flush() {
    int size = (uint8_t *) data.quad_vertex_buffer_ptr - (uint8_t *) data.quad_vertex_buffer_base;
    data.quad_vertex_buffer->SetData(data.quad_vertex_buffer_base, size);

    for (int i = 0; i < data.texture_slot_index; i++) {
        data.textures[i]->BindToArray(i);
    }
    RenderCommand::DrawIndexed(data.quad_vertex_array, data.quad_index_count);

    data.stats.draw_calls++;
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
    PROFILE_FUNCTION();

    if (data.quad_index_count >= Renderer2DData::max_indices) {
        NextBatch();
    }

    float texture_index = 0.0f; // white texture
    float tiling_factor = 1.0f;

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[0];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[1];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[2];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[3];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_index_count += 6;

    data.stats.quad_count++;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                          float tiling_factor, const glm::vec4& tint_color) {
    PROFILE_FUNCTION();

    if (data.quad_index_count >= Renderer2DData::max_indices) {
        NextBatch();
    }

    float texture_index = 0.0f;
    for (int i = 1; i < data.textures.size(); i++) {
        if (data.textures[i] && *data.textures[i] == *texture) {
            texture_index = (float) i;
            break;
        }
    }
    if (texture_index == 0.0f) {
        texture_index = (float) data.texture_slot_index;
        data.textures[data.texture_slot_index] = texture;
        data.texture_slot_index++;
    }

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[0];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[1];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[2];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[3];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_index_count += 6;

    data.stats.quad_count++;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture,
                          float tiling_factor, const glm::vec4& tint_color) {
    DrawQuad({position.x, position.y, 0.0f}, size, texture, tiling_factor, tint_color);
}

void
Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    PROFILE_FUNCTION();

    if (data.quad_index_count >= Renderer2DData::max_indices) {
        NextBatch();
    }

    float texture_index = 0.0f; // white texture
    float tiling_factor = 1.0f;

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[0];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[1];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[2];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[3];
    data.quad_vertex_buffer_ptr->color = color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_index_count += 6;

    data.stats.quad_count++;
}

void
Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                 const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color) {
    PROFILE_FUNCTION();

    if (data.quad_index_count >= Renderer2DData::max_indices) {
        NextBatch();
    }

    float texture_index = 0.0f;
    for (int i = 1; i < data.textures.size(); i++) {
        if (data.textures[i] && *data.textures[i] == *texture) {
            texture_index = (float) i;
            break;
        }
    }
    if (texture_index == 0.0f) {
        texture_index = (float) data.texture_slot_index;
        data.textures[data.texture_slot_index] = texture;
        data.texture_slot_index++;
    }

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                          * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
                          * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[0];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[1];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 0.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[2];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {1.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_vertex_buffer_ptr->position = transform * data.quad_vertex_positions[3];
    data.quad_vertex_buffer_ptr->color = tint_color;
    data.quad_vertex_buffer_ptr->texture_coordinates = {0.0f, 1.0f};
    data.quad_vertex_buffer_ptr->texture_index = texture_index;
    data.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
    data.quad_vertex_buffer_ptr++;

    data.quad_index_count += 6;

    data.stats.quad_count++;
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                 const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color) {
    DrawRotatedQuad({position.x, position.y, 0}, size, rotation, texture, tiling_factor, tint_color);
}

void Renderer2D::ResetStats() {
    data.stats.draw_calls = 0;
    data.stats.draw_calls = 0;
}

Renderer2D::Statistics Renderer2D::GetStats() {
    return data.stats;
}

void Renderer2D::StartBatch() {
    data.quad_vertex_buffer_ptr = data.quad_vertex_buffer_base;
    data.quad_index_count = 0;
}

void Renderer2D::NextBatch() {
    Flush();
    StartBatch();
}


} // chernoengine2

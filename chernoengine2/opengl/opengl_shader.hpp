//
// Created by shepherd on 26.3.23.
//

#ifndef CHERNOENGINE2_OPENGL_SHADER_HPP
#define CHERNOENGINE2_OPENGL_SHADER_HPP

#include <chernoengine2/renderer/shader.hpp>

#include <string>

namespace chernoengine2 {

class OpenglShader : public Shader {
public:
    explicit OpenglShader(const std::string& filepath);

    void Bind() const override;

    void SetInt(const std::string &name, int value) const override;

    void SetVec3(const std::string &name, const glm::vec3 &vec) const override;

    void SetVec4(const std::string& name, const glm::vec4& vec) const override;

    void SetMat4(const std::string& name, const glm::mat4& mat) const override;

private:
    void CheckCompileErrors(uint32_t shader_id, const std::string &type);

    uint32_t id_;
};

} // chernoengine2

#endif //CHERNOENGINE2_OPENGL_SHADER_HPP

//
// Created by shepherd on 26.2.23.
//

#ifndef CHERNOENGINE2_SHADER_HPP
#define CHERNOENGINE2_SHADER_HPP

#include <string>

#include <glm/glm.hpp>

namespace chernoengine2 {

class Shader {
public:
    explicit Shader(const std::string& filepath);

    void Bind() const;

    void SetBool(const std::string &name, bool value) const;

    void SetInt(const std::string &name, int value) const;

    void SetFloat(const std::string &name, float value) const;

    void SetVec4(const std::string &name, const glm::vec4 &vec) const;

    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    uint32_t GetId() const;

private:
    void CheckCompileErrors(uint32_t shader_id, const std::string &type);

    uint32_t id_;
};

} // chernoengine2

#endif //CHERNOENGINE2_SHADER_HPP

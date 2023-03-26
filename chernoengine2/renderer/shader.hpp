//
// Created by shepherd on 26.2.23.
//

#ifndef CHERNOENGINE2_SHADER_HPP
#define CHERNOENGINE2_SHADER_HPP

#include <string>

#include <glm/glm.hpp>

#include <chernoengine2/core/core.hpp>

namespace chernoengine2 {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;

    static Ref<Shader> Create(const std::string& filepath);

    virtual void SetVec3(const std::string& name, const glm::vec3& vec) const = 0;

    virtual void SetVec4(const std::string& name, const glm::vec4& vec) const = 0;

    virtual void SetMat4(const std::string& name, const glm::mat4& mat) const = 0;

};

} // chernoengine2

#endif //CHERNOENGINE2_SHADER_HPP

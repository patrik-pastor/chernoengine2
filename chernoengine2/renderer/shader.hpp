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
    Shader(const char *vertex_path, const char *fragment_path);

    void Bind() const;

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec4(const std::string &name, const glm::vec4 &vec) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

    uint32_t getId() const;

private:
    void CheckCompileErrors(uint32_t shader_id, const std::string &type);

    uint32_t id_;
};

} // chernoengine2

#endif //CHERNOENGINE2_SHADER_HPP

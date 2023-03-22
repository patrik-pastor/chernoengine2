//
// Created by shepherd on 26.2.23.
//

#include <chernoengine2/renderer/shader.hpp>

#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chernoengine2/core/log.hpp>

namespace chernoengine2 {

void Shader::CheckCompileErrors(uint32_t shader_id, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_id, 1024, nullptr, infoLog);
            LOG_CORE_ERROR("ERROR::SHADER::COMPILATION_ERROR of type: {0}\n{1}", type, infoLog);
        }
    } else {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_id, 1024, nullptr, infoLog);
            LOG_CORE_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {0}\n{1}", type, infoLog);
        }
    }
}

Shader::Shader(const char *vertex_path, const char *fragment_path) {
    // 1. read vertex and fragment source code from files
    std::ifstream vertex_file(vertex_path);
    std::ifstream fragment_file(fragment_path);
    std::stringstream vertex_stream, fragment_stream;
    std::string vertex_code, fragment_code;
    try {
        // 1.1 ensure std::ifstream objects can throw exceptions
        vertex_file.exceptions(std::ifstream::failbit);
        fragment_file.exceptions(std::ifstream::failbit);
        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();
        // 1.2 get the text source code out of the string streams
        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();
    } catch (const std::ifstream::failure& e) {
        LOG_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: {0}", e.what());
    }

    // 2. convert, compile and link sources to shader program
    // 2.1 convert string to c str
    const char *vertex_str = vertex_code.c_str();
    const char *fragment_str = fragment_code.c_str();
    // 2.2.1 vertex shader
    uint32_t vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, 1, &vertex_str, nullptr);
    glCompileShader(vertex_id);
    CheckCompileErrors(vertex_id, "VERTEX");
    // 2.2.2 fragment shader
    uint32_t fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, 1, &fragment_str, nullptr);
    glCompileShader(fragment_id);
    CheckCompileErrors(fragment_id, "FRAGMENT");
    // 2.3 shader program
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_id);
    glAttachShader(id_, fragment_id);
    glLinkProgram(id_);
    CheckCompileErrors(id_, "PROGRAM");
    LOG_CORE_TRACE("Shader linked successfully");
    // 2.4 delete the shaders as they're linked into program and no longer necessary
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void Shader::Bind() const {
    glUseProgram(id_);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

uint32_t Shader::getId() const {
    return id_;
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(getId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& vec) const {
    glUniform4f(glGetUniformLocation(getId(), name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

} // chernoengine2
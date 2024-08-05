//
// Created by 860122023 on 2024/7/29.
//

#ifndef OPENGL_TEST_SHADER_H
#define OPENGL_TEST_SHADER_H

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "string"
#include <sstream>
#include <fstream>
#include <iostream>
#include "Renderer.h"
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};
class Shader {
private:
    std::string m_FilePath;
    unsigned int m_RenderID;
    mutable std::unordered_map<std::string,GLint> m_UniFormLocationCache;
public:
    Shader(const std::string& filePath);
   ~Shader();
    void Bind() const;
    void UnBind() const;

    //set shader
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    ShaderProgramSource ParseShader(const std::string &filepath);
    //set uniforms
    void SetUniform1i(const std::string& name,int value);
    void SetUniform1f(const std::string& name,float value);
    void SetUniform1iv(const std::string& name,GLsizei size,const GLint * value);
    void SetUniform4f(const std::string& name,float v0, float v1,float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& marix);
private:
    bool CompileSharder();
    GLint GetUniformLocation(const std::string& name) const;
};


#endif //OPENGL_TEST_SHADER_H

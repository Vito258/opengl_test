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

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};
class Shader {
private:
    std::string m_FilePath;
    unsigned int m_RenderID;
    std::unordered_map<std::string,unsigned int> m_UniFormLocationCache;
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
    void SetUniform4f(const std::string& name,float v0, float v1,float v2, float v3);

private:
    bool CompileSharder();
    unsigned int GetUniformLocation(const std::string& name);
};


#endif //OPENGL_TEST_SHADER_H

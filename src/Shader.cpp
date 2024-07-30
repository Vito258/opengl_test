//
// Created by 860122023 on 2024/7/29.
//

#include "Shader.h"

Shader::Shader(const std::string &filePath)
:m_FilePath(filePath),m_RenderID(0){
    //读取着色器源码并传递着色器
    ShaderProgramSource shaderProgramSource = ParseShader(filePath);
    m_RenderID = CreateShader(shaderProgramSource.vertex_source, shaderProgramSource.fragment_source);
}

Shader::~Shader() {
    GlCall(glDeleteProgram(m_RenderID));
}
unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    //链接程序
    glLinkProgram(program);
    //对程序进行验证
    glValidateProgram(program);
    return program;
}

/*
 * source 编译器源码
 * */
unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    /* 创建一个shader并返回id */
    unsigned int id = glCreateShader(type);
    /* 转换成传统c语言风格的字符串 */
    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    /* TODO 预期的错误处理 */
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        /* 在堆栈空间临时保存错误信息 */
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "This is " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " message:" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

//读取着色器源码的方法
ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int) type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

void Shader::Bind() const {
    GlCall(glUseProgram(m_RenderID));
}

void Shader::UnBind() const {
    GlCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string &name, int value) {
    GlCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string &name, float value) {
    GlCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GlCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4& marix) {
    GlCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&marix[0][0]));
}

bool Shader::CompileSharder() {
    return false;
}

int Shader::GetUniformLocation(const std::string &name) {
    if(m_UniFormLocationCache.find(name) != m_UniFormLocationCache.end())
        return m_UniFormLocationCache[name];
    GlCall(int location = glGetUniformLocation(m_RenderID, name.c_str()));
    if(location == -1)
        std::cout<<"This uniform :"<<name<<"doesn't exist..."<<std::endl;
    m_UniFormLocationCache[name] = location;
    return location;
}

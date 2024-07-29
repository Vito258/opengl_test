#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "string"
#include <sstream>
#include <fstream>
//#include "Renderer.h"
//#include "IndexBuffer.h"
//#include "VertexBuffer.h"
//#include "VertexArray.h"
//#include "Shader.h"

//struct ShaderProgramSource {
//    std::string vertex_source;
//    std::string fragment_source;
//};
//
////读取着色器源码的方法
//static ShaderProgramSource ParseShader(const std::string &filepath) {
//    std::ifstream stream(filepath);
//    enum class ShaderType {
//        NONE = -1, VERTEX = 0, FRAGMENT = 1
//    };
//    std::string line;
//    std::stringstream ss[2];
//    ShaderType type = ShaderType::NONE;
//    while (getline(stream, line)) {
//        if (line.find("#shader") != std::string::npos) {
//            if (line.find("vertex") != std::string::npos) {
//                type = ShaderType::VERTEX;
//            } else if (line.find("fragment") != std::string::npos) {
//                type = ShaderType::FRAGMENT;
//            }
//        } else {
//            ss[(int) type] << line << '\n';
//        }
//    }
//    return {ss[0].str(), ss[1].str()};
//}
//
///*
// * source 编译器源码
// * */
//static unsigned int CompileShader(unsigned int type, const std::string &source) {
//    /* 创建一个shader并返回id */
//    unsigned int id = glCreateShader(type);
//    /* 转换成传统c语言风格的字符串 */
//    const char *src = source.c_str();
//
//    glShaderSource(id, 1, &src, nullptr);
//    glCompileShader(id);
//
//    /* TODO 预期的错误处理 */
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE) {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//        /* 在堆栈空间临时保存错误信息 */
//        char *message = (char *) alloca(length * sizeof(char));
//        glGetShaderInfoLog(id, length, &length, message);
//        std::cout << "This is " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " message:" << std::endl;
//        std::cout << message << std::endl;
//        glDeleteShader(id);
//        return 0;
//    }
//
//    return id;
//}
//
//static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
//    unsigned int program = glCreateProgram();
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    //
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//
//    //链接程序
//    glLinkProgram(program);
//    //对程序进行验证
//    glValidateProgram(program);
//    return program;
//}

//int main() {
//    GLFWwindow *window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//
//    // 设置期望的OPENGL 版本
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//    //设置核心配置文件
//    //这样设置会报错，提示1282 既没有顶点数组对象，需要自己显式设置
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    //设置兼容配置文件
//    //这样的话系统会默认设置一个顶点数组对象，它被绑定并供我们使用
//    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    //用于得到一个渲染openGL的上下文
//    glfwMakeContextCurrent(window);
//
//    //同步v-sync 或者时主频刷新率
//    glfwSwapInterval(1);
//
//    //改为使用GLEW
//    GLenum err = glewInit();
//    if (GLEW_OK != err) {
//        /* Problem: glewInit failed, something is seriously wrong. */
//        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//    }
//    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//    {
//        float positions[] = {
//                -0.5f, -0.5f,
//                0.5f, -0.5f,
//                0.5f, 0.5f,
//                -0.5f, 0.5f
//        };
//
//        unsigned int indices[] = {
//                0, 1, 2,
//                2, 3, 0
//        };
//
//        //显式创建一个顶点数组
//        VertexArray va;
//
//        //创建顶点缓冲区 会自动绑定
//        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
//        //VertexBuffer *vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));   在堆栈上创建缓冲区，最好别这样做
//
//        VertexBufferLayout layout;
//        GlCall(layout.push<float>(2));
//        GlCall(va.AddBuffer(vb, layout));
//
//        //索引缓冲区的设置
//        IndexBuffer ib(indices, 6);
//
//        //读取着色器源码
//        Shader shader("../res/shaders/Basic.shader");
//        shader.Bind();
//        shader.SetUniform4f("u_Color", 0.5f, 0.3f, 0.8f, 1.0f);
//
//        // 解绑
//        va.UnBind();
//        shader.UnBind();
//        vb.UnBind();
//        ib.UnBind();
//
//        float r = 0.5f;
//        float increment = 0.05f;
//        /* Loop until the user closes the window */
//        while (!glfwWindowShouldClose(window)) {
//            /* Render here */
//            GlCall(glClear(GL_COLOR_BUFFER_BIT));
//
//            shader.Bind();
//            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//
//            //在此绑定顶点数组,发现只绑定顶点数组对象和和索引缓冲区，之前的代码注掉，程序依旧可以运行
//            GlCall(va.Bind());
//            //最后绑定到索引缓冲区
//            GlCall(ib.Bind());
//
//            //调用 drawcall 方法绘制
//            /* 没有索引缓冲区时可以使用这个方法 */
//            //glDrawArrays(GL_TRIANGLES,0,6);
//
//            /* 有索引缓冲区时可以使用这个方法 */
//            GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//
//
//            /* Swap front and back buffers */
//            GlCall(glfwSwapBuffers(window));
//
//            /* Poll for and process events */
//            glfwPollEvents();
//
//            if (r > 1.0f) {
//                increment = -0.05f;
//            } else if (r < 0.0f) {
//                increment = 0.05f;
//            }
//            r += increment;
//        }
//    }
//    glfwTerminate();
//    return 0;
//}

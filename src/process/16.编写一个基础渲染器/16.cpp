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
//        //创建自定义渲染器的实例
//        Renderer renderer;
//
//        float r = 0.5f;
//        float increment = 0.05f;
//        /* Loop until the user closes the window */
//        while (!glfwWindowShouldClose(window)) {
//            /* Render here */
//            renderer.Clear();
//
//            shader.Bind();
//            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//
//            // 渲染器绘制
//            renderer.Draw(va,ib,shader);
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

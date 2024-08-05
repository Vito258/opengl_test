//
// Created by 860122023 on 2024/8/5.
//
#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "string"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../tests/TestClearColor.h"
#include "../tests/TestTexture2D.h"


//渲染两个正方形
int main() {
        GLFWwindow *window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;


        // 设置期望的OPENGL 版本
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        //设置核心配置文件
        //这样设置会报错，提示1282 既没有顶点数组对象，需要自己显式设置
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(1080, 970, "Hello World", NULL, NULL);
        if (!window) {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        //用于得到一个渲染openGL的上下文
        glfwMakeContextCurrent(window);

        //同步v-sync 或者时主频刷新率
        glfwSwapInterval(1);

        //改为使用GLEW
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        }
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    {
        float positions[] = {
                -0.2f, -0.2f,  //0
                0.2f, -0.2f,   //1
                0.2f, 0.2f,    //2
                -0.2f, 0.2f,   //3

                0.4f, -0.2f,   //4
                0.8f,-0.2f,  //5
                0.8f,0.2f,  //6
                0.4f,0.2f    //7
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0,
                4,5,6,
                6,7,4
        };

        //显式创建一个顶点数组
        VertexArray va;

        //创建顶点缓冲区 会自动绑定
        VertexBuffer vb(positions, 8 * 2 * sizeof(float));

        VertexBufferLayout layout;
        GlCall(layout.push<float>(2));
        GlCall(va.AddBuffer(vb, layout));

        //索引缓冲区的设置
        IndexBuffer ib(indices, 12);

        //读取着色器源码
        Shader shader("../res/shaders/SandboxLayer.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        // 解绑
        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ib.UnBind();

        //创建自定义渲染器的实例
        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();
            shader.Bind();

            // 渲染器绘制
            renderer.Draw(va,ib,shader);

            /* Swap front and back buffers */
            GlCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

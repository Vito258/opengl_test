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

struct Vertex {
    float Positions[2];
    float Color[4];
    float TexCoords[2];
    float TexID;
};

static std::array<Vertex, 4> CreateQuad(float x, float y, float textureID) {
    float size = 0.4f;
    Vertex v0 = {{x, y}, {0.18f, 0.6f, 0.96f, 1.0f}, {0.0f, 0.0f}, textureID};
    Vertex v1 = {{x + size, y}, {0.18f, 0.6f, 0.96f, 1.0f}, {1.0f, 0.0f}, textureID};;
    Vertex v2 = {{x + size, y + size}, {0.18f, 0.6f, 0.96f, 1.0f}, {1.0f, 1.0f}, textureID};;
    Vertex v3 = {{x, y + size}, {0.18f, 0.6f, 0.96f, 1.0f}, {0.0f, 1.0f}, textureID};;
    return {v0, v1, v2, v3};
}

//渲染两个正方形
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
//    window = glfwCreateWindow(1080, 970, "Hello World", NULL, NULL);
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
//
//    {
//        float position[2] = { -0.2f, -0.2f};
//        auto q1 = CreateQuad(position[0], position[1], 0.0f);
//        auto q2 = CreateQuad(0.4f, -0.2f, 1.0f);
//
//        Vertex vertices[8];
//        memcpy(vertices, q1.data(), q1.size() * sizeof(Vertex));
//        memcpy(vertices + q1.size(), q2.data(), q2.size() * sizeof(Vertex));
//        unsigned int indices[] = {
//                0, 1, 2,
//                2, 3, 0,
//                4, 5, 6,
//                6, 7, 4
//        };
//
//        //显式创建一个顶点数组
//        VertexArray va;
//
//        //创建顶点缓冲区 会自动绑定
////        VertexBuffer vb(vetices, 8 * 9 * sizeof(float));
//        GlCall(VertexBuffer vb(vertices, sizeof(vertices), VertexBuffer::DYNAMIC));
//        VertexBufferLayout layout;
//        GlCall(layout.push<float>(sizeof(Vertex::Positions) / sizeof(Vertex::Positions[0])));
//        GlCall(layout.push<float>(sizeof(Vertex::Color) / sizeof(Vertex::Color[0])));
//        GlCall(layout.push<float>(sizeof(Vertex::TexCoords) / sizeof(Vertex::TexCoords[0])));
//        GlCall(layout.push<float>(sizeof(Vertex::TexID) / sizeof(Vertex::TexID)));
//        GlCall(va.AddBuffer(vb, layout));
//
//        //索引缓冲区的设置
//        IndexBuffer ib(indices, 12);
//
//        //读取着色器源码
//        Shader shader("../res/shaders/SandboxLayer.shader");
//        shader.Bind();
//
//        //设置纹理的数组
//        int samplers[2] = {0, 1};
//        //创建纹理
//        Texture textureOne("../res/textures/Texture.png");
//        Texture textureTwo("../res/textures/Menma.png");
//
//        textureOne.Bind(samplers[0]);
//        textureTwo.Bind(samplers[1]);
//
//        shader.SetUniform1iv("u_Textures", 2, samplers);
//        // 解绑
//        va.UnBind();
//        shader.UnBind();
//        vb.UnBind();
//        ib.UnBind();
//
//        //创建自定义渲染器的实例
//        Renderer renderer;
//
//        // 创建一个imgui使用的上下文
//        IMGUI_CHECKVERSION();
//        ImGui::CreateContext();
//
//        // Setup consts of imgui
//        const char *glsl_version = "#version 130";    // Our state
//        ImGuiIO &io = ImGui::GetIO();
//        (void) io;
//
//        // Setup Dear ImGui style
//        ImGui::StyleColorsDark();
//
//        // 进行imgui 初始化
//        ImGui_ImplGlfw_InitForOpenGL(window, true);
//#ifdef __EMSCRIPTEN__
//        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
//#endif
//        ImGui_ImplOpenGL3_Init(glsl_version);
//
//
//        /* Loop until the user closes the window */
//        while (!glfwWindowShouldClose(window)) {
//            /* Render here */
//            renderer.Clear();
//
//            // 开启一个用于imgui 的新帧，在为这帧开始写任何imgui 代码之前需要有新的帧函数调用
//            ImGui_ImplOpenGL3_NewFrame();
//            ImGui_ImplGlfw_NewFrame();
//            ImGui::NewFrame();
//
//            shader.Bind();
//            // 设置模型视图投影矩阵的同一变量
////            shader.SetUniformMat4f("u_MVP", mvp);
//
//            // 渲染器绘制
//            renderer.Draw(va, ib, shader);
//
//            //Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
//            {
//                ImGui::Begin("Hello, world!"); // Begin a new window
//                if (ImGui::SliderFloat2("translation", &position[0], -1.0f, 1.0f)) {
//                    q1 = CreateQuad(position[0], position[1], 0.0f);
//                    memcpy(vertices, q1.data(), q1.size() * sizeof(Vertex));
//
//                    // 更新顶点缓冲区的内容
//                    GlCall(vb.UpdateData(vertices, q1.size() * sizeof(Vertex)));
//                }
//                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//                ImGui::End();
//            }
//            ImGui::Render();
//            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//            /* Swap front and back buffers */
//            GlCall(glfwSwapBuffers(window));
//
//            /* Poll for and process events */
//            glfwPollEvents();
//        }
//    }
//    //在glfwTerminate()之前调用
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}

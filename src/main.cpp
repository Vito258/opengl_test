#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "string"
#include <sstream>
#include <fstream>
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

    //设置兼容配置文件
    //这样的话系统会默认设置一个顶点数组对象，它被绑定并供我们使用
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    // window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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
        //默认情况下opengl 会使用src 的颜色通道直接覆盖掉 dest的颜色通道
        //启用混合
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GlCall(glEnable(GL_BLEND));

        Renderer renderer;

        // 创建一个imgui使用的上下文
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup consts of imgui
        const char *glsl_version = "#version 130";    // Our state

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // 进行imgui 初始化
        ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
        ImGui_ImplOpenGL3_Init(glsl_version);

        test::Test* currentTest = nullptr;
        test::TestMenu* pTestMenu = new test::TestMenu(currentTest);
        currentTest = pTestMenu;

        // 注册测试
        pTestMenu->RegisterTest<test::TestClearColor>("clear color");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            //测试完成后回到黑色
            GlCall(glClearColor(0.0f,0.0f,0.0f,1.0f));

            /* Render here */
            renderer.Clear();

            // 开启一个用于imgui 的新帧，在为这帧开始写任何imgui 代码之前需要有新的帧函数调用
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest) {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("current test");
                if (currentTest != pTestMenu && ImGui::Button("<=")) {
                    delete currentTest;
                    currentTest = pTestMenu;
                }
                currentTest->OnImguiRender();
                ImGui::End();
            }


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            GlCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            glfwPollEvents();
        }
        delete currentTest;
        if(currentTest != pTestMenu)
            delete pTestMenu;

    }
    //在glfwTerminate()之前调用
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

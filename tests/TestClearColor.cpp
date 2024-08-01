//
// Created by 111 on 2024/8/1.
//

#include "TestClearColor.h"
#include "Renderer.h"
#include <GL/glew.h>
#include <imgui/imgui.h>

namespace test{
    Test::Test() {
        // Constructor implementation
    }

    Test::~Test() {
        // Destructor implementation
    }
    TestClearColor::TestClearColor()
            : m_ClearColor{0.2f,0.3f,0.8f,1.0f}{

    }

    TestClearColor::~TestClearColor() {

    }

    void TestClearColor::OnUpdate(float deltaTime) {
    }

    void TestClearColor::OnRender() {
        GlCall(glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]));
        GlCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImguiRender() {
        ImGui::ColorEdit4("ColorEdit",m_ClearColor);
    }
}

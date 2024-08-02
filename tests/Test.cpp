//
// Created by 860122023 on 2024/8/2.
//
#include "Test.h"
#include "imgui/imgui.h"

namespace test {
    TestMenu::TestMenu(Test*& current_Pointer)
            : m_CurrentTest(current_Pointer) {
    }

    void TestMenu::OnImguiRender() {
        for (auto &test: m_Tests) {
            if (ImGui::Button(test.first.c_str())) {
                m_CurrentTest = test.second();
            }

        }
    }

}
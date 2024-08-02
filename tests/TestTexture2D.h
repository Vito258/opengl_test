//
// Created by 860122023 on 2024/8/2.
//

#ifndef OPENGL_TEST_TESTTEXTURE2D_H
#define OPENGL_TEST_TESTTEXTURE2D_H
#include <GL/gl.h>
#include "Test.h"
#include "imgui/imgui.h"
#include "glm/vec3.hpp"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"


namespace test{
    class TestTexture2D : public Test{
    public:
        TestTexture2D();
        ~TestTexture2D() override;

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImguiRender() override;

    private:
        glm::vec3 m_TranslationA;
        glm::vec3 m_TranslationB;
        ImGuiIO &m_Io = ImGui::GetIO();
        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::mat4 m_Model;
    };
}



#endif //OPENGL_TEST_TESTTEXTURE2D_H

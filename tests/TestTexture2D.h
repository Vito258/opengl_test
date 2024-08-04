//
// Created by 860122023 on 2024/8/2.
//

#ifndef OPENGL_TEST_TESTTEXTURE2D_H
#define OPENGL_TEST_TESTTEXTURE2D_H
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <memory>
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
        std::unique_ptr<VertexArray> m_Vao;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        glm::mat4 m_Proj,m_View,m_Model;
    };
}



#endif //OPENGL_TEST_TESTTEXTURE2D_H

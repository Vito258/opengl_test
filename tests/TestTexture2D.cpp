//
// Created by 860122023 on 2024/8/2.
//
#include "TestTexture2D.h"
test::TestTexture2D::TestTexture2D()
   :m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(200, 200, 0),m_TranslationB(400, 200, 0){
    float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,    // 0
            50.0f, -50.0f, 1.0f, 0.0f,    // 1
            50.0f, 50.0f, 1.0f, 1.0f,     // 2
            -50.0f, 50.0f, 0.0f, 1.0f   //  3
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };
    //启用混合
    GlCall(glEnable(GL_BLEND));
    GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_Vao = std::make_unique<VertexArray>();
    m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");

    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    GlCall(layout.push<float>(2));
    // 加入纹理坐标后新push 两个float
    GlCall(layout.push<float>(2));
    GlCall(m_Vao -> AddBuffer(*m_VertexBuffer, layout));

    //索引缓冲区的设置
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    // 读取着色器源码
    m_Shader -> Bind();
    m_Texture = std::make_unique<Texture>("../res/textures/Texture.png");
    m_Texture -> Bind(0);
    m_Shader -> SetUniform1i("u_Texture", 0);
}

test::TestTexture2D::~TestTexture2D() {

}

void test::TestTexture2D::OnUpdate(float deltaTime) {

}

void test::TestTexture2D::OnRender() {
    GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GlCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;
    {

        // 创建模型矩阵，将对象向右移动200，向上移动200
        glm::mat4 model  = glm::translate(glm::mat4(1.0f), m_TranslationA);
        // 这里的mvp就是模型视图投影矩阵，opengl中的矩阵乘法是从右到左，所以是模型*视图*投影
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader -> SetUniformMat4f("u_MVP", mvp);
        // 渲染器绘制
        renderer.Draw(*m_Vao, *m_IndexBuffer, *m_Shader);
    }

    {
        // 创建模型矩阵，将对象向右移动200，向上移动200
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        // 这里的mvp就是模型视图投影矩阵，opengl中的矩阵乘法是从右到左，所以是模型*视图*投影
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader-> SetUniformMat4f("u_MVP", mvp);
        // 渲染多个对象
        renderer.Draw(*m_Vao, *m_IndexBuffer, *m_Shader);
    }
}

void test::TestTexture2D::OnImguiRender() {
    ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

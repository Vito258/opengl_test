//
// Created by 860122023 on 2024/8/2.
//
#include "TestTexture2D.h"
test::TestTexture2D::TestTexture2D()
   :m_TranslationA(200, 200, 0),m_TranslationB(400, 200, 0){
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
    GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GlCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    GlCall(layout.push<float>(2));
    // 加入纹理坐标后新push 两个float
    GlCall(layout.push<float>(2));
    GlCall(va.AddBuffer(vb, layout));

    //索引缓冲区的设置
    IndexBuffer ib(indices, 6);

    m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    // 读取着色器源码
    Shader shader("../res/shaders/Basic.shader");
    shader.Bind();
    Texture texture("../res/textures/Texture.png");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    // 解绑
    va.UnBind();
    shader.UnBind();
    vb.UnBind();
    ib.UnBind();

}

test::TestTexture2D::~TestTexture2D() {

}

void test::TestTexture2D::OnUpdate(float deltaTime) {

}

//void test::TestTexture2D::OnRender() {
//    GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
//    GlCall(glClear(GL_COLOR_BUFFER_BIT));
//    Renderer renderer;
//    {
//        // 创建模型矩阵，将对象向右移动200，向上移动200
//        m_Model = glm::translate(glm::mat4(1.0f), m_TranslationA);
//        // 这里的mvp就是模型视图投影矩阵，opengl中的矩阵乘法是从右到左，所以是模型*视图*投影
//        glm::mat4 mvp = m_Proj * m_View * m_Model;
//        shader.SetUniformMat4f("u_MVP", mvp);
//        // 渲染器绘制
//        renderer.Draw(va, ib, shader);
//    }
//
//    {
//        // 创建模型矩阵，将对象向右移动200，向上移动200
//        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
//        // 这里的mvp就是模型视图投影矩阵，opengl中的矩阵乘法是从右到左，所以是模型*视图*投影
//        glm::mat4 mvp = proj * view * model;
//        shader.SetUniformMat4f("u_MVP", mvp);
//        // 渲染多个对象
//        renderer.Draw(va, ib, shader);
//    }
//}

void test::TestTexture2D::OnImguiRender() {
    ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_Io.Framerate, m_Io.Framerate);

}

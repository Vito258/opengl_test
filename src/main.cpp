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
        //新增的為紋理坐標
//        float positions[] = {
//                -0.5f, -0.5f, 0.0f, 0.0f,    // 0
//                0.5f, -0.5f, 1.0f, 0.0f,    // 1
//                0.5f, 0.5f, 1.0f, 1.0f,     // 2
//                -0.5f, 0.5f, 0.0f, 1.0f   //  3
//        };

        //将视窗分辨率改为960×540 之后
        float positions[] = {
                100.0f, 100.0f, 0.0f, 0.0f,    // 0
                200.0f, 100.0f, 1.0f, 0.0f,    // 1
                200.0f, 200.0f, 1.0f, 1.0f,     // 2
                100.0f, 200.0f, 0.0f, 1.0f   //  3
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        //默认情况下opengl 会使用src 的颜色通道直接覆盖掉 dest的颜色通道
        //启用混合
        GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GlCall(glEnable(GL_BLEND));
        //显式创建一个顶点数组
        VertexArray va;

        //创建顶点缓冲区 会自动绑定
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        //VertexBuffer *vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));   在堆栈上创建缓冲区，最好别这样做

        VertexBufferLayout layout;
        GlCall(layout.push<float>(2));
        // 加入纹理坐标后新push 两个float
        GlCall(layout.push<float>(2));
        GlCall(va.AddBuffer(vb, layout));

        //索引缓冲区的设置
        IndexBuffer ib(indices, 6);

        // 创建投影矩阵，使用glm::ortho 这将会产生一个正交矩阵
        // 通过指定四个位置设置了边界以及纵横比，这里是4：3
        // 归根到底，这个正交投影矩阵和上面的顶点位置相乘，将他们转换到-1到1的空间
        // 以x 的边界举例，-2.0f和2.0f之间的中点是0，原点的x=0
        // 假设上面的第一个顶点（-0.5f, -0.5f,0.0f,0.0f,）第一个值-0.5f，在-2.0f和0之间（最左边界）占1/4 ,所以当他与矩阵相乘并转换到-1到1的空间后，就由-0.5f变成了-0.2f
        // 这发生在我们的vertex 的shader里面
        // glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        // 将视窗分辨率改为960×540 之后
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        // 创建视图矩阵，将相机向右移动100.0f，既将对象向左移动100.0f
        glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3 (-100,0,0));

        // 创建模型矩阵，将对象向右移动200，向上移动200
        glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3 (200,200,0));
        // 这里的mvp就是模型视图投影矩阵，opengl中的矩阵乘法是从右到左，所以是模型*视图*投影
        glm::mat4 mvp = proj * view * model;

        //读取着色器源码
        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.5f, 0.3f, 0.8f, 1.0f);

        Texture texture("../res/textures/Texture.png");
        texture.Bind(2);
        shader.SetUniform1i("u_Texture", 2);
        // 设置
        shader.SetUniformMat4f("u_MVP", mvp);

        // 解绑
        va.UnBind();
        shader.UnBind();
        vb.UnBind();
        ib.UnBind();

        //创建自定义渲染器的实例
        Renderer renderer;

        float r = 0.5f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            // shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            // 渲染器绘制
            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            GlCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            glfwPollEvents();

            if (r > 1.0f) {
                increment = -0.05f;
            } else if (r < 0.0f) {
                increment = 0.05f;
            }
            r += increment;
        }
    }
    glfwTerminate();
    return 0;
}

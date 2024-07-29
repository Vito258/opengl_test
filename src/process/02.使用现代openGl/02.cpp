//#include <iostream>
//#include <GL/glew.h>
//#include "GLFW/glfw3.h"
//使用glew 有两点：
//1、有渲染openGl 的上下文
//2、在之后使用glewInit();然后使用glew
//int main() {
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    //用于得到一个渲染openGL的上下文
//    glfwMakeContextCurrent(window);
//
//    //改为使用GLEW
//    GLenum err = glewInit();
//    if (GLEW_OK != err)
//    {
//        /* Problem: glewInit failed, something is seriously wrong. */
//        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//    }
//    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//
//    //打印当前openGl版本
//    std::cout<<glGetString(GL_VERSION)<<std::endl;
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glBegin(GL_TRIANGLES);
//
//        //绘制3个顶点
//        glVertex2f(-0.5f,-0.5f);
//        glVertex2f(0.0f,0.5f);
//        glVertex2f(0.5f,-0.5f);
//
//        glEnd();
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}

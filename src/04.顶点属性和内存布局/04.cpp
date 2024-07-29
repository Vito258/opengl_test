#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
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
//    float positions[6]={
//            -0.5f,-0.5f,
//            0.0f,0.5f,
//            0.5f,-0.5f,
//    };
//    unsigned int buffer;
//    /* 生成一个缓冲区，并定义一个id */
//    glGenBuffers(1,&buffer);
//    /* 绑定这个缓冲区 */
//    glBindBuffer(GL_ARRAY_BUFFER,buffer);
//    /* 定义缓冲区的大小 */
//    glBufferData(GL_ARRAY_BUFFER,6 * sizeof(float),positions,GL_STATIC_DRAW);
//    /* 开启顶点属性 */
//    glEnableVertexAttribArray(0);
//
//    /* 为 Atrtribute 变量制定VBO中的数据。 */
//    // index: 顶点参数的索引，位置0，纹理坐标1，法线2
//    // size, Attribute 变量数据是由几个元素组成的， x,y,z,w ; 最多四个。
//    // type, Attribute 变量数据 的数据类型
//    // normalized, 是否归一化， 编程1.0以内的数，这样做的目的是减少向gpu传递数据的带宽。
//    // stride,一个顶点的内存大小，等于sizeof(float)*参数的数量，参数的数量即数据的数量
//    // pointer,顶点参数的内存地址，例如一个三维顶点(float) ，位置的pointer就是0，纹理坐标的pointer就是12 = 3*sizeof(float),法线的pointer为 20 = 3*sizeof(float) + 2*sizeof(float)
//    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        /* 没有索引缓冲区时可以使用这个方法 */
//         glDrawArrays(GL_TRIANGLES,0,3);
//
//        /* 有索引缓冲区时可以使用这个方法 */
//        // glDrawElements();
//
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

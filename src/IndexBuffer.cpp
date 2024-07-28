//
// Created by 111 on 2024/7/25.
//

#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
  :m_count(count){
    /* 生成一个缓冲区，并定义一个id */
    glGenBuffers(1,&m_RendererId);
    /* 绑定这个缓冲区 */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererId);
    /* 定义缓冲区的大小 */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof (unsigned int), data,GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    // 析构函数中调用 glGetError时，，windows 关闭视窗之后是在glfwTerminate(); 之后调用，会有一个无限循环的异常
    // 解决方法
    // 1.在堆上创建VertexBuffer对象，然后在glfwTerminate(); 之前delete 掉，确保析构函数在其之后执行
    // 2.在glfwTerminate(); 之前设置{}作用域
    GlCall(glDeleteBuffers(1,&m_RendererId));
};

void IndexBuffer::Bind() const{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererId));
}

void IndexBuffer::UnBind() const{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

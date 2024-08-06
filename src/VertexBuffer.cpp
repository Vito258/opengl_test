//
// Created by 111 on 2024/7/25.
//

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    /* 生成一个缓冲区，并定义一个id */
    glGenBuffers(1,&m_RendererId);
    /* 绑定这个缓冲区 */
    glBindBuffer(GL_ARRAY_BUFFER,m_RendererId);
    /* 定义缓冲区的大小 */
    glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1,&m_RendererId);
};

void VertexBuffer::Bind() const {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER,m_RendererId));
}

void VertexBuffer::UnBind() const{
    GlCall((GL_ARRAY_BUFFER,0));
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size, unsigned int type) {
    /* 生成一个缓冲区，并定义一个id */
    glGenBuffers(1,&m_RendererId);
    /* 绑定这个缓冲区 */
    glBindBuffer(GL_ARRAY_BUFFER,m_RendererId);
    /* 定义缓冲区的大小 */
    if(type == DYNAMIC){
        glBufferData(GL_ARRAY_BUFFER,size,data,GL_DYNAMIC_DRAW);
    }else if(type == STATIC){
        glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
    }else if(type == SUB){
        glBufferSubData(GL_ARRAY_BUFFER,0,size,data);
    }
}

void VertexBuffer::UpdateData(const void* data, unsigned int size) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

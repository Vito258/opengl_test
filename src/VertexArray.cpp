//
// Created by 111 on 2024/7/25.
//

#include "VertexArray.h"

VertexArray::VertexArray()
{
    GlCall(glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray() {
    GlCall(glDeleteVertexArrays(1,&m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout) {
    //绑定顶点数组
    Bind();
    // 绑定实际的缓存区elements = {const std::vector<VertexBufferElement> &}
    vb.Bind();
    // 设置布局
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    // 循环Elements
    for(unsigned int i=0;i<elements.size();i++){
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                              reinterpret_cast<const void *>(offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const {
    GlCall(glBindVertexArray(m_RenderID));
}

void VertexArray::UnBind() const {
    GlCall(glBindVertexArray(0));
}

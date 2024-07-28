#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
//
// Created by 111 on 2024/7/25.
//

// 把顶点数组对象抽象成一个类
class VertexArray {
private:
    unsigned int m_RenderID;
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);
    void Bind() const;
    void UnBind() const;
};


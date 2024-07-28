#pragma once
//
// Created by 111 on 2024/7/25.
//
class VertexBuffer {
private:
    unsigned int m_RendererId{};
public:
    VertexBuffer(const void* data,unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;

};

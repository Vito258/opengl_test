//
// Created by 111 on 2024/7/25.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
class VertexBuffer {
private:
    unsigned int m_RendererId{};
public:
    VertexBuffer(const void* data,unsigned int size);
    VertexBuffer(const void* data,unsigned int size,unsigned int type);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;

    enum DrawType{
        STATIC = 0,
        DYNAMIC = 1,
        SUB = 2
    };

    void UpdateData(const void *data, unsigned int size) const;
};
#endif // VERTEXBUFFER_H
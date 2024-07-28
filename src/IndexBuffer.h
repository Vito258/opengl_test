//
// Created by 111 on 2024/7/25.
//
class IndexBuffer {
private:
    unsigned int m_RendererId;

    unsigned int m_count;
public:
    IndexBuffer(const unsigned int*  data,unsigned int size);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

};

//
// Created by 111 on 2024/7/25.
//
#include <vector>
#include "GL/glew.h"
#include "Renderer.h"

struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;      // 判断是否标准化
    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
        }
        return 0;
    }
};

template<typename T>
struct identity {
    typedef T type;
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout() : m_Stride(0) {}

//    template<typename T>
//    void push(unsigned int count) {
//        static_assert(false, "Unsupported type");
//    }

    template<typename R>
    void push(unsigned int count) {
        TPush(identity<R>(), count);
    }

    template<typename R>
    void TPush(identity<R>, unsigned int count) {
//        static_assert(false, "Unsupported type");
        static_assert(sizeof(R) == 0, "Unsupported type");
    }

    void TPush(identity<float>, unsigned int count) {
        m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void TPush(identity<unsigned int>, unsigned int count) {
        m_Elements.push_back({count,GL_UNSIGNED_INT, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void TPush(identity<unsigned char>, unsigned int count) {
        m_Elements.push_back({count, GL_UNSIGNED_BYTE, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }

    inline unsigned int GetStride() const { return m_Stride; }
};


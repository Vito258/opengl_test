//
// Created by 111 on 2024/7/29.
//

#ifndef OPENGL_TEST_TEXTURE_H
#define OPENGL_TEST_TEXTURE_H
#include "string"

class Texture {
private:
    unsigned int m_RenderID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width,m_Height,m_BPP;

public:
    Texture(const std::string& filePath);
    ~Texture();

    void Bind(unsigned int slots = 0) const;
    void Unbind() const;

    inline int GetWidth() const{
        return m_Width;
    }
    inline int GetHeight() const {
        return m_Height;
    };
};


#endif //OPENGL_TEST_TEXTURE_H

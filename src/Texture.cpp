//
// Created by 111 on 2024/7/29.
//

#include "Texture.h"
#include "Renderer.h"
#include "vendor/stb_image/stb_image.h"
Texture::Texture(const std::string &filePath)
        : m_RenderID(0), m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {

    //垂直反转纹理，查看纹理的类型是否需要反转
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(filePath.c_str(),&m_Width,&m_Height,&m_BPP,4);

    GlCall(glGenTextures(1, &m_RenderID));
    GlCall(glBindTexture(GL_TEXTURE_2D,m_RenderID));

    // 对于纹理必须指定这四个参数，如果没有就会漆黑一片，没有默认值
    // 如果需要渲染的比它的实际像素要小，进行缩小
    GlCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR));
    // 反之进行扩大
    GlCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR));
    // 指定嵌入模式
    GlCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
    GlCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));

    // 将数据传送给OpenGl
    // 内部格式是OpenGl 内部存储数据数据的格式，格式是我们传递给OpenGl 数据的格式，也就是m_LocalBuffer
    GlCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_LocalBuffer));

    // 解绑我们的纹理
    GlCall(glBindTexture(GL_TEXTURE_2D,0));

    if(m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
    // 在显卡中删除我们的纹理
    GlCall(glDeleteTextures(1,&m_RenderID));
}

void Texture::Bind(unsigned int slot) const {
    //指定插槽
    GlCall(glActiveTexture(GL_TEXTURE0 + slot));
    GlCall(glBindTexture(GL_TEXTURE_2D,m_RenderID));
}

void Texture::Unbind() const {
    GlCall(glBindTexture(GL_TEXTURE_2D,0));
}

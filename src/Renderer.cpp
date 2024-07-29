//
// Created by 111 on 2024/7/25.
//

#include "Renderer.h"

void GlClearError() {
    while (glGetError() != GL_NO_ERROR) {
        std::cout << "there is a gl_error" << std::endl;
    };
}

/* 打印Error 的方法 */
bool GlLogCall(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OPENGL ERROR]:" << error << " function:" << function << " file:" << file << " \n Line: " << line
                  << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const{
    shader.Bind();

    GlCall(va.Bind());
    //最后绑定到索引缓冲区
    GlCall(ib.Bind());

    /* 有索引缓冲区时可以使用这个方法 */
    GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
    GlCall(glClear(GL_COLOR_BUFFER_BIT));
}

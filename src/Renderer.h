//
// Created by 111 on 2024/7/25.
//
#ifndef OPENGL_TEST_RENDERER_H
#define OPENGL_TEST_RENDERER_H


//断言,如果函数返回false ,在代码中插入断点并中断调试器
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Shader;
class VertexArray;
#define ASSERT(expr) do { if(!(expr)) __builtin_trap(); } while(0)
#define GlCall(expr) GlClearError();\
expr;\
ASSERT(GlLogCall(#expr,__FILE__,__LINE__))
//使用glGetError 排除错误
/* 清除Error 的方法 */
void GlClearError();

/* 打印Error 的方法 */
bool GlLogCall(const char* function, const char* file, int line);

class Renderer{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
#endif //OPENGL_TEST_RENDERER_H

#pragma once
//
// Created by 111 on 2024/7/25.
//
#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#ifndef OPENGL_TEST_RENDERER_H
#define OPENGL_TEST_RENDERER_H

//断言,如果函数返回false ,在代码中插入断点并中断调试器
#define ASSERT(expr) do { if(!(expr)) __builtin_trap(); } while(0)
#define GlCall(expr) GlClearError();\
expr;\
ASSERT(GlLogCall(#expr,__FILE__,__LINE__))
//使用glGetError 排除错误
/* 清除Error 的方法 */
void GlClearError();

/* 打印Error 的方法 */
bool GlLogCall(const char* function, const char* file, int line);

#endif //OPENGL_TEST_RENDERER_H

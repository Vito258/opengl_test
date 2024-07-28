//
// Created by 111 on 2024/7/25.
//

#include "Renderer.h"
#include <iostream>
void GlClearError()
{
while(glGetError() != GL_NO_ERROR){
std::cout<<"there is a gl_error"<<std::endl;
};
}

/* 打印Error 的方法 */
bool GlLogCall(const char* function, const char* file, int line)
{
while(GLenum error = glGetError())
{
std::cout<<"[OPENGL ERROR]:"<<error<<" function:"<<function<< " file:"<<file<<" \n Line: "<< line <<std::endl;
return false;
}
return true;
}
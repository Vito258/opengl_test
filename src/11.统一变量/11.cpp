#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "string"
#include <sstream>
#include <fstream>

//断言,如果函数返回false ,在代码中插入断点并中断调试器
#define ASSERT(expr) do { if(!(expr)) __builtin_trap(); } while(0)
#define GlCall(expr) GlClearError();\
expr;\
ASSERT(GlLogCall(#expr,__FILE__,__LINE__))
//使用glGetError 排除错误
/* 清除Error 的方法 */
static void GlClearError(){
    while(glGetError() != GL_NO_ERROR){
        std::cout<<"there is a gl_error"<<std::endl;
    };
}

/* 打印Error 的方法 */
static bool GlLogCall(const char* function, const char* file, int line){
    while(GLenum error = glGetError())
    {
      std::cout<<"[OPENGL ERROR]:"<<error<<" function:"<<function<< " file:"<<file<<" \n Line: "<< line <<std::endl;
      return false;
    }
    return true;
}

struct ShaderProgramSource{
    std::string vertex_source;
    std::string fragment_source;
};

//读取着色器源码的方法
static ShaderProgramSource ParseShader(const std::string& filepath){
  std::ifstream stream(filepath);
  enum class ShaderType{
      NONE = -1, VERTEX=0,FRAGMENT=1
  };
  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;
  while(getline(stream,line)){
      if(line.find("#shader") != std::string::npos){
          if(line.find("vertex") != std::string::npos){
              type = ShaderType::VERTEX;
          }
          else if(line.find("fragment") != std::string::npos){
              type = ShaderType::FRAGMENT;
          }
      }
      else
      {
          ss[(int)type] << line <<'\n';
      }
  }
  return {ss[0].str(),ss[1].str()};
}

/*
 * source 编译器源码
 * */
static unsigned int CompileShader(unsigned int type,const std::string& source){
    /* 创建一个shader并返回id */
    unsigned int id = glCreateShader(type);
    /* 转换成传统c语言风格的字符串 */
    const char* src = source.c_str();

    glShaderSource(id,1,&src, nullptr);
    glCompileShader(id);

    /* TODO 预期的错误处理 */
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        /* 在堆栈空间临时保存错误信息 */
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout<<"This is "<< (type == GL_VERTEX_SHADER ? "vertex":"fragment")<< " message:" <<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
   unsigned int program = glCreateProgram();
   unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
   unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

   //
   glAttachShader(program,vs);
   glAttachShader(program,fs);

   //链接程序
   glLinkProgram(program);
   //对程序进行验证
   glValidateProgram(program);
   return program;
}

//int main() {
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    //用于得到一个渲染openGL的上下文
//    glfwMakeContextCurrent(window);
//
//    //同步v-sync 或者时主频刷新率
//    glfwSwapInterval(1);
//
//    //改为使用GLEW
//    GLenum err = glewInit();
//    if (GLEW_OK != err)
//    {
//        /* Problem: glewInit failed, something is seriously wrong. */
//        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//    }
//    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//
//    float positions[]={
//            -0.5f,-0.5f,
//            0.5f,-0.5f,
//            0.5f,0.5f,
//            -0.5f,0.5f
//    };
//
//    unsigned int indices[] = {
//            0,1,2,
//            2,3,0
//    };
//    unsigned int buffer;
//    /* 生成一个缓冲区，并定义一个id */
//    glGenBuffers(1,&buffer);
//    /* 绑定这个缓冲区 */
//    glBindBuffer(GL_ARRAY_BUFFER,buffer);
//    /* 定义缓冲区的大小 */
//    glBufferData(GL_ARRAY_BUFFER,4 * 2 * sizeof(float),positions,GL_STATIC_DRAW);
//    /* 开启顶点属性 */
//    glEnableVertexAttribArray(0);
//
//    /* 为 Atrtribute 变量制定VBO中的数据。 */
//    // index: 顶点参数的索引，位置0，纹理坐标1，法线2
//    // size, Attribute 变量数据是由几个元素组成的， x,y,z,w ; 最多四个。
//    // type, Attribute 变量数据 的数据类型
//    // normalized, 是否归一化， 编程1.0以内的数，这样做的目的是减少向gpu传递数据的带宽。
//    // stride,一个顶点的内存大小，等于sizeof(float)*参数的数量，参数的数量即数据的数量
//    // pointer,顶点参数的内存地址，例如一个三维顶点(float) ，位置的pointer就是0，纹理坐标的pointer就是12 = 3*sizeof(float),法线的pointer为 20 = 3*sizeof(float) + 2*sizeof(float)
//    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);
//
//    //索引缓冲区的设置
//    unsigned int ibo;
//    glGenBuffers(1,&ibo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6  * sizeof(unsigned int),indices,GL_STATIC_DRAW);
//
//    //读取着色器源码
//    ShaderProgramSource shaderProgramSource = ParseShader("../res/shaders/Basic.shader");
//    unsigned int shader = CreateShader(shaderProgramSource.vertex_source,shaderProgramSource.fragment_source);
//    //根据一个已经绑定好的着色器id,使用这个shader作为当前的渲染程序
//    glUseProgram(shader);
//
//    //将代码从着色器移到 c++中
//    //1.获取变量的位置
//    int location = glGetUniformLocation(shader,"u_Color");
//    ASSERT( location!= -1);
//
//    float r= 0.5f;
//    float increment = 0.05f;
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //2.根据前面得到的位置整数
//        glUniform4f(location,r, 0.3f, 0.8f, 1.0f);
//        /* 没有索引缓冲区时可以使用这个方法 */
//        //glDrawArrays(GL_TRIANGLES,0,6);
//
//        /* 有索引缓冲区时可以使用这个方法 */
//        GlCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, nullptr));
//
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//        if(r>1.0f){
//            increment = -0.05f;
//        }else if(r < 0.0f){
//            increment = 0.05f;
//        }
//        r+=increment;
//    }
//    glDeleteProgram(shader);
//    glfwTerminate();
//    return 0;
//}

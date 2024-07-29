cmake_minimum_required(VERSION 3.26)
project(openGl_test)

set(CMAKE_CXX_STANDARD 17)

# 添加预处理器定义
add_definitions(-DGLEW_STATIC)
# 设置 GLFW 库和头文件路径
set(GLFW_LIB_DIR "Dependencies/GLFW/lib-mingw-w64")
set(GLFW_INCLUDE_DIR "Dependencies/GLFW/include")

# 设置CMake搜索路径,用于搜索glew
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};Dependencies/GLEW")
set(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH};Dependencies/GLEW/include")

# 添加 GLFW 库路径
link_directories(${GLFW_LIB_DIR})
# 添加 GLEW 库路径
find_package(GLEW REQUIRED)

# 添加 GLFW 和 GLEW 的头文件路径
include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})


add_executable(openGl_test src/main.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/VertexBufferLayout.cpp
        src/VertexBufferLayout.h
        src/Shader.cpp
        src/Shader.h)

# 链接 GLFW库
target_link_libraries(openGl_test
        PRIVATE
        ${GLEW_STATIC_LIBRARIES}
        opengl32
        glu32
        glfw3
        kernel32
        user32
        gdi32
        shell32
        ole32
        uuid
)




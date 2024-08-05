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

# 设置自定义vendor
set(VENDOR_DIR "src/vendor")

# 添加ImGui库的路径
set(IMGUI_DIR "src/vendor/imgui")
# 添加ImGui库的源文件
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
)

# 设置src下 的头文件
set(SOURCE_LIB_DIR "src")

# 添加自定义测试框架源文件
set(TEST_SOURCES
        tests/TestClearColor.cpp
        tests/Test.cpp
        tests/TestTexture2D.cpp
)

# 添加源文件
set(SOURCES
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
        src/Shader.h
        src/vendor/stb_image/stb_image.h
        src/vendor/stb_image/stb_image.cpp
        src/Texture.cpp
        src/Texture.h
)

# 添加头文件路径
include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${VENDOR_DIR} ${SOURCE_LIB_DIR})


add_executable(openGl_test
        src/main.cpp
        ${SOURCES}
        ${IMGUI_SOURCES}
        ${TEST_SOURCES})

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




add_executable(SandboxLayer
        src/SandboxLayer.cpp
        ${SOURCES}
        ${IMGUI_SOURCES}
        ${TEST_SOURCES}
)
# 链接 GLFW库
target_link_libraries(SandboxLayer
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
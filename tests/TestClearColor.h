//
// Created by 111 on 2024/8/1.
//

#ifndef OPENGL_TEST_TESTCLEARCOLOR_H
#define OPENGL_TEST_TESTCLEARCOLOR_H

#include "Test.h"

namespace test{
    class TestClearColor :public Test{
    public:
        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImguiRender() override;

    private:
        float m_ClearColor[4];
    };
}



#endif //OPENGL_TEST_TESTCLEARCOLOR_H

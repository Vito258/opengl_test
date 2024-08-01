//
// Created by 111 on 2024/8/1.
//

#ifndef OPENGL_TEST_TEST_H
#define OPENGL_TEST_TEST_H
namespace test{
    class Test {
    public:
        Test();
        virtual ~Test();

        virtual void OnUpdate(float deltaTime){};
        virtual void OnRender(){};
        virtual void OnImguiRender(){};
    };
}
#endif //OPENGL_TEST_TEST_H

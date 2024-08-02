//
// Created by 111 on 2024/8/1.
//

#ifndef OPENGL_TEST_TEST_H
#define OPENGL_TEST_TEST_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace test{

    class Test {
    public:
        Test(){};
        virtual ~Test(){};

        virtual void OnUpdate(float deltaTime){};
        virtual void OnRender(){};
        virtual void OnImguiRender(){};
    };

    class TestMenu : public Test{
    public:
        TestMenu(Test*& currentPointer);

        void OnImguiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name){
            std::cout<<"Registering Test : "<<name<<std::endl;
            m_Tests.push_back(std::make_pair(name,[](){return new T();}));
        };
    private:
        // 改变当前应用中活动的 current_Test
        Test*& m_CurrentTest;
        // std::function<Test*()>：一个返回Test* 的方法
        std::vector<std::pair<std::string,std::function<Test*()>>> m_Tests;
    };

}
#endif //OPENGL_TEST_TEST_H

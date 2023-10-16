/*
 * 单例模板类，使用时公有继承并将特化模板作为友元
 */
#pragma once
#include <iostream>

template<typename T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;

    Singleton& operator=(const Singleton&) = delete; 

    static T& get_instance() {
        static T t;
        return t;
    }

protected:
    Singleton() {}
    
    virtual ~Singleton() {}
};

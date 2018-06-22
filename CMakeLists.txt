cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CMAKE_CXX_FLAGS "-std=c++14 -lsfml-graphics -lsfml-system -lsfml-window  -lsfml-audio")

add_executable(
        ECS
        test.cpp
        EntityManager.cpp
        EntityManager.h
        EntityComponentSystem.cpp
        EntityComponentSystem.h
        ComponentSystems/System.h
        ComponentSystems/SystemBase.h
        MessageManager.cpp
        MessageManager.h
        SystemManager.cpp
        SystemManager.h
        Entity.h
        Entity.cpp
        example.cpp
        ComponentSystems/SystemBase.cpp)
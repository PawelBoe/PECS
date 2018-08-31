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
        System.h
        SystemBase.h
        SystemManager.cpp
        SystemManager.h
        Entity.h
        Entity.cpp
        example.cpp
        SystemBase.cpp
        ComponentManager.cpp
        ComponentManager.h
        Component.h ComponentBase.cpp ComponentBase.h View.cpp View.h util/sparse_set.cpp util/sparse_set.h util/sparse_map.cpp util/sparse_map.h)
cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        ECS
        main.cpp
        EntityManager.cpp
        EntityManager.h
        EntityComponentSystem.cpp
        EntityComponentSystem.h
        ComponentSystems/ComponentSystem.h
        ComponentSystems/ComponentSystemBase.h
        ComponentSystems/ComponentBase.h
        ComponentSystems/ComponentDummy.h
        ComponentSystems/ComponentBase.cpp
        ComponentSystems/ComponentDummy.cpp
        MessageManager.cpp
        MessageManager.h
        ComponentManager.cpp
        ComponentManager.h
        Entity.h
        Entity.cpp)
cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-system -lsfml-window  -lsfml-audio")  # TODO make platform independent

set(CATCH_DIR "tests/catch")
set(INCLUDE_DIR "src/")
include_directories(${CATCH_DIR} ${INCLUDE_DIR})

set(SOURCE_FILES
        src/core/EntityManager.cpp
        src/core/EntityManager.h
        src/core/EntityComponentSystem.cpp
        src/core/EntityComponentSystem.h
        src/core/System.h
        src/core/SystemBase.h
        src/core/SystemManager.cpp
        src/core/SystemManager.h
        src/core/Entity.h
        src/core/Entity.cpp
        src/core/ComponentManager.cpp
        src/core/ComponentManager.h
        src/core/Component.h
        src/core/ComponentBase.h
        src/util/sparse_set.h
        src/util/sparse_map.h
        src/core/Signature.h
        src/core/SignatureBase.h
        src/util/TypeId.h
        src/core/View.h
        src/core/ViewBase.h
        src/core/ViewManager.cpp
        src/core/ViewManager.h
        src/pecs.h
        )

add_executable(TESTS
        tests/TestMain.cpp
        tests/TestCase_util.cpp
        tests/TestCase_entity.cpp
        tests/TestCase_signature.cpp
        tests/TestCase_view.cpp
        tests/TestCase_ecs.cpp
        ${SOURCE_FILES}
        )


add_executable(EXAMPLE_0
        examples/example_0.cpp
        ${SOURCE_FILES}
        )

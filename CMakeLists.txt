cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-system -lsfml-window  -lsfml-audio")  # TODO make platform independent

set(CATCH_DIR "tests/catch")
set(INCLUDE_DIR "src/")
include_directories(${CATCH_DIR} ${INCLUDE_DIR})

set(SOURCE_FILES
        src/EntityManager.cpp
        src/EntityManager.h
        src/EntityComponentSystem.cpp
        src/EntityComponentSystem.h
        src/System.h
        src/SystemBase.h
        src/SystemManager.cpp
        src/SystemManager.h
        src/Entity.h
        src/Entity.cpp
        src/ComponentManager.cpp
        src/ComponentManager.h
        src/Component.h
        src/ComponentBase.h
        src/View.cpp
        src/View.h
        src/util/sparse_set.h
        src/util/sparse_map.h
        src/Signature.h
        src/SignatureBase.h
        src/util/TypeId.h
        )

add_executable(TESTS
        tests/TestMain.cpp
        tests/TestCase_util.cpp
        tests/TestCase_entity.cpp
        tests/TestCase_signature.cpp
        tests/TestCase_view.cpp
        ${SOURCE_FILES}
        )


add_executable(EXAMPLE_0
        examples/example_0.cpp
        ${SOURCE_FILES}
        )

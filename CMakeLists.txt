cmake_minimum_required(VERSION 3.10)
project(ECS)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5.1
  COMPONENTS 
    system window graphics network audio REQUIRED)


set(CATCH_DIR "tests/catch")
set(INCLUDE_DIR "PECS/")
include_directories(${CATCH_DIR} ${PSSET_DIR} ${INCLUDE_DIR})

set(SOURCE_FILES
        PECS/core/EntityManager.cpp
        PECS/core/EntityManager.h
        PECS/core/EntityComponentSystem.cpp
        PECS/core/EntityComponentSystem.h
        PECS/core/System.h
        PECS/core/SystemBase.h
        PECS/core/SystemManager.cpp
        PECS/core/SystemManager.h
        PECS/core/Entity.h
        PECS/core/Entity.cpp
        PECS/core/ComponentManager.cpp
        PECS/core/ComponentManager.h
        PECS/core/Component.h
        PECS/core/ComponentBase.h
        PECS/core/Signature.h
        PECS/core/SignatureBase.h
        PECS/util/TypeId.h
        PECS/core/View.h
        PECS/core/ViewBase.h
        PECS/core/ViewManager.cpp
        PECS/core/ViewManager.h
        PECS/pecs.h

        PECS/lib/psset.h
        )

add_executable(TESTS
        tests/TestMain.cpp
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

add_executable(EXAMPLE_1
        examples/example_1.cpp
        ${SOURCE_FILES}
        )

target_link_libraries(TESTS sfml-graphics)
target_link_libraries(TESTS sfml-system)
target_link_libraries(TESTS sfml-window)
target_link_libraries(TESTS sfml-audio)

target_link_libraries(EXAMPLE_0 sfml-graphics)
target_link_libraries(EXAMPLE_0 sfml-system)
target_link_libraries(EXAMPLE_0 sfml-window)
target_link_libraries(EXAMPLE_0 sfml-audio)

target_link_libraries(EXAMPLE_1 sfml-graphics)
target_link_libraries(EXAMPLE_1 sfml-system)
target_link_libraries(EXAMPLE_1 sfml-window)
target_link_libraries(EXAMPLE_1 sfml-audio)

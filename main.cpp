#include <iostream>
#include <chrono>
#include "EntityComponentSystem.h"
#include "ComponentSystems/ComponentDummy.h"


void handle_events()
{
}

void update()
{
    std::cout << "update" << std::endl;
}

void render(double dt)
{
}

using namespace std::chrono_literals;
int test_game_loop()
{
    using clock = std::chrono::high_resolution_clock;

    std::chrono::nanoseconds timestep(50ms);
    std::chrono::nanoseconds lag(0ns);

    auto time_start = clock::now();
    bool quit_game = false;

    while(!quit_game) {
        auto delta_time = clock::now() - time_start;
        time_start = clock::now();
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

        if (lag > timestep * 10)
            lag = timestep * 10;

        handle_events();

        while (lag >= timestep) {
            lag -= timestep;
            update();
        }

        auto interpol = (float) lag.count() / timestep.count();
        render(interpol);
    }

    return 0;
}

void test_entity_manager()
{
    pecs::EntityManager em = pecs::EntityManager();

    pecs::Entity e0 = em.create_entity();
    std::cout << "e0 index: " << e0.index() << std::endl;
    std::cout << "e0 version: " << e0.version() << std::endl;
    std::cout << "e0 exists: " << em.exists_entity(e0) << std::endl;

    pecs::Entity e1 = em.create_entity();
    std::cout << "e1 index: " << e1.index() << std::endl;
    std::cout << "e1 version: " << e1.version() << std::endl;
    std::cout << "e1 exists: " << em.exists_entity(e1) << std::endl;

    pecs::Entity e2 = em.create_entity();
    std::cout << "e2 index: " << e2.index() << std::endl;
    std::cout << "e2 version: " << e2.version() << std::endl;
    std::cout << "e2 exists: " << em.exists_entity(e2) << std::endl;

    em.remove_entity(e1);
    std::cout << "e1 index: " << e1.index() << std::endl;
    std::cout << "e1 version: " << e1.version() << std::endl;
    std::cout << "e1 exists: " << em.exists_entity(e1) << std::endl;

    pecs::Entity e3 = em.create_entity();
    std::cout << "e3 index: " << e3.index() << std::endl;
    std::cout << "e3 version: " << e3.version() << std::endl;
    std::cout << "e3 exists: " << em.exists_entity(e3) << std::endl;

    pecs::Entity e4 = em.create_entity();
    std::cout << "e4 index: " << e4.index() << std::endl;
    std::cout << "e4 version: " << e4.version() << std::endl;
    std::cout << "e4 exists: " << em.exists_entity(e4) << std::endl;

    em.remove_entity(e0);
    std::cout << "e0 index: " << e0.index() << std::endl;
    std::cout << "e0 version: " << e0.version() << std::endl;
    std::cout << "e0 exists: " << em.exists_entity(e0) << std::endl;

    pecs::Entity e5 = em.create_entity();
    std::cout << "e5 index: " << e5.index() << std::endl;
    std::cout << "e5 version: " << e5.version() << std::endl;
    std::cout << "e5 exists: " << em.exists_entity(e5) << std::endl;
}

void test_entity_component_system()
{
    auto ecs = pecs::EntityComponentSystem();
    auto entity = ecs.create_entity();
    auto entity_exists = ecs.exists_entity(entity);

    ecs.create_component<pecs::ComponentDummy>(entity);
    auto component = ecs.get_component<pecs::ComponentDummy>(entity);
    ecs.delete_component<pecs::ComponentDummy>(entity);

    std::cout << "Entity index: " << entity.index() << std::__1::endl;
    std::cout << "Entity version: " << entity.version() << std::__1::endl;
    std::cout << "Entity exists: " << entity_exists << std::endl;
    std::cout << "Component Address: " << component << std::endl;
    std::cout << "Component->x: " << component->x << std::endl;
    std::cout << "Component->y: " << component->y << std::endl;

    ecs.delete_entity(entity);
}


int main()
{
    test_entity_manager();
    test_entity_component_system();
}
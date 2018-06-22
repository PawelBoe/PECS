#include <iostream>
#include <chrono>
#include "EntityComponentSystem.h"


void test_entity_manager()
{
    pecs::EntityManager em = pecs::EntityManager();

    pecs::Entity e0 = em.create();
    std::cout << "e0 index: " << e0.index() << std::endl;
    std::cout << "e0 version: " << e0.version() << std::endl;
    std::cout << "e0 exists: " << em.exists(e0) << std::endl;

    pecs::Entity e1 = em.create();
    std::cout << "e1 index: " << e1.index() << std::endl;
    std::cout << "e1 version: " << e1.version() << std::endl;
    std::cout << "e1 exists: " << em.exists(e1) << std::endl;

    pecs::Entity e2 = em.create();
    std::cout << "e2 index: " << e2.index() << std::endl;
    std::cout << "e2 version: " << e2.version() << std::endl;
    std::cout << "e2 exists: " << em.exists(e2) << std::endl;

    em.remove(e1);
    std::cout << "e1 index: " << e1.index() << std::endl;
    std::cout << "e1 version: " << e1.version() << std::endl;
    std::cout << "e1 exists: " << em.exists(e1) << std::endl;

    pecs::Entity e3 = em.create();
    std::cout << "e3 index: " << e3.index() << std::endl;
    std::cout << "e3 version: " << e3.version() << std::endl;
    std::cout << "e3 exists: " << em.exists(e3) << std::endl;

    pecs::Entity e4 = em.create();
    std::cout << "e4 index: " << e4.index() << std::endl;
    std::cout << "e4 version: " << e4.version() << std::endl;
    std::cout << "e4 exists: " << em.exists(e4) << std::endl;

    em.remove(e0);
    std::cout << "e0 index: " << e0.index() << std::endl;
    std::cout << "e0 version: " << e0.version() << std::endl;
    std::cout << "e0 exists: " << em.exists(e0) << std::endl;

    pecs::Entity e5 = em.create();
    std::cout << "e5 index: " << e5.index() << std::endl;
    std::cout << "e5 version: " << e5.version() << std::endl;
    std::cout << "e5 exists: " << em.exists(e5) << std::endl;
}

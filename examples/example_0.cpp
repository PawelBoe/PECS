//
// Created by Pawel Boening on 22/06/18.
//

#include <iostream>
#include "pecs.h"
#include "SFML/Graphics.hpp"


struct ParticleComponent
{
    int particles;
};

struct PositionComponent
{
    int x;
    int y;
};

struct XComponent
{

};

class RenderSystem : public pecs::System<RenderSystem, PositionComponent>
{
public:
    RenderSystem(sf::RenderTarget &target)
    {
    }

    void _update(pecs::View<PositionComponent> &view, float dt)
    {
        // TODO render something
    }
};

class ParticleSystem : public pecs::System<ParticleSystem, PositionComponent, ParticleComponent>
{
public:
    ParticleSystem()
    {
    }

    void _update(pecs::View<PositionComponent, ParticleComponent> &view, float dt)
    {
        std::cout << "ParticleSystem: ";
        for (auto entity : view)
        {
            std::cout << entity.index() << " ";
        }
        std::cout << std::endl;
    }
};

class XSystem : public pecs::System<XSystem, XComponent>
{
public:
    XSystem()
    {
    }

    void _update(pecs::View<XComponent> &view, float dt)
    {
        std::cout << "XSystem: ";
        for (auto entity : view)
        {
            std::cout << entity.index() << " ";
        }
        std::cout << std::endl;
    }
};

class AllSystem : public pecs::System<AllSystem>
{
public:
    AllSystem()
    {
    }

    void _update(pecs::View<> &view, float dt)
    {
        std::cout << "AllSystem: ";
        for (auto entity : view)
        {
            std::cout << entity.index() << " ";
        }
        std::cout << std::endl;
    }
};


class Application : public pecs::EntityComponentSystem
{
public:
    explicit  Application(sf::RenderTarget &target)
    {
        assign_system<ParticleSystem>();
        assign_system<RenderSystem>(target);
        assign_system<XSystem>();
        assign_system<AllSystem>();

        assign_component<PositionComponent>();
        assign_component<ParticleComponent>();
        assign_component<XComponent>();

        pecs::Entity e0 = _data.create();
        _data.add<PositionComponent>(e0);
        _data.get<PositionComponent>(e0).x = 100;
        _data.get<PositionComponent>(e0).y = 100;
        _data.add<ParticleComponent>(e0);
        _data.get<ParticleComponent>(e0).particles = 100;

        pecs::Entity e1 = _data.create();
        _data.add<PositionComponent>(e1);
        _data.get<PositionComponent>(e1).x = 300;
        _data.get<PositionComponent>(e1).y = 300;
        _data.add<ParticleComponent>(e1);
        _data.get<ParticleComponent>(e1).particles = 300;

        pecs::Entity e2 = _data.create();
        _data.add<PositionComponent>(e2);
        _data.get<PositionComponent>(e2).x = 500;
        _data.get<PositionComponent>(e2).y = 500;
        _data.add<ParticleComponent>(e2);
        _data.get<ParticleComponent>(e2).particles = 500;

        pecs::Entity e3 = _data.create();
        _data.add<XComponent>(e3);
    }

    void simulate(float dt)
    {
        update<ParticleSystem>(dt);
        update<XSystem>(dt);
        update<AllSystem>(dt);
    }

    void render(float dt)
    {
        update<RenderSystem>(dt);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "PECS Particle Example");

    Application app(window);

    sf::Clock clock;
    float elapsed = 0;
    float STEPTIME = 50;

    while (window.isOpen()) {
        elapsed += clock.restart().asMilliseconds();

        if (elapsed > STEPTIME * 10)
            elapsed = STEPTIME * 10;

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                case sf::Event::KeyPressed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        while (elapsed >= STEPTIME) {
            app.simulate(STEPTIME);
            elapsed -= STEPTIME;
        }

       window.clear();
       app.render(elapsed / STEPTIME);
       window.display();
    }

    return 0;
}
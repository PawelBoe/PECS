//
// Created by Pawel Boening on 22/06/18.
//

#include "EntityComponentSystem.h"
#include "SFML/Graphics.hpp"


class RenderSystem : public pecs::System<RenderSystem>
{
public:
    RenderSystem(sf::RenderTarget &target)
    {
    }

    void _assign(pecs::Entity entity)
    {
    }

    void _remove(pecs::Entity entity)
    {
    }

    void _update(float dt)
    {
    }
};

class PositionSystem : public pecs::System<PositionSystem>
{
public:
    PositionSystem()
    {
    }

    void _assign(pecs::Entity entity, int x, int y)
    {

    }

    void _remove(pecs::Entity entity)
    {
    }

    void _update(float dt)
    {
    }

};

class ParticleSystem : public pecs::System<ParticleSystem>
{
public:
    ParticleSystem(int particle_count)
    {
    }

    void _assign(pecs::Entity entity)
    {
    }

    void _remove(pecs::Entity entity)
    {
    }

    void _update(float dt)
    {
    }
};


class Application : public pecs::EntityComponentSystem
{
public:
    explicit Application(sf::RenderTarget &target)
    {
        _systems.add<RenderSystem>(target);
        _systems.add<ParticleSystem>(500);
        _systems.add<PositionSystem>();

        auto e0 = _entities.create();
        _systems.assign<RenderSystem>(e0);
        _systems.assign<ParticleSystem>(e0);
        _systems.assign<PositionSystem>(e0, 100, 100);

        auto e1 = _entities.create();
        _systems.assign<RenderSystem>(e1);
        _systems.assign<ParticleSystem>(e1);
        _systems.assign<PositionSystem>(e1, 300, 300);

        auto e2 = _entities.create();
        _systems.assign<RenderSystem>(e2);
        _systems.assign<ParticleSystem>(e2);
        _systems.assign<PositionSystem>(e2, 500, 500);
    }

    void update(float dt)
    {
        _systems.update<PositionSystem>(dt);
        _systems.update<ParticleSystem>(dt);
    }

    void render(float dt)
    {
        _systems.update<RenderSystem>(dt);
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
        elapsed += clock.restart().asMicroseconds();

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
            app.update(STEPTIME);
            elapsed -= STEPTIME;
        }

       window.clear();
       app.render(elapsed / STEPTIME);
       window.display();
    }

    return 0;
}
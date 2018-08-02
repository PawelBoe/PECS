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

    void _update(pecs::EntityManager &entities, pecs::ComponentManager &components, float dt)
    {
    }
};

class ParticleSystem : public pecs::System<ParticleSystem>
{
public:
    ParticleSystem()
    {
    }

    void _update(pecs::EntityManager &entities, pecs::ComponentManager &components, float dt)
    {
    }
};

struct ParticleComponent
{
    int particles;
};

struct PositionComponent
{
    int x;
    int y;
};


class Application : public pecs::EntityComponentSystem
{
public:
    Application(sf::RenderTarget &target)
    {
        _systems.add<ParticleSystem>();
        _systems.add<RenderSystem>(target);

        _components.add<PositionComponent>();
        _components.add<ParticleComponent>();

        pecs::Entity e0 = _entities.create();
        _components.create<PositionComponent>(e0);
        _components.get<PositionComponent>(e0).x = 100;
        _components.get<PositionComponent>(e0).x = 100;
        _components.create<ParticleComponent>(e0);
        _components.get<ParticleComponent>(e0).particles = 100;

        pecs::Entity e1 = _entities.create();
        _components.create<PositionComponent>(e1);
        _components.get<PositionComponent>(e1).x = 300;
        _components.get<PositionComponent>(e1).y = 300;
        _components.create<ParticleComponent>(e1);
        _components.get<ParticleComponent>(e1).particles = 300;

        pecs::Entity e2 = _entities.create();
        _components.create<PositionComponent>(e2);
        _components.get<PositionComponent>(e2).x = 500;
        _components.get<PositionComponent>(e2).y = 500;
        _components.create<ParticleComponent>(e2);
        _components.get<ParticleComponent>(e2).particles = 500;
    }

    void simulate(float dt)
    {
        update<ParticleSystem>(dt);
        update<ParticleSystem>(dt);
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
            app.simulate(STEPTIME);
            elapsed -= STEPTIME;
        }

       window.clear();
       app.render(elapsed / STEPTIME);
       window.display();
    }

    return 0;
}
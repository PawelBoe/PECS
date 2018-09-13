//
// Created by Pawel Boening on 13.09.18.
//


#include <SFML/Graphics.hpp>
#include "pecs.h"


struct Position
{
    float x;
    float y;
};

struct Velocity
{
    float dx;
    float dy;
};

struct CircleCollisionBody
{
    float r;
};

struct CircleAppearance
{
    float size;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};


class CircleRenderer : public pecs::System<CircleRenderer, Position, CircleAppearance>
{
public:
    CircleRenderer(sf::RenderTarget &target) : _target(target)
    {
    }

    void _update(pecs::View<Position, CircleAppearance> &view, float dt)
    {
        for (pecs::Entity e : view) {
            auto x = view.get<Position>(e).x;
            auto y = view.get<Position>(e).y;
            auto size = view.get<CircleAppearance>(e).size;
            auto red = view.get<CircleAppearance>(e).red;
            auto green = view.get<CircleAppearance>(e).green;
            auto blue = view.get<CircleAppearance>(e).blue;

            sf::CircleShape shape;
            shape.setOrigin(size, size);
            shape.setRadius(size);
            shape.setFillColor(sf::Color(red, green, blue));
            shape.setPosition(x, y);

            _target.draw(shape);
        }
    }
private:
    sf::RenderTarget &_target;
};

class Movement : public pecs::System<Movement, Position, Velocity>
{
public:
    Movement() = default;

    void _update(pecs::View<Position, Velocity> &view, float dt)
    {
        for (pecs::Entity e : view) {
            view.get<Position>(e).x += view.get<Velocity>(e).dx * dt;
            view.get<Position>(e).y += view.get<Velocity>(e).dy * dt;
        }
    }
};


class Application : public pecs::EntityComponentSystem
{
public:
    Application()
            : _window(sf::VideoMode(1500, 1000), "PECS Circle Physics Example")
    {
        assign_system<CircleRenderer>(_window);
        assign_system<Movement>();
        assign_component<Position>();
        assign_component<Velocity>();
        assign_component<CircleCollisionBody>();
        assign_component<CircleAppearance>();

        pecs::Entity e0 = _data.create();
        _data.add<Position>(e0);
        _data.add<Velocity>(e0);
        _data.add<CircleCollisionBody>(e0);
        _data.add<CircleAppearance>(e0);

        _data.get<Position>(e0).x = 100;
        _data.get<Position>(e0).y = 100;
        _data.get<Velocity>(e0).dx = 200;
        _data.get<Velocity>(e0).dy = 200;
        _data.get<CircleCollisionBody>(e0).r = 42;
        _data.get<CircleAppearance>(e0).size = 13;
        _data.get<CircleAppearance>(e0).red = 100;
        _data.get<CircleAppearance>(e0).green = 0;
        _data.get<CircleAppearance>(e0).blue = 0;
    }

    void run()
    {
        sf::Clock clock;
        float elapsed = 0;
        float STEPTIME = 1.0f / 10.0f;

        simulate(STEPTIME);
        while (_window.isOpen()) {
            elapsed += clock.restart().asSeconds();

            if (elapsed > STEPTIME * 10)
                elapsed = STEPTIME * 10;

            sf::Event event;
            while (_window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                    case sf::Event::KeyPressed:
                        _window.close();
                        break;
                    default:
                        break;
                }
            }

            while (elapsed >= STEPTIME) {
                simulate(STEPTIME);
                elapsed -= STEPTIME;
            }

            _window.clear();
            render(elapsed / STEPTIME);
            _window.display();
        }
    }

private:
    void simulate(float dt)
    {
        update<Movement>(dt);
    }

    void render(float dt)
    {
        update<CircleRenderer>(dt);
    }

    sf::RenderWindow _window;
};

int main()
{
    Application app;
    app.run();
}

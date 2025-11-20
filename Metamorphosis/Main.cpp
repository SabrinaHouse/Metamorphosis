#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Camera.h"
#include "Game.h"
#include "Renderer.h"

Camera camera(200.0f);

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "METAMORPHOSIS");
    sf::Clock deltaClock;
    Renderer renderer(window);

    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(camera.position);

    Begin(window);
    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

       window.setView(camera.getView(window.getSize()));

       Update(deltaTime);

       window.clear();

       Render(renderer);

       window.display();
    }
}
#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Camera.h"
#include "Game.h"
#include "Renderer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "METAMORPHOSIS");
    sf::Clock deltaClock;
    Renderer renderer(window);

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

       window.clear(sf::Color::White);

       Render(renderer, window);

       window.display();
    }
}
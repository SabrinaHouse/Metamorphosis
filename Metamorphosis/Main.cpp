#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Camera.h"
#include "Renderer.h"
#include "Game.h"

Game game;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1600, 900 }), "METAMORPHOSIS");
    sf::Clock deltaClock;
    Renderer renderer(window);

    game.Begin(window);

    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyReleased>())
            {
                auto keyEvent = event->getIf<sf::Event::KeyReleased>();
                if (keyEvent->code == sf::Keyboard::Key::Backspace)
                {
                    ChangeLevels();
                    game.Begin(window);
                }
            }
        }

        if (game.LevelComplete) {
            ChangeLevels();
            game.Begin(window);
        }

       window.setView(camera.getView(window.getSize()));

       game.Update(deltaTime);

       window.clear();

       game.Render(renderer);

       window.display();
    }
}
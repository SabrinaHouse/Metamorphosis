#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Camera.h"
#include "Renderer.h"
#include "Game.h"
#include "Menu.h"

Game game;
Menu menu;

int main()
{
    //load files
    for (auto& file : std::filesystem::directory_iterator("./Resources/"))
    {
        if (file.is_regular_file() && file.path().extension() == ".png") {
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }

        else if (file.is_regular_file() && (file.path().extension() == ".ttf")) {
            if (!Resources::fonts[file.path().filename().string()].openFromFile(file.path().string())) {
                std::abort();
            }
        }
    }

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ 1600, 900 }), "METAMORPHOSIS");
    sf::Clock deltaClock;
    Renderer renderer(*window);


    game.Begin(*window);
    menu.MainMenu(camera, window);


    while (window->isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();

        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }

            if (event->is<sf::Event::KeyReleased>())
            {
                auto keyEvent = event->getIf<sf::Event::KeyReleased>();
                if (keyEvent->code == sf::Keyboard::Key::Backspace)
                {
                    ChangeLevels();
                    game.Begin(*window);
                    if (CurrentLevel() == 0) {
                        game.inMenu = true;
                    }
                    else {
                        game.inMenu = false;
                    }

                    
                }
            }

            if (game.inMenu) {
                auto keyEvent = event->getIf<sf::Event::KeyReleased>();

                //selction moved up
                if ((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::W) ||
                    (event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Up)) {
                    menu.moveUp();
                }

                //selection moved down
                if ((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::S) ||
                    (event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Down)) {
                    menu.moveDown();
                }

                if (((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Enter) ||
                    (event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Space))) {
                    switch (menu.getPressedItem()) {
                    case 0:
                        //title
                        break;
                    case 1:
                        
                        //unpause
                        game.LevelComplete = true;
                        game.inMenu = false;

                        break;
                    case 2:
                        //quit
                        window->close();
                        break;
                    case 3:
                        //level select
                        
                        break;
                    }
                }
            }
        }

        if (game.LevelComplete) {
            ChangeLevels();
            game.Begin(*window);
        }

       window->setView(camera.getView(window->getSize()));

       if (!game.inMenu) {
           game.Update(deltaTime);

           window->clear();

           game.Render(renderer);
       }
       else {
           window->clear();
           menu.updatePosition(camera, window);
           menu.draw(window, renderer);
       }
       

       window->display();
    }
}
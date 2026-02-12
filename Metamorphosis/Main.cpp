#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Camera.h"
#include "Renderer.h"
#include "Game.h"
#include "Menu.h"

Game game;
Menu menu;

bool isPaused;

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
        sf::View cameraView = camera.getView(window->getSize());

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

                //return to previous screen if you are in level select
                if ((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Escape) && (CurrentLevel() != 0 && game.playerDead && menu.inLevelSelect)) {
                    menu.DeathScreen(camera, window);
                }else  if ((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Escape) && (CurrentLevel() != 0 && menu.inLevelSelect)) {
                    menu.PauseScreen(camera, window);
                }
                else if ((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Escape) && CurrentLevel() ){
                    //pause or unpause the game
                    game.inMenu = !game.inMenu;
                    isPaused = !isPaused;
                    menu.PauseScreen(camera, window);
                }

                //return to main menu
                if ((event->is<sf::Event::KeyReleased>() && keyEvent->code == sf::Keyboard::Key::Escape) && CurrentLevel() == 0 && menu.inLevelSelect) {
                    menu.MainMenu(camera, window);
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
                    //select any level from any point
                    if (menu.inLevelSelect) {
                        switch (menu.getPressedItem()) {
                        case 0:
                            // lvl 1
                            SelectLevel(1);
                            break;
                        case 1:
                            //lvl 2
                            SelectLevel(2);
                            break;
                        case 2:
                            //lvl 3
                            SelectLevel(3);
                            break;
                        case 3:
                            //Lvl 4
                            SelectLevel(4);
                            break;
                        }
                        game.Begin(*window);
                        game.inMenu = false;
                    }
                    else {
                        switch (menu.getPressedItem()) {
                        case 0:
                            //title
                            break;
                        case 1:
                            //unpause
                            if (isPaused) {
                                isPaused = false;
                            }
                            else if (game.inDeathScreen) {
                                SelectLevel(CurrentLevel());
                                game.playerDead = false;
                                game.inDeathScreen = false;
                                game.Begin(*window);
                            }
                            //start the game
                            else {
                                game.LevelComplete = true;
                            }
                            game.inMenu = false;
                            break;
                        case 2:
                            //quit
                            window->close();
                            break;
                        case 3:
                            //level select
                            menu.LevelSelectScreen(camera, window);
                            game.inDeathScreen = false;
                            break;
                        }
                    }
                }
            }
        }

        if (game.LevelComplete) {
            ChangeLevels();
            game.Begin(*window);
        }

        if (game.inDeathScreen) {
            menu.DeathScreen(camera, window);
            game.inMenu = true;
        }

       window->setView(camera.getView(window->getSize()));

       if (!game.inMenu) {
           game.Update(deltaTime);

           window->clear();

           game.Render(renderer);
       }
       else {
           window->clear();
           renderer.Draw(Resources::textures["Sky.png"],(cameraView.getCenter()), sf::Vector2f(camera.getViewSize().x * 1.5, camera.getViewSize().y * 1.5));
           menu.updatePosition(camera, window);
           menu.draw(window, renderer);
       }
       

       window->display();
    }
}
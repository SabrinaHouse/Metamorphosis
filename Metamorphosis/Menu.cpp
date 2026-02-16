#include "Menu.h"

void Menu::MainMenu(Camera camera, sf::RenderWindow* window) {
	
	selectedItemIndex = 1;
	sf::View cameraView = camera.getView(window->getSize());
	font = Resources::fonts["smallburg.ttf"];
	sf::FloatRect bounds;

	inLevelSelect = false;

	//set style
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i] = new sf::Text(font);
		menu[i]->setFillColor(sf::Color::White);
		menu[i]->setScale({ .75f, .75f });
		menu[i]->setCharacterSize(36);
	}

	//title
	menu[0]->setString("Metamorphosis");
	//make title bigger
	menu[0]->setCharacterSize(60);

	//play button
	menu[1]->setString("Play");
	//starting selection
	menu[1]->setFillColor(sf::Color::Blue);

	//quit button
	menu[2]->setString("Quit");

	//highscore display
	menu[3]->setString("Level Select");

	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS * 8) * (-1 + i)) - 20 });
	}

	if (!inLevelSelect) {
		menu[0]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS * 8) * (-1)) - 30 });
	}

}

Menu::~Menu() {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		delete menu[i];
	}
}

void Menu::PauseScreen(Camera camera, sf::RenderWindow* window) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());

	inLevelSelect = false;

	//reset what is selected when you enter the screen
	menu[0]->setFillColor(sf::Color::White);
	menu[2]->setFillColor(sf::Color::White);
	menu[3]->setFillColor(sf::Color::White);

	selectedItemIndex = 1;
	menu[1]->setFillColor(sf::Color::Blue);

	//reset strings to proper text and size
	menu[0]->setString("Paused");
	menu[0]->setCharacterSize(60);

	menu[1]->setString("Resume");
	menu[2]->setString("Quit");
	menu[3]->setString("Level Select");


	//set positions
	
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}
	
}

void Menu::DeathScreen(Camera camera, sf::RenderWindow* window) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());

	inLevelSelect = false;

	//reset what is selected when you enter the screen
	menu[0]->setFillColor(sf::Color::White);
	menu[2]->setFillColor(sf::Color::White);
	menu[3]->setFillColor(sf::Color::White);

	selectedItemIndex = 1;
	menu[1]->setFillColor(sf::Color::Blue);

	//reset strings to proper text and size
	menu[0]->setString("You Died!");
	menu[0]->setCharacterSize(60);

	menu[1]->setString("Try Again");
	menu[2]->setString("Quit");
	menu[3]->setString("Level Select");


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS * 8) * (-1 + i)) - 20 });
	}

}

void Menu::LevelSelectScreen(Camera camera, sf::RenderWindow* window) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());

	inLevelSelect = true;

	//reset what is selected when you enter the screen
	menu[0]->setFillColor(sf::Color::White);
	menu[2]->setFillColor(sf::Color::White);
	menu[3]->setFillColor(sf::Color::White);

	selectedItemIndex = 1;
	menu[1]->setFillColor(sf::Color::Blue);

	//reset strings to proper text and size
	menu[0]->setString("Caterpillar");
	menu[0]->setCharacterSize(36);

	menu[1]->setString("Chrysalis");
	menu[2]->setString("Hatchling");
	menu[3]->setString("Butterfly");


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS * 8) * (-1 + i)) - 20 });
	}
}

void Menu::FinalScreen(Camera camera, sf::RenderWindow* window) {
	sf::FloatRect bounds;
	sf::View cameraView = camera.getView(window->getSize());

	inLevelSelect = false;

	//reset what is selected when you enter the screen
	menu[selectedItemIndex]->setFillColor(sf::Color::White);
	selectedItemIndex = 1;
	menu[selectedItemIndex]->setFillColor(sf::Color::Blue);

	//reset strings to proper text and size
	menu[0]->setString("Metamorphosis");
	menu[0]->setCharacterSize(60);

	menu[1]->setString("Play Again");
	menu[2]->setString("Quit");
	menu[3]->setString("Level Select");


	//set positions
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		bounds = menu[i]->getLocalBounds();
		menu[i]->setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS + 1) * (-1 + i)) - 4 });
	}
}


void Menu::updatePosition(Camera camera, sf::RenderWindow* window) {
	sf::View cameraView = camera.getView(window->getSize());
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS * 10) * (-1 + i)) - 20 });
	}

	if (!inLevelSelect) {
		menu[0]->setPosition({ cameraView.getCenter().x, cameraView.getCenter().y + ((MAX_NUMBER_OF_ITEMS * 9) * (-1)) - 30 });
	}
}

void Menu::draw(sf::RenderWindow* window, Renderer& renderer) {

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window->draw(*menu[i]);
	}
}

void Menu::moveUp() {
	if ((selectedItemIndex - 1 > 0 && !inLevelSelect) || (selectedItemIndex - 1 >= 0 && inLevelSelect)) {
		menu[selectedItemIndex]->setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex]->setFillColor(sf::Color::Blue);
	}
}
void Menu::moveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex]->setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex]->setFillColor(sf::Color::Blue);
	}
}
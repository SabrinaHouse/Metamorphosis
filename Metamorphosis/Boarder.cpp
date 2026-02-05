#include "Boarder.h"
#include "Resources.h"
#include "Levels.h"

void Boarder::Begin() {
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	if (CurrentLevel() == 0) {
		polygonShape.SetAsBox(24, 24);
	}
	else {
		polygonShape.SetAsBox(20, 75);
	}

	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void Boarder::Draw(Renderer& renderer) {
	//check which kind of boarder should be drawn based on the level
	if (CurrentLevel() == 0) {
		switch (typeOfBoarder) {
		case 0:
			renderer.Draw(Resources::textures["TopBoarder.png"], position, sf::Vector2f(50, 50));
			break;
		case 1:
			renderer.Draw(Resources::textures["Boarder.png"], position, sf::Vector2f(50, 50));
			break;
		case 2:
			renderer.Draw(Resources::textures["Boarder.png"], position, sf::Vector2f(50, 50), 45.0f);
			break;
		}
	}
	else if (CurrentLevel() == 1) {
		//draw the boarder on both sides at the same time
		renderer.Draw(Resources::textures["Boarder.png"], position, sf::Vector2f(-75, 150));

		renderer.Draw(Resources::textures["Boarder.png"], sf::Vector2f(-position.x, position.y), sf::Vector2f(75, 150));
	}
	

}
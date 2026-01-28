#include "Mantis.h"
#include <iostream>
sf::Clock mantisClock;

void Mantis::Begin() {
	mantisClock.start();

	//tagging with the correct listener
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Mantis;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	//bodyDef.gravityScale = 0;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(20, 15);
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.friction = 0;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Mantis::Update(float deltaTime) {

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;

	//change only x velocity if left/right mantis
	if (LeftToRight) {
		//change the direction the mantis is moving
		if (flipped) {
			velocity.x -= movementSpeed;

		}
		else {
			velocity.x += movementSpeed;
		}
	}
	//change only y velocity if up/down mantis
	else {
		//change the direction the mantis is moving
		if (flipped) {
			velocity.y -= movementSpeed;

		}
		else {
			velocity.y += movementSpeed;
		}
	}
	
	if (mantisClock.getElapsedTime().asSeconds() > 5) {
		//change direction after 5 seconds
		flipped = !flipped;
		mantisClock.restart();
	}

	std::cout << mantisClock.getElapsedTime().asSeconds() << std::endl;

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);

}


void Mantis::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Mantis.png"], position, sf::Vector2f(50, 40));
}
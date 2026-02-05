#include "Wasp.h"
#include <iostream>


void Wasp::Begin() {
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Wasp;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x - 50, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(15, 15);
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.friction = 0;
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);

}

void Wasp::Update(float deltaTime) {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;

	if (horizontal) {
		if (TopOrLeft) {
			std::cout << "West" << std::endl;
			velocity.x += movementSpeed;
		}
		else {
			std::cout << "East" << std::endl;
			velocity.x -= movementSpeed;
		}
	}
	else {
		if (TopOrLeft) {
			std::cout << "North" << std::endl;
			velocity.y += movementSpeed;
		}
		else {
			std::cout << "South" << std::endl;
			velocity.y -= movementSpeed;
		}
	}

	body->SetLinearVelocity(velocity);

	std::cout << velocity.y << std::endl;

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

void Wasp::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Wasp.png"], position, sf::Vector2f(30.0, 25.0f));
}
#include "JuvenileButterfly.h"
#include "Resources.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>

void JuvenileButterfly::Begin() {
	//tagging with the correct listeners
	FixtureData* fixtureData = new FixtureData();
	//fixtureData->listener = this;
	fixtureData->juvenileButterfly = this;
	fixtureData->type = FixtureDataType::JuvenileButterfly;

	//drawing a body for the player to apply physics and collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.density = 10000;
	fixtureDef.friction = 5;
	fixtureDef.userData = fixtureData;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(4, 4);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	//making the box that detects if the player has hit something
	/*
	polygonShape.SetAsBox(4, 4);
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef); */
}

void JuvenileButterfly::Update(float deltaTime) {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 20;

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
	{
		velocity.y -= jumpPower;
		std::cout << std::to_string(position.x) << ", " << std::to_string(position.y) << std::endl;
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

void JuvenileButterfly::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Butterfly.png"], position, sf::Vector2f(15.0, 15.0f));
}
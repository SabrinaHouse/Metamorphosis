#include "JuvenileButterfly.h"
#include "Resources.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>

sf::Event* event;

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
	fixtureDef.density = 2;
	fixtureDef.friction = 5;
	fixtureDef.userData = fixtureData;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(8, 6);
	fixtureDef.shape = &polygonShape;
	body->SetGravityScale(5.0f);
	body->CreateFixture(&fixtureDef);

	//making the box that detects if the player has hit something
	polygonShape.SetAsBox(8, 6);
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef); 
}

sf::Clock jumpClock;

void JuvenileButterfly::Update(float deltaTime) {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 30;

	//jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) && jumpClock.getElapsedTime().asSeconds() >= 0.5f 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) && jumpClock.getElapsedTime().asSeconds() >= 0.5f 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && jumpClock.getElapsedTime().asSeconds() >= 0.5f)
	{
		velocity.y -= jumpPower;
		jumpClock.restart();
		//std::cout << std::to_string(position.x) << ", " << std::to_string(position.y) << std::endl;
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

void JuvenileButterfly::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Butterfly.png"], position, sf::Vector2f(20.0, 15.0f));
}
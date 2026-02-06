#include "Butterfly.h"
#include "Resources.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>

void Butterfly::Begin() {
	//tagging with the correct listeners
	FixtureData* fixtureData = new FixtureData();
	fixtureData->listener = this;
	fixtureData->butterfly = this;
	fixtureData->type = FixtureDataType::Butterfly;

	//drawing a body for the player to apply physics and collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = false;
	body = Physics::world->CreateBody(&bodyDef);


	b2FixtureDef fixtureDef{};
	fixtureDef.density = 0;
	fixtureDef.friction = 0;
	fixtureDef.userData = fixtureData;

	//only needs a sensor hit box
	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(10, 6);
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void Butterfly::Update(float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) //EAST
	{
		location = 1;
		angle = 0.5f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) //WEST
	{
		location = 2;
		angle = 0.5f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) //NORTH
	{
		location = 3;
		angle = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) //SOUTH
	{
		location = 4;
		angle = 0;
	}

	bodyPosition = { position.x, position.y };

	body->SetTransform(bodyPosition, angle * b2_pi);
}

void Butterfly::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Butterfly.png"], position, sf::Vector2f(20.0, 15.0f));

}

void Butterfly::OnBeginContact(b2Fixture* other) {

}

void Butterfly::OnEndContact(b2Fixture* other) {

}
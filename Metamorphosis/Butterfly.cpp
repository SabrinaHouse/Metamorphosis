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

void Butterfly::Update(float deltaTime) {

}

void Butterfly::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Butterfly.png"], position, sf::Vector2f(20.0, 15.0f));

}

void Butterfly::OnBeginContact(b2Fixture* other) {

}

void Butterfly::OnEndContact(b2Fixture* other) {

}
#include "Chrysalis.h"
#include "Resources.h"
#include "Physics.h"
#include "Levels.h"
#include "Ground.h"
#include <iostream>

constexpr float M_PI = 22.0 / 7.0;

bool facingLeft = false;

void Chrysalis::Begin() {
	//tagging with the correct listeners
	FixtureData* fixtureData = new FixtureData();
	fixtureData->listener = this;
	fixtureData->chrysalis = this;
	fixtureData->type = FixtureDataType::Chrysalis;

	//drawing a body for the player to apply physics and collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.density = 4;
	fixtureDef.friction = 0;
	fixtureDef.userData = fixtureData;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(2, 4);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	//making the box that detects if the player has hit something
	polygonShape.SetAsBox(2, 4);
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void Chrysalis::Update(float deltaTime) {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;

	//left and right movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) //right
	{
		velocity.x += movementSpeed;
		facingLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) //left
	{
		velocity.x -= movementSpeed;
		facingLeft = true;
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);

}
void Chrysalis::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Chrysalis.png"], position, sf::Vector2f(facingLeft ? -15.0f : 15.0, 15.0f));
}

void Chrysalis::OnBeginContact(b2Fixture* other) {
	FixtureData* data = (FixtureData*)other->GetUserData();
	if (data && data->type == FixtureDataType::Ground && data->ground->tag == "ground") {
		hitGround = true;
	} else if (data && data->type == FixtureDataType::Branch) {
		hitBranch = true;
	}
}

void Chrysalis::OnEndContact(b2Fixture* other) {

}

void Chrysalis::Reset() {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;

	position = sf::Vector2f(0, 0);


	

}
#include "Caterpillar.h"
#include "Resources.h"
#include "Physics.h"
#include "Levels.h"
#include <iostream>

constexpr float M_PI = 22.0 / 7.0;

void Caterpillar::Begin() {
	//tagging with the correct listeners
	FixtureData* fixtureData = new FixtureData();
	fixtureData->listener = this;
	fixtureData->caterpillar = this;
	fixtureData->type = FixtureDataType::Caterpillar;

	//drawing a body for the player to apply physics and collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.density = 0;
	fixtureDef.friction = 0;
	fixtureDef.userData = fixtureData;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(11, 6);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);

	//making the box that detects if the player has hit something
	polygonShape.SetAsBox(11, 6);
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef); 

	eatenLeaves = 0;
}

void Caterpillar::Update(float deltaTime) {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;

	//left and right movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) //right
	{
		velocity.x += movementSpeed;
		//facingLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) //left
	{
		velocity.x -= movementSpeed;
		//facingLeft = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) //up
	{
		velocity.y -= movementSpeed;
		//facingForward = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S )|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) //down
	{
		velocity.y += movementSpeed;
		//facingForward = false;
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y); 

	

}

void Caterpillar::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Caterpillar.png"], position, sf::Vector2f(30.0, 15.0f));

}

void Caterpillar::OnBeginContact(b2Fixture* other) {
	FixtureData* data = (FixtureData*)other->GetUserData();
	if (data && data->type == FixtureDataType::Leaf) {
		eatenLeaves++;
		std::cout << eatenLeaves << std::endl;
	}
}

void Caterpillar::OnEndContact(b2Fixture* other) {

}
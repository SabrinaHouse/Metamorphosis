#include "Wasp.h"
#include <iostream>

Wasp::~Wasp() {
	Physics::world->DestroyBody(body);
}

void Wasp::Begin() {
	waspAnimation = Animation(0.2f,
		{
			AnimFrame(0.15, Resources::textures["WaspAnim1.png"]),
			AnimFrame(0.1, Resources::textures["WaspAnim2.png"]),
			AnimFrame(0.05, Resources::textures["WaspAnim3.png"]),
			AnimFrame(0.0, Resources::textures["WaspAnim2.png"]),
		});

	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Wasp;
	fixtureData->listener = this;


	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(startPosition.x, startPosition.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(10, 10);
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.friction = 0;
	fixtureDef.isSensor = true;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);

	//turn the sprite to face the correct direction
	if (horizontal) {
		if (TopOrLeft) {
			angle = sf::degrees(90); //GOING EAST
		}
		else {
			angle = sf::degrees(270); //GOING WEST
		}
	}
	else {
		if (TopOrLeft) {
			angle = sf::degrees(180); //GOING SOUTH
		}
		else {
			angle = sf::degrees(0); //GOING NORTH

		}
	}
}

void Wasp::Update(float deltaTime) {
	waspAnimation.Update(deltaTime);

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;


	if (horizontal) {
		if (TopOrLeft) {
			velocity.x += movementSpeed; //GOING EAST
		}
		else {
			velocity.x -= movementSpeed; //GOING WEST
		}
	}
	else {
		if (TopOrLeft) {
			velocity.y += movementSpeed; //GOING SOUTH
		}
		else {
			velocity.y -= movementSpeed; //GOING NORTH

		}
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);

	textureToDraw = waspAnimation.GetTexture();
}

void Wasp::Draw(Renderer& renderer) {
	renderer.Draw(textureToDraw, position, sf::Vector2f(30.0, 30.0f), angle);
}

void Wasp::OnBeginContact(b2Fixture* other) {
	FixtureData* data = (FixtureData*)other->GetUserData();
	if (data && data->type == FixtureDataType::Eggs) {
		hitEggs = true;
	}
	else if (data && data->type == FixtureDataType::Butterfly) {
		hitButterfly = true;
	}
}

void Wasp::OnEndContact(b2Fixture* other) {

}
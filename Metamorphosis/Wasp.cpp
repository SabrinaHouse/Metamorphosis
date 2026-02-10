#include "Wasp.h"
#include <iostream>

Wasp::~Wasp() {
	Physics::world->DestroyBody(body);
}

void Wasp::Begin() {
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

}

void Wasp::Update(float deltaTime) {
	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;

	if (horizontal) {
		if (TopOrLeft) {
			velocity.x += movementSpeed;
		}
		else {
			velocity.x -= movementSpeed;
		}
	}
	else {
		if (TopOrLeft) {
			velocity.y += movementSpeed;
		}
		else {
			velocity.y -= movementSpeed;
		}
	}

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
}

void Wasp::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Wasp.png"], position, sf::Vector2f(10.0, 10.0f));
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
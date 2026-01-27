#include "Mantis.h"
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

	int movementSpeed = 20;

	if (LeftToRight) {
		velocity.x += movementSpeed;
	}
	else {
		velocity.y += movementSpeed;

	}

	if (mantisClock.getElapsedTime().asSeconds() > 3) {
		if (LeftToRight) {
			velocity.x = velocity.x * -1;
		}
		else {
			velocity.y = velocity.y * -1;
		}

		mantisClock.restart();
	}


	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);

}


void Mantis::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Mantis.png"], position, sf::Vector2f(50, 40));
}
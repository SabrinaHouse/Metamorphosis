#include "Mantis.h"
#include <iostream>
sf::Clock mantisClock;

void Mantis::Begin() {
	mantisClock.start();

	runAnimation = Animation(0.4f,
		{
			AnimFrame(0.2, Resources::textures["Mantis1.png"]),
			AnimFrame(0.0, Resources::textures["Mantis2.png"]),
		});

	//tagging with the correct listener
	FixtureData* fixtureData = new FixtureData();
	fixtureData->type = FixtureDataType::Mantis;

	//box 2d body for collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(15, 15);
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.friction = 0;
	fixtureDef.userData = fixtureData;
	body->CreateFixture(&fixtureDef);
}

void Mantis::Update(float deltaTime) {
	runAnimation.Update(deltaTime);

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0;
	velocity.y = 0;

	//change only x velocity if left/right mantis
	if (LeftToRight) {
		//change the direction the mantis is moving
		if (flipped) {
			angle = sf::degrees(270);
			velocity.x -= movementSpeed;
		}
		else {
			angle = sf::degrees(90);
			velocity.x += movementSpeed;
		}
	}
	//change only y velocity if up/down mantis
	else {
		//change the direction the mantis is moving
		if (flipped) {
			angle = sf::degrees(0);
			velocity.y -= movementSpeed;

		}
		else {
			angle = sf::degrees(180);
			velocity.y += movementSpeed;
		}
	}

	if (mantisClock.getElapsedTime().asSeconds() > (rand() % 3) + 2 
		|| position.x < 0 || position.x > 550 || position.y < 0 || position.y > 550) {
		//change direction after 5 seconds
		//or if the mantis hits the barrier
		flipped = !flipped;
		mantisClock.restart();
	}

	body->SetLinearVelocity(velocity);
	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	textureToDraw = runAnimation.GetTexture();
}


void Mantis::Draw(Renderer& renderer) {
	renderer.Draw(textureToDraw, position, sf::Vector2f(30, 40), angle);
}
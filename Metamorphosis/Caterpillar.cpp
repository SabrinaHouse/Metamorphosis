#include "Caterpillar.h"
#include "Resources.h"
#include "Physics.h"
#include "Levels.h"
#include "Level1.h"
#include <iostream>

constexpr float M_PI = 22.0 / 7.0;
sf::Angle angle;
float32 bodyAngle;

void Caterpillar::Begin() {

	runAnimation = Animation(0.6f,
		{
			AnimFrame(0.3, Resources::textures["Caterpillar1.png"]),
			AnimFrame(0.0, Resources::textures["Caterpillar2.png"]),
		});

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
	hitMantis = false;
}

void Caterpillar::Update(float deltaTime) {
	runAnimation.Update(deltaTime);

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

	//cahnge which dirrection the body is facing based on what direction you are going
	//play animation if you are moving
	if (std::abs(velocity.y) > std::abs(velocity.x)) {
		if (velocity.y < 0.02f) {
			textureToDraw = runAnimation.GetTexture();
			angle = sf::degrees(0);
		}
		else if (velocity.y > 0.02f) {
			textureToDraw = runAnimation.GetTexture();
			angle = sf::degrees(180);
			
		}
		bodyAngle = 0.5 * b2_pi;

	}
	else if (std::abs(velocity.y) < std::abs(velocity.x) || (std::abs(velocity.y) == std::abs(velocity.x) && std::abs(velocity.y) !=0)) {
		if (velocity.x > 0.02f) {
			textureToDraw = runAnimation.GetTexture();
			angle = sf::degrees(90);
		}
		else if (velocity.x < 0.02f) {
			textureToDraw = runAnimation.GetTexture();
			angle = sf::degrees(270);
		}
		bodyAngle = 0 * b2_pi;

	} else {
		textureToDraw = Resources::textures["Caterpillar1.png"];
	}

	body->SetTransform(body->GetPosition(), bodyAngle);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);

}

void Caterpillar::Draw(Renderer& renderer) {
	renderer.Draw(textureToDraw, position, sf::Vector2f(20, 35), angle);

}

void Caterpillar::OnBeginContact(b2Fixture* other) {
	FixtureData* data = (FixtureData*)other->GetUserData();
	if (data && data->type == FixtureDataType::Leaf) {
		data->leaf->eaten = true;
	}

	if (data && data->type == FixtureDataType::Mantis) {
		hitMantis = true;
	}
}

void Caterpillar::OnEndContact(b2Fixture* other) {
}
	
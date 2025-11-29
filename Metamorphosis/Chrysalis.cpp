#include "Chrysalis.h"
#include "Resources.h"
#include "Physics.h"

constexpr float M_PI = 22.0 / 7.0;

bool facingLeft = false;

void Chrysalis::Begin() {
	//drawing a body for the player to apply physics and collisions
	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};
	fixtureDef.density = 4;
	fixtureDef.friction = 0;

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(2, 4);
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
	renderer.Draw(Resources::textures["Chrysalis.png"], position, sf::Vector2f(facingLeft ? -10.0f : 10.0, 10.0f));
}

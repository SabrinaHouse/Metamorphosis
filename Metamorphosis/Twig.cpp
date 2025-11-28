#include "Twig.h"
#include "Resources.h"
#include "Physics.h"

void Twig::Begin() {

	b2BodyDef bodyDef{};
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef{};

	b2PolygonShape polygonShape{};
	polygonShape.SetAsBox(2, 1);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void Twig::Draw(Renderer& renderer) {
	renderer.Draw(Resources::textures["Twig.png"], position, sf::Vector2f(leftSide ? 25.0f : -25.0f, 12.5f));
}
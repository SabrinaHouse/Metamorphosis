#include "Game.h"
#include "Camera.h"
#include "Resources.h"
#include "Renderer.h"
#include "Chrysalis.h"
#include "Physics.h"

Chrysalis chrysalis;

void Begin(const sf::Window& window) {
	for (auto& file : std::filesystem::directory_iterator("./Resources/"))
	{
		if (file.is_regular_file() && file.path().extension() == ".png") {
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	chrysalis.Begin();
}
void Update(float deltaTime) {
	Physics::Update(deltaTime);
	chrysalis.Update(deltaTime);
	//camera.position = chrysalis.position;

}
void Render(Renderer& renderer) {
	chrysalis.Draw(renderer);
}

#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Plant.hpp"

PlayScene* Plant::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Plant::Plant(std::string img, float x, float y, float radius, int price, float coolDown) :
	Sprite(img, x, y), price(price), coolDown(coolDown) {
	CollisionRadius = radius;
}
void Plant::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
	if (Target) {
		Engine::Point diff = Target->Position - Position;
		if (diff.Magnitude() > CollisionRadius) {
			Target->lockedTurrets.erase(lockedTurretIterator);
			Target = nullptr;
			lockedTurretIterator = std::list<Plant*>::iterator();
		}
	}
	if (!Target) {
		// Lock first seen target.
		// Can be improved by Spatial Hash, Quad Tree, ...
		// However, simply loop through all enemies is enough for this program.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
			Engine::Point diff = it->Position - Position;
			if (diff.Magnitude() <= CollisionRadius) {
				Target = dynamic_cast<Zombie*>(it);
				Target->lockedTurrets.push_back(this);
				lockedTurretIterator = std::prev(Target->lockedTurrets.end());
				break;
			}
		}
	}
	if (Target) {
		// Shoot reload.
		reload -= deltaTime;
		if (reload <= 0) {
			// shoot.
			reload = coolDown;
			CreatePea();
		}
	}
}
void Plant::Draw() const {
	Sprite::Draw();
}
int Plant::GetPrice() const {
	return price;
}

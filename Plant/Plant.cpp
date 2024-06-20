#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Plant.hpp"

#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"

PlayScene* Plant::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
Plant::Plant(std::string img, float x, float y,int hp,float radius, int price, float coolDown, PlantType plantType) :
	Sprite(img, x, y), hp(hp), price(price), coolDown(coolDown), plantType(plantType) {
	CollisionRadius = radius;
}
void Plant::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
    if(plantType == PlantType::SUNFLOWER) {
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreatePea();
        }
        return;
    }
	if(plantType == PlantType::LAWNMOWER) {
		if (Target) {
			CreatePea();
			Target = nullptr;
			TakeDamage(INT8_MAX);
		}
		return;
	}
	if (Target) {
		Engine::Point diff = Target->Position - Position;
		if (diff.Magnitude() > CollisionRadius) {
			Target->lockedPlants.erase(lockedPlantIterator);
			Target = nullptr;
			lockedPlantIterator = std::list<Plant*>::iterator();
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
				Target->lockedPlants.push_back(this);
				lockedPlantIterator = std::prev(Target->lockedPlants.end());
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

void Plant::TakeDamage(float damage) {
	Engine::LOG(Engine::INFO) << "taking damage";
	hp -= damage;
	if (hp <= 0) {
		getPlayScene()->lawn[pos_x][pos_y] = nullptr;
		getPlayScene()->mapState[pos_x][pos_y] = TILE_EMPTY;
		getPlayScene()->TowerGroup->RemoveObject(objectIterator);
	}
}

void Plant::SetPos(int x, int y) {
	pos_x = x;
	pos_y = y;
}

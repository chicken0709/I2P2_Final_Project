#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"

#include "Plant.hpp"
#include "Zombie/Zombie.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* Plant::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Plant::Plant(std::string img, float x, float y, int hp, int price, float coolDown, PlantType plantType, std::string name, int totalFrameCount, int frameWidth, int frameHeight, std::vector<int> animationFrameCount) :
	Sprite(img, x, y, 0, 0), hp(hp), price(price), coolDown(coolDown), plantType(plantType), name(name), totalFrameCount(totalFrameCount), frameWidth(frameWidth), frameHeight(frameHeight) ,animationFrameCount(animationFrameCount){
}

void Plant::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();

	if (!Enabled)
		return;
    if(plantType == PlantType::SUNFLOWER || plantType == PlantType::OTHER) {
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreatePea();
        }
        return;
    }
	if(plantType == PlantType::CHERRYBOMB) {
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
			TakeDamage(INT16_MAX, true);
		}
		return;
	}
	// CRASH !!!
	/*if (Target) {
		Engine::Point diff = Target->Position - Position;
		if (diff.Magnitude() > CollisionRadius) {
			Target->lockedPlants.erase(lockedPlantIterator);
			Target = nullptr;
			lockedPlantIterator = std::list<Plant*>::iterator();
		}
	}*/
	if (!Target) {
		// Lock first seen target.
		for (auto& it : scene->EnemyGroup->GetObjects()) {
			if (static_cast<int>(it->Position.y / 150) == static_cast<int>(Position.y / 150)) {
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

void Plant::TakeDamage(float damage, bool shovel) {
	Engine::LOG(Engine::INFO) << "taking damage";
	hp -= damage;
	if(plantType == PlantType::LAWNMOWER) {
		getPlayScene()->PlantGroup->RemoveObject(objectIterator);
		return;
	}
	if (hp <= 0) {
        if(!shovel)
            AudioHelper::PlayAudio("gulp.ogg");
		getPlayScene()->plant_lawn[pos_x][pos_y] = nullptr;
		getPlayScene()->mapState[pos_x][pos_y] = TILE_EMPTY;
		getPlayScene()->PlantGroup->RemoveObject(objectIterator);
	}
}

void Plant::SetPos(int x, int y) {
	pos_x = x;
	pos_y = y;
}


PlantType Plant::GetPlantType() {
	return plantType;
}
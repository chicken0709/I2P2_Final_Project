#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"

#include "Plant.hpp"
#include "Zombie/Zombie.hpp"
#include "Scene/PlayScene.hpp"

PlayScene* Plant::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Plant::Plant(
	std::string name,
	std::string img,
	float x,
	float y,
	int hp,
	int price,
	float coolDown,
	PlantType plantType
) :
	Sprite(img, x, y),
	name(name),
	hp(hp),
	price(price),
	coolDown(coolDown),
	plantType(plantType)
{
}

Plant::Plant(
	std::string name,
	int totalFrameCount,
	int frameWidth,
	int frameHeight,
	std::vector<int> animationFrameCount,
	float x,
	float y,
	int hp,
	int price,
	float coolDown,
	PlantType plantType
) :
	Sprite(1, totalFrameCount, "play/" + name + "_animation_1.png", x, y),
	name(name),
	totalFrameCount(totalFrameCount),
	frameWidth(frameWidth),
	frameHeight(frameHeight),
	animationFrameCount(animationFrameCount),
	hp(hp),
	price(price),
	coolDown(coolDown),
	plantType(plantType)
{
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
}

void Plant::Update(float deltaTime) {
	PlayScene* scene = getPlayScene();
	if (!Enabled)
		return;
    if(plantType == PlantType::SUNFLOWER) {
        reload -= deltaTime;
        if (reload <= 0) {
            reload = coolDown;
            CreatePea();
        }
    }
	if(plantType == PlantType::CHERRYBOMB) {
		reload -= deltaTime;
		if (reload <= 0) {
			reload = coolDown;
			CreatePea();
			return;
		}
	}
	if(plantType == PlantType::LAWNMOWER) {
		if (Target) {
			CreatePea();
			Target = nullptr;
			TakeDamage(INT16_MAX, true);
			return;
		}
	}
	if (plantType == PlantType::PEASHOOTER) {
		if (!Target) {
			// Lock first seen target
			for (auto& it : scene->EnemyGroup->GetObjects()) {
				if (static_cast<int>(it->Position.y / 150) == static_cast<int>(Position.y / 150)) {
					Target = dynamic_cast<Zombie*>(it);
					Target->lockedPlants.push_back(this);
					break;
				}
			}
		}
		if (Target) {
			// Shoot reload
			reload -= deltaTime;
			if (reload <= 0) {
				// Shoot
				reload = coolDown;
				CreatePea();
			}
		}
	}
	// No animation
	if (plantType == PlantType::LAWNMOWER || plantType == PlantType::OTHER) {
		Sprite::Update(deltaTime);
		return;
	}

	// Animation
	int buffer = 0;
	currentFrameCount = animationFrameCount[animationIndex];
	for (int i = 0; i < animationIndex; i++) {
		buffer += animationFrameCount[i] * frameWidth;
	}

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		timeTicks = 0;
	}
	int phase = floor(timeTicks / timeSpan * currentFrameCount);

	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer + phase * frameWidth, 0, frameWidth, frameHeight);
	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
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
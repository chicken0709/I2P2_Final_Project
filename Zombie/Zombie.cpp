#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <string>

#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"

#include "Zombie.hpp"
#include "Scene/PlayScene.hpp"
#include "Plant/Plant.hpp"

const int ZDMG = 1;

PlayScene* Zombie::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Zombie::OnExplode() {
	if (getPlayScene()->MapId == 2) {
		AudioHelper::PlayAudio("bowlingimpact.ogg");
	} else {
		AudioHelper::PlayAudio("limbs_pop.mp3");
	}
}

Zombie::Zombie(
	std::string name,
	int totalFrameCount,
	int frameWidth,
	int frameHeight,
	std::vector<int> animationFrameCount,
	float x,
	float y,
	float radius,
	float speed,
	float originalSpeed,
	float hp
) :
	Sprite(1,totalFrameCount,"play/" + name + "_animation_1.png", x, y),
	name(name),
	totalFrameCount(totalFrameCount),
	frameWidth(frameWidth),
	frameHeight(frameHeight),
	animationFrameCount(animationFrameCount),
	speed(speed),
	originalSpeed(originalSpeed),
	hp(hp)
{
	CollisionRadius = radius;
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
}

void Zombie::TakeDamage(float damage) {
	hp -= damage;
	if (zombieType == ZombieType::NEWSPAPER) {
		if(hp <= 300) {
			if(!isRage) {
				isRage = true;
				AudioHelper::PlayAudio("newspaper_rarrgh.ogg");
			}
		}
	}
	if (hp <= 0) {
		if (isDead == false) {
			isDead = true;
			OnExplode();
		}
        return;
	}
	switch(zombieType) {
		case ZombieType::BASIC_FLAG:
			AudioHelper::PlayAudio("splat.ogg");
			break;
		case ZombieType::NEWSPAPER:
			AudioHelper::PlayAudio("splat.ogg");
			break;
		case ZombieType::BUCKET:
			AudioHelper::PlayAudio("shieldhit.ogg");
			break;
		case ZombieType::CONE_FOOTBALL:
			AudioHelper::PlayAudio("plastichit.ogg");
			break;
	}
}

void Zombie::Update(float deltaTime) {
	if (hp > 0) {
		float remainSpeed = speed * deltaTime;
		while (remainSpeed > 0) {
			// Calculate current block
			int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize) - 1);//somehow need to magically -1
			int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
			// Reach house
			if (x < 0) {
				if(getPlayScene()->mower_available[y - 1] != nullptr) {
					getPlayScene()->mower_available[y - 1]->Target = this;
					getPlayScene()->mower_available[y - 1] = nullptr;
				}else {
					if(x <= -2)
						getPlayScene()->ReachHouse();
				}
			}
			// Check outside lawn
			bool outside = false;
			if (x >= PlayScene::MapWidth) {
				x = PlayScene::MapWidth - 1;
				outside = true;
			}
			// Make sure in range
			if (y < 0) y = 0;
			if (y > PlayScene::MapHeight) y = PlayScene::MapHeight;
			// Stop at plant
			if (!outside) {
				if (getPlayScene()->mapState[y - 1][x] == TILE_OCCUPIED) {
					isEating = true;
					Velocity = Engine::Point(0, 0);
					reload -= deltaTime;
					// eat
					if(animationIndex == 0)
						animationIndex = 1;
					else if(animationIndex == 4)
						animationIndex = 5;
					if (reload <= 0) {
						reload = coolDown;
						Plant *plant = getPlayScene()->plant_lawn[y - 1][x];
						plant->TakeDamage(ZDMG, false);
						AudioHelper::PlayAudio("chomp.mp3");
					}
					remainSpeed = 0;
				} else {
					isEating = false;
					if (FinishedRageAnimation) {
						animationIndex = 4;
					} else {
						animationIndex = 0;
					}
				}
			}
			// Moving
			if (isEating == false) {
				// Calculate move target
				Engine::Point target((x - 1) * PlayScene::BlockSize + PlayScene::BlockSize / 2, Position.y);
				Engine::Point vec = target - Position;
				float distance = vec.Magnitude();

				// Move
				if (remainSpeed > distance) {
					Position = target;
					remainSpeed -= distance;
				}
				else {
					Engine::Point normalized = vec.Normalize();
					Velocity = normalized * remainSpeed / deltaTime;
					Position.x += normalized.x * remainSpeed;
					Position.y += normalized.y * remainSpeed;
					remainSpeed = 0;
				}
			}
		}
	}

	// Animation
	if (isDead) {
		if (!FinalAnimation) {
			RageAnimation = false;
			FinishedRageAnimation = true;
			FinalAnimation = true;
			timeTicks = 0;
		}
	}
	else if(isRage) {
		if(!RageAnimation && !FinishedRageAnimation) {
			RageAnimation = true;
			speed = 0;
			timeTicks = 0;
		}
	}

	if(isSlow) {
		Tint = al_map_rgb(125,125,255);
	}

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		if(FinalAnimation) {
			remove = true;
			for (auto& it: lockedPlants) {
				it->Target = nullptr;
			}
			getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
			return;
		}
		if(RageAnimation) {
			animationIndex = 4;
			speed = 30;
			RageAnimation = false;
			FinishedRageAnimation = true;
		}
		timeTicks = 0;
	}

	int buffer = 0;

	if (FinalAnimation)
		animationIndex = 2;
	else if (RageAnimation)
		animationIndex = 3;

	if (animationIndex <= 2)
		currentFrameCount = animationFrameCount[animationIndex];
	else if (animationIndex == 3) {
		currentFrameCount = 13;
	}
	else if (animationIndex == 4) {
		currentFrameCount = 47;
	}
	else if (animationIndex == 5) {
		currentFrameCount = 24;
	}

	int phase = floor(timeTicks / timeSpan * currentFrameCount);

	ALLEGRO_BITMAP* subBitmap;
	if (animationIndex <= 2) {
		for(int i = 0;i < animationIndex;i++) {
			buffer = buffer + animationFrameCount[i] * frameWidth;
		}
		subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer + phase * frameWidth, 0, frameWidth, frameHeight);
	}
	else {
		if(changeSize == 0) {
			bmp = rageSpriteSheet;
			Size.x = GetBitmapWidth() / 84 * 1.6;
			Size.y = GetBitmapHeight() * 1.6;
			changeSize = 1;
		}
		if(animationIndex == 4)
			buffer = 13 * frameWidth;
		else if(animationIndex == 5)
			buffer = 50 * frameWidth;
		subBitmap = al_create_sub_bitmap(rageSpriteSheet.get(), buffer +phase * frameWidth, 0, frameWidth, frameHeight);
	}
	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
}

void Zombie::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}

void Zombie::UpdateSpeed() {
	if (hp <= 0) return;
    if(speed == originalSpeed) AudioHelper::PlayAudio("frozen.ogg");
    speed = originalSpeed / 2;
}
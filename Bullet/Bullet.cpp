#include <random>

#include "Engine/Collider.hpp"
#include "Engine/LOG.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"

#include "Bullet.hpp"
#include "Scene/PlayScene.hpp"
#include "Zombie/Zombie.hpp"

PlayScene* Bullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Bullet::OnExplode(Zombie* enemy) {
}

Bullet::Bullet(
	std::string img,
	float speed,
	float damage,
	Engine::Point position
) :
	Sprite(img, position.x, position.y), speed(speed), damage(damage)
{
	Velocity = forwardDirection.Normalize() * speed;
	CollisionRadius = 4;
}

Bullet::Bullet(
	std::string name,
	int totalFrameCount,
	int frameWidth,
	int frameHeight,
	float speed,
	float damage,
	Engine::Point position
) :
	Sprite(1,totalFrameCount,"play/" + name + "_animation_1.png", position.x, position.y),
	totalFrameCount(totalFrameCount),
	frameWidth(frameWidth),
	frameHeight(frameHeight),
	speed(speed),
	damage(damage)
{
	Velocity = forwardDirection.Normalize() * speed;
}

void Bullet::Update(float deltaTime) {
	PlayScene* scene = getPlayScene();
	int bulletPositionY = static_cast<int>(Position.y / 150);
	// Loop through zombies
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Zombie* zombie = dynamic_cast<Zombie*>(it);
		int zombiePositionY = static_cast<int>(zombie->Position.y / 150);
		if (!zombie->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, zombie->Position, zombie->CollisionRadius) && zombiePositionY == bulletPositionY) {
            OnExplode(zombie);
			if (bulletType != BulletType::BOMB_BOWLING_BALL) zombie->TakeDamage(damage);
			if (bulletType == BulletType::MOWER) {
			} else if (bulletType == BulletType::BOWLING_BALL) {
				if (bulletPositionY == 1) {
					Velocity = Engine::Point(1, 1).Normalize() * speed;
				} else if (bulletPositionY == 5) {
					Velocity = Engine::Point(1, -1).Normalize() * speed;
				} else {
					if(Velocity.Normalize() == Engine::Point(1, 1).Normalize()) {
						Velocity = Engine::Point(1, -1).Normalize() * speed;
					} else if(Velocity.Normalize() == Engine::Point(1, -1).Normalize()) {
						Velocity = Engine::Point(1, 1).Normalize() * speed;
					} else {
						std::random_device dev;
						std::mt19937 rng(dev());
						std::uniform_int_distribution<std::mt19937::result_type> id(1, 2);
						if (id(rng) == 1) {
							Velocity = Engine::Point(1, 1).Normalize() * speed;
						} else {
							Velocity = Engine::Point(1, -1).Normalize() * speed;
						}
					}
				}
			} else {
            	getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            	return;
            }
		}
	}
	// Check bowling ball y axis boundary
	if (bulletType == BulletType::BOWLING_BALL) {
		if(Position.y <= 160 && Velocity.Normalize() != Engine::Point(1, 0)) {
			Velocity = Engine::Point(1, 1).Normalize() * speed;
		} else if (Position.y >= 800 && Velocity.Normalize() != Engine::Point(1, 0)) {
			Velocity = Engine::Point(1, -1).Normalize() * speed;
		}
	}
	// Check out of boundary
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(1, 1), PlayScene::GetClientSize())) {
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
		return;
	}

	// Animation
	if (bulletType == BulletType::BOWLING_BALL || bulletType == BulletType::BOMB_BOWLING_BALL) {
		int buffer = 0;
		int currentFrameCount = totalFrameCount;

		timeTicks += deltaTime;
		if (timeTicks >= timeSpan) {
			timeTicks = 0;
		}

		int phase = floor(timeTicks / timeSpan * currentFrameCount);
		ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer + phase * frameWidth, 0, frameWidth, frameHeight);
		bmp.reset(subBitmap, al_destroy_bitmap);
	}

	Sprite::Update(deltaTime);
}

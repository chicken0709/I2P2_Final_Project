#include "Bullet.hpp"
#include "Engine/Collider.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include <random>

#include "Engine/LOG.hpp"
#include "Engine/AudioHelper.hpp"

PlayScene* Bullet::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Bullet::OnExplode(Zombie* enemy) {
}

Bullet::Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
}
Bullet::Bullet(int index,int totalFrameCount,int frameWidth,int frameHeight,std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent)
	:Sprite(img, position.x, position.y), speed(speed), damage(damage), parent(parent) {
	Velocity = forwardDirection.Normalize() * speed;
	Rotation = rotation;
	CollisionRadius = 4;
	this->index = index;
	this->totalFrameCount = totalFrameCount;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
}
void Bullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
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
				if(getPlayScene()->MapId == 2 && !getPlayScene()->allBullets_isDestroy.empty())
					getPlayScene()->allBullets_isDestroy[index] = true;
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
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(1, 1), PlayScene::GetClientSize())) {
		if(getPlayScene()->MapId == 2&& !getPlayScene()->allBullets_isDestroy.empty())
			getPlayScene()->allBullets_isDestroy[index] = true;
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
	}
}

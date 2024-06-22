#include "Bullet.hpp"
#include "Engine/Collider.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"

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

void Bullet::Update(float deltaTime) {
	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Loop through zombies
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Zombie* zombie = dynamic_cast<Zombie*>(it);
		if (!zombie->Visible)
			continue;
		int bulletPositionY = static_cast<int>(Position.y / 150);
		int zombiePositionY = static_cast<int>(zombie->Position.y / 150);
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, zombie->Position, zombie->CollisionRadius) && zombiePositionY == bulletPositionY) {
            OnExplode(zombie);
			zombie->TakeDamage(damage);
			if(bulletType != BulletType::MOWER) {
                getPlayScene()->BulletGroup->RemoveObject(objectIterator);
                return;
            }
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(1, 1), PlayScene::GetClientSize()))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}

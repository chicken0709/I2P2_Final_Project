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
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However, simply loop through all enemies is enough for this program.
	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Zombie* enemy = dynamic_cast<Zombie*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
			OnExplode(enemy);
			enemy->TakeDamage(damage);
			if(bullettype != Bullettype::MOWER)
				getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(1, 1), PlayScene::GetClientSize()))
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}

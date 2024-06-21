#include "Bullet.hpp"
#include "Engine/Collider.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Plant/Plant.hpp"
#include "Bullet/FirePea.hpp"

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

    if(bulletType == BulletType::BASICPEA) {
        int pos_x = static_cast<int>(Position.x / 150);
        int pos_y = static_cast<int>(Position.y / 150);
        if (pos_x <= PlayScene::MapWidth) {
            Plant *plant = getPlayScene()->lawn[pos_y - 1][pos_x - 1];
            if(plant != nullptr && plant->GetPlantType() == PlantType::TORCHWOOD) {
                getPlayScene()->BulletGroup->AddNewObject(new FirePea(Position, Engine::Point(1, 0), 0, nullptr));
                getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            }
        }
    }

	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Zombie* enemy = dynamic_cast<Zombie*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
            OnExplode(enemy);
			enemy->TakeDamage(damage, bulletType);
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

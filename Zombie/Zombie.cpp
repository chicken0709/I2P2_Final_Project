#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet.hpp"
#include "Zombie.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Plant/Plant.hpp"
const int ZDMG = 1;

PlayScene* Zombie::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

void Zombie::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
    AudioHelper::PlayAudio("limbs_pop.mp3");
}

Zombie::Zombie(std::string img, float x, float y, float radius, float speed, float originalSpeed, float hp, int money,float cooldown) :
	Engine::Sprite(img, x, y), speed(speed), originalSpeed(originalSpeed), hp(hp), money(money), coolDown(cooldown){
	CollisionRadius = radius;
}

void Zombie::TakeDamage(float damage) {
	hp -= damage;
    AudioHelper::PlayAudio("splat.ogg");
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedPlants)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
	}
}

void Zombie::Update(float deltaTime) {


	float remainSpeed = speed * deltaTime;
	while (remainSpeed > 0) {
		//calc current block
		int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize) - 1);//somehow need to magically -1
		int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));

		//reach house
		if (x < 0) {
			getPlayScene()->Hit(Position.y);
			Sprite::Update(deltaTime);
			return;
		}

		//check outside lawn
		bool outside = false;
		if (x >= PlayScene::MapWidth) {
			x = PlayScene::MapWidth - 1;
			outside = true;
		}

		//make sure in range
		if (y < 0) y = 0;
		if (y >= PlayScene::MapHeight) y = PlayScene::MapHeight - 1;

		//stop at plant
		if (!outside) {
			if (getPlayScene()->mapState[y - 1][x] == TILE_OCCUPIED) {//is 1-base so weird
				Velocity = Engine::Point(0, 0);
				Sprite::Update(deltaTime);
				reload -= deltaTime;
				//eat
				if(reload <= 0) {
					reload = coolDown;
					Plant* plant = getPlayScene()->lawn[y - 1][x];
					plant->TakeDamage(ZDMG);
				}
				return;
			}
		}


		//calc move target
		Engine::Point target((x - 1) * PlayScene::BlockSize + PlayScene::BlockSize / 2, Position.y);
		Engine::Point vec = target - Position;
		float distance = vec.Magnitude();

		//if can reach,then reach XD
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
	//somehow -1
	Rotation = atan2(Velocity.y, Velocity.x * -1);
	Sprite::Update(deltaTime);

}

void Zombie::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}

void Zombie::UpdateSpeed() {
    if(speed == originalSpeed) AudioHelper::PlayAudio("frozen.ogg");
    speed = originalSpeed / 2;
}

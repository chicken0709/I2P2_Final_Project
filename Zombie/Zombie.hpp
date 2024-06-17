#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <list>
#include <vector>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class Bullet;
class PlayScene;
class Plant;

class Zombie : public Engine::Sprite {
protected:
	std::vector<Engine::Point> path;
	float speed;
    float originalSpeed;
	float hp;
	int money;
	PlayScene* getPlayScene();
	virtual void OnExplode();
public:
	std::list<Plant*> lockedPlants;
	std::list<Bullet*> lockedBullets;
	Zombie(std::string img, float x, float y, float radius, float speed, float originalSpeed, float hp, int money);
	void Hit(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	void UpdateSpeed();
};
#endif // ZOMBIE_HPP

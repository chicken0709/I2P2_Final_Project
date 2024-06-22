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
	float reload = 0;
	float coolDown;
	PlayScene* getPlayScene();
	virtual void OnExplode();
public:
	std::list<Plant*> lockedPlants;
	std::list<Bullet*> lockedBullets;
	std::string name;
	Zombie(std::string name,int index,int totalFrameCount,int frameWidth,int frameHeight,std::vector<int> animationFrameCount,std::string img, float x, float y, float radius, float speed, float originalSpeed, float hp, int money, float cooldown);
	void TakeDamage(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	void UpdateSpeed();

	int index;

	int totalFrameCount;
	int frameWidth;
	int frameHeight;
	int animationIndex = 0;
	std::vector<int> animationFrameCount;
};
#endif // ZOMBIE_HPP

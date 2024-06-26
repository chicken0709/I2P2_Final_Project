#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <list>
#include <vector>
#include <string>

#include "Engine/Sprite.hpp"
#include "Bullet/Bullet.hpp"

class Bullet;
class PlayScene;
class Plant;

enum class ZombieType {
	BASIC_FLAG, CONE_FOOTBALL, BUCKET, NEWSPAPER
};

class Zombie : public Engine::Sprite {
protected:
	int index;
	float speed;
    float originalSpeed;
	float hp;
	float reload = 0;
	float coolDown = 0.5;
	ZombieType zombieType;
	PlayScene* getPlayScene();
	virtual void OnExplode();
	// Animation
	std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
	std::shared_ptr<ALLEGRO_BITMAP> rageSpriteSheet;
	int frameCount;
	int frameWidth;
	int frameHeight;
	int currentFrameCount;
	int totalFrameCount;
	int animationIndex = 0;
	std::vector<int> animationFrameCount;
	float timeTicks;
	float timeSpan = 3.5;
	float posX;
	float posY;
	bool FinalAnimation = false;
	bool RageAnimation = false;
	bool FinishedRageAnimation = false;
	bool changeSize = false;
	bool remove = false;
	bool isRage = false;
	bool isEating = false;
public:
	std::list<Plant*> lockedPlants;
	std::string name;
	Zombie(std::string name, int index, int totalFrameCount, int frameWidth, int frameHeight, std::vector<int> animationFrameCount, float x, float y, float radius, float speed, float originalSpeed, float hp);
	void TakeDamage(float damage);
	void Update(float deltaTime) override;
	void Draw() const override;
	void UpdateSpeed();
	bool isSlow = false;
	bool isDead = false;
};
#endif // ZOMBIE_HPP

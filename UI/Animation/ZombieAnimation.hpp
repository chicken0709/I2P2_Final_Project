#ifndef ZOMBIEANIMATION_HPP
#define ZOMBIEANIMATION_HPP
#include <string>

#include "Engine/Sprite.hpp"
#include "Zombie/Zombie.hpp"

class PlayScene;

class ZombieAnimation : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	float timeSpan = 0.5;
	float posX;
	float posY;
	int index;

	std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
	int frameCount;
	int frameWidth;
	int frameHeight;
	int currentFrameCount;
	std::vector<int> animationFrameCount;
	Zombie* currentZombie;

	bool FinalAnimation = false;
	bool RageAnimation = false;
	bool FinishedRageAnimation = false;
public:

	ZombieAnimation(std::string name,int index,int totalFrameCount,float x, float y);

	void Update(float deltaTime) override;


};
#endif // ZOMBIEANIMATION_HPP

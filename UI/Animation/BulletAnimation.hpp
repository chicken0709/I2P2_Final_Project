#ifndef BULLETANIMATION_HPP
#define BULLETANIMATION_HPP
#include <string>

#include "Engine/Sprite.hpp"
#include "Bullet/Bullet.hpp"

class PlayScene;

class BulletAnimation : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	float timeSpan = 0.5;
	std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
	Bullet* currentBullet;
	int frameWidth;
	int frameHeight;
	int totalFrameCount;
	int index;
public:

	BulletAnimation(std::string name,int index,int totalFrameCount,float x, float y);

	void Update(float deltaTime) override;

};
#endif // BULLETANIMATION_HPP

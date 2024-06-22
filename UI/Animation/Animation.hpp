#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <string>

#include "Engine/Sprite.hpp"

class PlayScene;

class Animation : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	float timeSpan = 0.5;
	float posX;
	float posY;
	int blockX;
	int blockY;
	std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
	int frameCount;
	int frameWidth;
	int frameHeight;
public:

	Animation(std::string name,int frameCount,int frameWidth,int frameHeight, int index, float x, float y, int blockX, int blockY);

	void Update(float deltaTime) override;

};
#endif // ANIMATION_HPP

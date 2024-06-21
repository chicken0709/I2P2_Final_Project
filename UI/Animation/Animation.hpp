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
public:
	Animation(std::string name,float x, float y,int posX,int posY);
	void Update(float deltaTime) override;

};
#endif // ANIMATION_HPP

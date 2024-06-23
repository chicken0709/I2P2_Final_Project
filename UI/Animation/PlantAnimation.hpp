#ifndef PLANTANIMATION_HPP
#define PLANTANIMATION_HPP
#include <string>

#include "Engine/Sprite.hpp"
#include "Plant/Plant.hpp"

class PlayScene;

class PlantAnimation : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	float timeSpan = 0.5;
	float posX;
	float posY;
	int blockX;
	int blockY;
	std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
	Plant* currentPlant;
	PlantType planttype = PlantType::NUL;
	int currentFrameCount;
public:

	PlantAnimation(std::string name,int totalFrameCount,float x, float y, int blockX, int blockY);

	void Update(float deltaTime) override;

};
#endif // PLANTANIMATION_HPP

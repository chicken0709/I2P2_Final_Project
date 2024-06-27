#include <cmath>
#include "PlantAnimation.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Plant/Plant.hpp"
#include "Scene/PlayScene.hpp"


PlayScene* PlantAnimation::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

PlantAnimation::PlantAnimation(std::string name,int totalFrameCount,float x, float y, int blockX, int blockY)
	: Sprite(1,totalFrameCount,"play/" + name + "_animation_1.png", x, y),timeTicks(0), posX(x), posY(y), blockX(blockX), blockY(blockY)
{
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
	timeSpan = 1.5;
}

void PlantAnimation::Update(float deltaTime) {
	if (getPlayScene()->mapState[blockY - 1][blockX - 1] != TILE_OCCUPIED) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int animationIndex = 0;
	int buffer = 0;

	currentPlant = getPlayScene()->plant_lawn[blockY - 1][blockX - 1];
	animationIndex = currentPlant->animationIndex;
	currentFrameCount = currentPlant->animationFrameCount[animationIndex];
	for(int i = 0;i < animationIndex;i++) {
		buffer += currentPlant->animationFrameCount[i] * currentPlant->frameWidth;
	}

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		timeTicks = 0;
	}

	int phase = floor(timeTicks / timeSpan * currentFrameCount);

	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer + phase * currentPlant->frameWidth, 0, currentPlant->frameWidth, currentPlant->frameHeight);
	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
}

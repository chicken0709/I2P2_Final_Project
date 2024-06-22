#include <cmath>
#include "Animation.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Resources.hpp"
#include "Plant/Plant.hpp"
#include "Scene/PlayScene.hpp"


PlayScene* Animation::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Animation::Animation(std::string name,int frameCount,int frameWidth,int frameHeight,int index,float x, float y, int blockX, int blockY)
	: Sprite(1,frameCount,"play/" + name + "_animation_" + std::to_string(index) + ".png", x, y),frameCount(frameCount),frameWidth(frameWidth),frameHeight(frameHeight), timeTicks(0), posX(x), posY(y), blockX(blockX), blockY(blockY) {
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_" + std::to_string(index) + ".png");
	timeSpan = 1.75;
}

void Animation::Update(float deltaTime) {
	if (getPlayScene()->mapState[blockY - 1][blockX - 1] != TILE_OCCUPIED)
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		timeTicks = 0;
	}
	int phase = floor(timeTicks / timeSpan * frameCount);

	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), phase * frameWidth, 0, frameWidth, frameHeight);
	bmp.reset(subBitmap, al_destroy_bitmap);

	Sprite::Update(deltaTime);
}

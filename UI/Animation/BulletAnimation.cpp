#include <cmath>
#include "BulletAnimation.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Plant/Plant.hpp"
#include "Scene/PlayScene.hpp"


PlayScene* BulletAnimation::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

BulletAnimation::BulletAnimation(std::string name,int index,int totalFrameCount,float x, float y)
	: Sprite(1,totalFrameCount,"play/" + name + "_animation_1.png", x, y),index(index), timeTicks(0)
{
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
	timeSpan = 1.5;
	currentBullet = getPlayScene()->allBullets[index];
	frameHeight = currentBullet->frameHeight;
	frameWidth = currentBullet->frameWidth;
	this->totalFrameCount = totalFrameCount;
}

void BulletAnimation::Update(float deltaTime) {
	if (getPlayScene()->allBullets_isDestroy[index] == true) {
		Engine::LOG(Engine::INFO) << "destroy";
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int buffer = 0;
	int currentFrameCount = totalFrameCount;

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		timeTicks = 0;
	}

	int phase = floor(timeTicks / timeSpan * currentFrameCount);
	Position = currentBullet->Position;
	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer + phase * frameWidth, 0, frameWidth, frameHeight);
	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
}

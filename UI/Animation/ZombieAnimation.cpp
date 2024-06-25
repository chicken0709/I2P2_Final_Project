#include <cmath>
#include "ZombieAnimation.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Plant/Plant.hpp"
#include "Scene/PlayScene.hpp"


PlayScene* ZombieAnimation::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

ZombieAnimation::ZombieAnimation(std::string name,int index,int totalFrameCount,float x, float y)
	: Sprite(1,totalFrameCount,"play/" + name + "_animation_1.png", x, y),index(index), timeTicks(0), posX(x), posY(y)
{
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
	timeSpan = 3.5;
	currentZombie = getPlayScene()->allZombies[index];
	if(currentZombie->GetZombieType() == ZombieType::NEWSPAPER)
		rageSpriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_2.png");
	frameHeight = currentZombie->frameHeight;
	frameWidth = currentZombie->frameWidth;
	animationFrameCount = currentZombie->animationFrameCount;
}

void ZombieAnimation::Update(float deltaTime) {
	if (getPlayScene()->allZombies_isDestroy[index] == true) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	if(currentZombie->isDead) {
		if(!FinalAnimation) {
			RageAnimation = false;
			FinishedRageAnimation = true;
			FinalAnimation = true;
			timeTicks = 0;
		}
	}
	else if(currentZombie->isRage) {
		if(!RageAnimation && !FinishedRageAnimation) {
			RageAnimation = true;
			currentZombie->SetSpeed(0);
			timeTicks = 0;
		}
	}

	if(currentZombie->isSlow) {
		Tint = al_map_rgb(125,125,255);
	}

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		if(FinalAnimation) {
			getPlayScene()->EffectGroup->RemoveObject(objectIterator);
			return;
		}
		if(RageAnimation) {
			currentZombie->animationIndex = 4;
			currentZombie->SetSpeed(50);
			RageAnimation = false;
			FinishedRageAnimation = true;
		}
		timeTicks = 0;
	}

	int animationIndex = 0;
	int buffer = 0;

	if(FinalAnimation)
		animationIndex = 2;
	else if(RageAnimation)
		animationIndex = 3;
	else
		animationIndex = currentZombie->animationIndex;
	if(animationIndex <= 2)
		currentFrameCount = animationFrameCount[animationIndex];
	else if(animationIndex == 3) {
		currentFrameCount = 13;
	}
	else if(animationIndex == 4) {
		currentFrameCount = 47;
	}
	else if(animationIndex == 5) {
		currentFrameCount = 24;
	}



	int phase = floor(timeTicks / timeSpan * currentFrameCount);
	if(!FinalAnimation && !RageAnimation)
		Position = currentZombie->Position;

	ALLEGRO_BITMAP* subBitmap;
	if(animationIndex <= 2) {
		for(int i = 0;i < animationIndex;i++) {
			buffer = buffer + animationFrameCount[i] * frameWidth;
		}
		subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer +phase * frameWidth, 0, frameWidth, frameHeight);
	}
	else {
		if(changeSize == 0) {
			bmp = rageSpriteSheet;
			Size.x = GetBitmapWidth()/84 * 1.6;
			Size.y = GetBitmapHeight() * 1.6;
			changeSize = 1;
		}
		if(animationIndex == 4)
			buffer = 13 * frameWidth;
		else if(animationIndex == 5)
			buffer = 50 * frameWidth;
		subBitmap = al_create_sub_bitmap(rageSpriteSheet.get(), buffer +phase * frameWidth, 0, frameWidth, frameHeight);
	}

	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
}

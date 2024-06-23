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
	timeSpan = 1;
	currentZombie = getPlayScene()->allZombies[index];
	frameHeight = currentZombie->frameHeight;
	frameWidth = currentZombie->frameWidth;
	animationFrameCount = currentZombie->animationFrameCount;
}

void ZombieAnimation::Update(float deltaTime) {
	if(currentZombie->index == 0)
		Engine::LOG(Engine::INFO) << "isDead" << currentZombie->isDead << " isRage" << currentZombie->isRage;
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
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		if(FinalAnimation) {
			getPlayScene()->EffectGroup->RemoveObject(objectIterator);
			return;
		}
		if(RageAnimation) {
			if(currentZombie->index == 0)
				Engine::LOG(Engine::INFO) << "end Rage";
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
	if(currentZombie->index ==0)
		Engine::LOG(Engine::INFO) << "animationIndex" << animationIndex;
	currentFrameCount = animationFrameCount[animationIndex];
	if(currentZombie->index ==0)
		Engine::LOG(Engine::INFO) << "currentframeCount" << currentFrameCount;
	int phase = floor(timeTicks / timeSpan * currentFrameCount);
	for(int i = 0;i < animationIndex;i++) {
		buffer = buffer + animationFrameCount[i] * frameWidth;
	}
	if(currentZombie->index ==0)
		Engine::LOG(Engine::INFO) << "buffer" << buffer;
	//if(!FinalAnimation && !RageAnimation)
		Position = currentZombie->Position;

	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer +phase * frameWidth, 0, frameWidth, frameHeight);
	if(currentZombie->index ==0)
		Engine::LOG(Engine::INFO) << "pahse" << phase;
	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
}

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
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
	timeSpan = 1.5;

}

void ZombieAnimation::Update(float deltaTime) {
	currentZombie = getPlayScene()->allZombies[index];
	if (currentZombie->animationIndex == -1) {
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
		return;
	}
	int animationIndex = 0;
	int buffer = 0;


	animationIndex = currentZombie->animationIndex;
	currentFrameCount = currentZombie->animationFrameCount[animationIndex];
	for(int i = 0;i < animationIndex;i++) {
		buffer += currentZombie->animationFrameCount[i] * currentZombie->frameWidth;
	}

	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		timeTicks = 0;
	}

	int phase = floor(timeTicks / timeSpan * currentFrameCount);

	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), buffer + phase * currentZombie->frameWidth, 0, currentZombie->frameWidth, currentZombie->frameHeight);
	bmp.reset(subBitmap, al_destroy_bitmap);
	Sprite::Update(deltaTime);
}

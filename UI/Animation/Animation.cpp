#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include "Animation.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Resources.hpp"
#include "Plant/Plant.hpp"
#include "Scene/PlayScene.hpp"

const int FRAME_WIDTH = 70; // Width of each frame in the sprite sheet
const int FRAME_HEIGHT = 72; // Height of each frame in the sprite sheet
const int FRAME_COUNT_X = 24; // Number of frames in a row
const int FRAME_COUNT_Y = 1; // Number of frames in a column

PlayScene* Animation::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Animation::Animation(std::string name, float x, float y, int blockX, int blockY)
	: Sprite(1,"play/" + name + "_animation.png", x, y), timeTicks(0), posX(x), posY(y), blockX(blockX), blockY(blockY) {
	spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation.png");
	timeSpan = 4;
}

void Animation::Update(float deltaTime) {
	if (getPlayScene()->mapState[blockY - 1][blockX - 1] != TILE_OCCUPIED)
		getPlayScene()->EffectGroup->RemoveObject(objectIterator);
	timeTicks += deltaTime;
	if (timeTicks >= timeSpan) {
		timeTicks = 0;
	}
	int totalFrames = FRAME_COUNT_X * FRAME_COUNT_Y;
	int phase = floor(timeTicks / timeSpan * totalFrames);

	ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(spriteSheet.get(), phase * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT);
	bmp.reset(subBitmap, al_destroy_bitmap);

	Sprite::Update(deltaTime);
}

#ifndef BULLET_HPP
#define BULLET_HPP
#include "Engine/Sprite.hpp"

class Zombie;
class PlayScene;
class Plant;
namespace Engine {
	struct Point;
}  // namespace Engine

enum class BulletType {
	BASICPEA, SNOWPEA, MOWER, BOWLING_BALL, BOMB_BOWLING_BALL
};

class Bullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	BulletType bulletType;
	PlayScene* getPlayScene();
	virtual void OnExplode(Zombie* enemy);
public:
	Zombie* Target = nullptr;
	Engine::Point forwardDirection = Engine::Point(1, 0);
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position);
	explicit Bullet(std::string name, int totalFrameCount, int frameWidth, int frameHeight, float speed, float damage, Engine::Point position);
	void Update(float deltaTime) override;
	// Animation
	std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
	int frameWidth;
	int frameHeight;
	int totalFrameCount;
	float timeTicks = 0;
	float timeSpan = 1.5;
};
#endif // BULLET_HPP

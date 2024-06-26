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
	Plant* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Zombie* enemy);
public:
	Zombie* Target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
	explicit Bullet(int index,int totalFrameCount,int frameWidth,int frameHeight,std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
	void Update(float deltaTime) override;
	int index = 0;
	int frameWidth;
	int frameHeight;
	int totalFrameCount;
};
#endif // BULLET_HPP

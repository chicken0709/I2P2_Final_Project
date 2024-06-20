#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Engine/Sprite.hpp"

class Zombie;
class PlayScene;
class Plant;
namespace Engine {
struct Point;
}  // namespace Engine
enum class BulletType {
	PEA, MOWER
};
class Bullet : public Engine::Sprite {
protected:
	float speed;
	float damage;
	BulletType bulletType = BulletType::PEA;
	Plant* parent;
	PlayScene* getPlayScene();
	virtual void OnExplode(Zombie* enemy);
public:
	Zombie* Target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
	void Update(float deltaTime) override;
};
#endif // BULLET_HPP

#ifndef LASERBULLET_HPP
#define LASERBULLET_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
struct Point;
}  // namespace Engine

class LaserBullet : public Bullet {
public:
	explicit LaserBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
	void OnExplode(Zombie* enemy) override;
};
#endif // LASERBULLET_HPP

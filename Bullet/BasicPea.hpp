#ifndef FIREBULLET_HPP
#define FIREBULLET_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
struct Point;
}  // namespace Engine

class BasicPea : public Bullet {
public:
	explicit BasicPea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
	void OnExplode(Zombie* enemy) override;
};
#endif // FIREBULLET_HPP

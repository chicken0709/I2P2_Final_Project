#ifndef MOWER_HPP
#define MOWER_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
struct Point;
}  // namespace Engine

class Mower : public Bullet {
public:
	explicit Mower(Engine::Point position, Engine::Point forwardDirection, float rotation);
	void OnExplode(Zombie* enemy) override;
};
#endif // MOWER_HPP

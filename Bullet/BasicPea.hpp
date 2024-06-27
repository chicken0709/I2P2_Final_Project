#ifndef BASICPEA_HPP
#define BASICPEA_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
struct Point;
}  // namespace Engine

class BasicPea : public Bullet {
public:
	explicit BasicPea(Engine::Point position);
	void OnExplode(Zombie* enemy) override;
};
#endif // BASICPEA_HPP

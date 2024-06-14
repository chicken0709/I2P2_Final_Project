#ifndef TANKENEMY_HPP
#define TANKENEMY_HPP
#include "Zombie.hpp"
#include "Engine/Sprite.hpp"

class TankEnemy : public Zombie {
private:
	Sprite head;
	float targetRotation;
public:
	TankEnemy(int x, int y);
	void Draw() const override;
	void Update(float deltaTime) override;
};
#endif // TANKENEMY_HPP

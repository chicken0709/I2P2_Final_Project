#ifndef MISSILETURRET_HPP
#define MISSILETURRET_HPP
#include "Plant.hpp"

class MissileTurret: public Plant {
public:
	static const int Price;
    MissileTurret(float x, float y);
    void CreatePea() override;
};
#endif // MISSILETURRET_HPP

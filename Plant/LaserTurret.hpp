#ifndef LASERTURRET_HPP
#define LASERTURRET_HPP
#include "Plant.hpp"

class LaserTurret: public Plant {
public:
	static const int Price;
    LaserTurret(float x, float y);
    void CreatePea() override;
};
#endif // LASERTURRET_HPP

#ifndef NEWTURRET_HPP
#define NEWTURRET_HPP
#include "Plant.hpp"

class NewTurret: public Plant {
public:
	static const int Price;
    NewTurret(float x, float y);
    void CreatePea() override;
};
#endif // NEWTURRET_HPP
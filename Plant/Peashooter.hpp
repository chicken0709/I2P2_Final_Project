#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include "Plant.hpp"

class Peashooter: public Plant {
public:
	static const int Price;
    Peashooter(float x, float y);
	void CreatePea() override;
};
#endif // PEASHOOTER_HPP

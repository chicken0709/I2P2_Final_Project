#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP
#include "Plant.hpp"

class Sunflower: public Plant {
public:
	static const int Price;
    Sunflower(float x, float y);
	void CreatePea() override;
};
#endif // SUNFLOWER_HPP


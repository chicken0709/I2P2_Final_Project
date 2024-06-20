#ifndef SHOVEL_HPP
#define SHOVEL_HPP
#include "Plant.hpp"

class Shovel: public Plant {
public:
    static const int Price;
    Shovel(float x, float y);
    void CreatePea() override;
};
#endif // SHOVEL_HPP



#ifndef LAWNMOWER_HPP
#define LAWNMOWER_HPP
#include "Plant.hpp"

class LawnMower: public Plant {
public:
    LawnMower(float x, float y);
    void CreatePea() override;
};
#endif // LAWNMOWER_HPP
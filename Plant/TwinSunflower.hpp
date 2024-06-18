#ifndef TWINSUNFLOWER_HPP
#define TWINSUNFLOWER_HPP
#include "Plant.hpp"

class TwinSunflower: public Plant {
public:
    static const int Price;
    TwinSunflower(float x, float y);
    void CreatePea() override;
};
#endif // TWINSUNFLOWER_HPP


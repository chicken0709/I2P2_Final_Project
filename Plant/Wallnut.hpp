#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "Plant.hpp"

class Wallnut: public Plant {
public:
    static const int Price;
    Wallnut(float x, float y);
    void CreatePea() override;
};
#endif // WALLNUT_HPP


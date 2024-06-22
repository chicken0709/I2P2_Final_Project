#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "Plant.hpp"

class Wallnut: public Plant {
public:
    static const int Price;
    Wallnut(float x, float y);
    void CreatePea() override;
    void TakeDamage(float damage, bool shovel) override;
};
#endif // WALLNUT_HPP


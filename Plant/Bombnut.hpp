#ifndef BOMBNUT_HPP
#define BOMBNUT_HPP
#include "Plant.hpp"

class Bombnut: public Plant {
public:
    static const int Price;
    Bombnut(float x, float y);
    void CreatePea() override;
    void TakeDamage(float damage, bool shovel) override;
};
#endif // BOMBNUT_HPP


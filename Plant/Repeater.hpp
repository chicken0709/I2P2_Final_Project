#ifndef REPEATER_HPP
#define REPEATER_HPP
#include "Plant.hpp"

class Repeater: public Plant {
protected:
    int shotCycle = 0;
public:
    static const int Price;
    Repeater(float x, float y);
    void CreatePea() override;
};
#endif // REPEATER_HPP
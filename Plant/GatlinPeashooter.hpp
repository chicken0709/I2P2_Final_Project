#ifndef GATLINPEASHOOTER_HPP
#define GATLINPEASHOOTER_HPP
#include "Plant.hpp"

class GatlinPeashooter: public Plant {
protected:
    int shotCycle = 0;
public:
    static const int Price;
    GatlinPeashooter(float x, float y);
    void CreatePea() override;
};
#endif // GATLINPEASHOOTER_HPP
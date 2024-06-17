#ifndef ICEPEASHOOTER_HPP
#define ICEPEASHOOTER_HPP
#include "Plant.hpp"

class SnowPeashooter: public Plant {
public:
    static const int Price;
    SnowPeashooter(float x, float y);
    void CreatePea() override;
};
#endif // ICEPEASHOOTER_HPP


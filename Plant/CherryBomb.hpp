#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP
#include "Plant.hpp"

class CherryBomb: public Plant {
public:
    static const int Price;
    CherryBomb(float x, float y);
    void CreatePea() override;
};
#endif // CHERRYBOMB_HPP


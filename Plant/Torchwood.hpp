#ifndef TORCHWOOD_HPP
#define TORCHWOOD_HPP
#include "Plant.hpp"

class Torchwood: public Plant {
public:
    static const int Price;
    Torchwood(float x, float y);
    void CreatePea() override;
};
#endif // TORCHWOOD_HPP


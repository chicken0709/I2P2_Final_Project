#ifndef PLANT_HPP
#define PLANT_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Zombie;
class PlayScene;

class Plant: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    std::list<Plant*>::iterator lockedPlantIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreatePea() = 0;

public:
    bool Enabled = true;
    bool Preview = false;
    Zombie* Target = nullptr;
    Plant(std::string img, float x, float y, float radius, int price, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
};
#endif // PLANT_HPP
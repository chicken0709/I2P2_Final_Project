#ifndef PLANT_HPP
#define PLANT_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Zombie;
class PlayScene;

enum class PlantType {
    SUNFLOWER, PEASHOOTER, LAWNMOWER, OTHER
};

class Plant: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    int hp;
    int pos_x = 0;
    int pos_y = 0;
    PlantType plantType;
    std::list<Plant*>::iterator lockedPlantIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreatePea() = 0;

public:
    bool Enabled = true;
    bool Preview = false;
    Zombie* Target = nullptr;
    Plant(std::string img, float x, float y, int hp, int price, float coolDown, PlantType plantType);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    PlantType GetPlantType() const;
    void TakeDamage(float damage, bool shovel);
    void OnExplode();
    void SetPos(int x,int y);
};
#endif // PLANT_HPP
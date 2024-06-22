#ifndef PLANT_HPP
#define PLANT_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Zombie;
class PlayScene;

enum class PlantType {
    SUNFLOWER, PEASHOOTER, LAWNMOWER, WALLNUT, CHERRYBOMB, OTHER, NUL,
};

class Plant: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    int hp;
    int pos_x = 0;
    int pos_y = 0;
    PlantType plantType = PlantType::NUL;
    std::list<Plant*>::iterator lockedPlantIterator;
    PlayScene* getPlayScene();

    Plant(std::string img, float x, float y, int hp, int price, float coolDown, PlantType plantType, std::string name,int totalFrameCount,int frameWidth,int frameHeight,std::vector<int> animationFrameCount);

    // Reference: Design Patterns - Factory Method.
    virtual void CreatePea() = 0;

public:
    std::string name;
    bool Enabled = true;
    bool Preview = false;
    Zombie* Target = nullptr;
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    virtual void TakeDamage(float damage, bool shovel);
    void OnExplode();
    void SetPos(int x,int y);
    PlantType GetPlantType();

    int totalFrameCount;
    int frameWidth;
    int frameHeight;
    int animationIndex = 0;
    std::vector<int> animationFrameCount;
};
#endif // PLANT_HPP
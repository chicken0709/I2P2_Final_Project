#ifndef PLANT_HPP
#define PLANT_HPP
#include <list>
#include <string>

#include "Engine/Sprite.hpp"

class Zombie;
class PlayScene;

enum class PlantType {
    SUNFLOWER, PEASHOOTER, LAWNMOWER, WALLNUT, CHERRYBOMB, OTHER
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
    PlayScene* getPlayScene();
    Plant(std::string name, std::string img, float x, float y, int hp, int price, float coolDown);
    Plant(std::string name, int totalFrameCount, int frameWidth, int frameHeight, std::vector<int> animationFrameCount, float x, float y, int hp, int price, float coolDown);
    virtual void CreatePea() = 0;
    // Animation
    std::shared_ptr<ALLEGRO_BITMAP> spriteSheet;
    int frameWidth;
    int frameHeight;
    int currentFrameCount;
    int totalFrameCount;
    int animationIndex = 0;
    std::vector<int> animationFrameCount;
    float timeTicks = 0;
    float timeSpan = 1.5;
public:
    std::string name;
    bool Enabled = true;
    bool Preview = false;
    Zombie* Target = nullptr;
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
    virtual void TakeDamage(float damage, bool shovel);
    void SetPos(int x,int y);
    PlantType GetPlantType();
};
#endif // PLANT_HPP
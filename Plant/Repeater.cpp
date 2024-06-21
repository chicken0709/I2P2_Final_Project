#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "Repeater.hpp"
#include "Scene/PlayScene.hpp"

const int Repeater::Price = 200;

Repeater::Repeater(float x, float y) :
        Plant("play/repeater.png", x, y, 10, Price, 0.3, PlantType::PEASHOOTER) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Repeater::CreatePea() {
    if(shotCycle == 2) {
        coolDown = 0.3;
        shotCycle = 0;
        return;
    } else if(shotCycle == 1) {
        coolDown = 0.9;
        shotCycle++;
    } else {
        coolDown = 0.3;
        shotCycle++;
    }
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
    Engine::Point normalized = Engine::Point(50, -35);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new BasicPea(Position + normalized, diff, 0, this));
    AudioHelper::PlayAudio("throw.mp3");
}

#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "GatlinPeashooter.hpp"
#include "Scene/PlayScene.hpp"

const int GatlinPeashooter::Price = 450;

GatlinPeashooter::GatlinPeashooter(float x, float y) :
        Plant("play/gatlin_peashooter.png", x, y,10, Price, 0.3, PlantType::PEASHOOTER,"gatlinpeashooter",13,88,84,{13}) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void GatlinPeashooter::CreatePea() {
    if(shotCycle == 4) {
        coolDown = 0.3;
        shotCycle = 0;
        return;
    } else if(shotCycle == 3) {
        coolDown = 0.6;
        shotCycle++;
    } else {
        coolDown = 0.3;
        shotCycle++;
    }
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
    Engine::Point normalized = Engine::Point(65, -35);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new BasicPea(Position + normalized, diff, 0));
    AudioHelper::PlayAudio("throw.mp3");
}
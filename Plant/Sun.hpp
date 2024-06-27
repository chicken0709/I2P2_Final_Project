#ifndef SUN_HPP
#define SUN_HPP

#include "Engine/Sprite.hpp"

class PlayScene;
class Plant;
namespace Engine {
    struct Point;
}  // namespace Engine

class Sun : public Engine::Sprite {
protected:
    PlayScene* getPlayScene();
    bool mouseIn = false;
public:
    explicit Sun(std::string img, Engine::Point position);
    void Update(float deltaTime) override;
};
#endif // SUN_HPP


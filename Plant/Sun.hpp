#ifndef SUN_HPP
#define SUN_HPP
#include <string>

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
    explicit Sun(std::string img, Engine::Point position, Plant* parent);
    void Update(float deltaTime) override;
};
#endif // SUN_HPP


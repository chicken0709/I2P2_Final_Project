#ifndef STARTSCENE_HPP
#define STARTSCENE_HPP
#include <allegro5/allegro_audio.h>

#include "Engine/IScene.hpp"

extern std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

class StartScene final : public Engine::IScene {
public:
    explicit StartScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
};
#endif // STARTSCENE_HPP

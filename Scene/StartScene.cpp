#include <functional>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"

#include "StartScene.hpp"
#include "UI/ImageButton.hpp"
#include "UI/Label.hpp"

std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

void StartScene::Initialize() {
    AddNewObject(new Engine::Image("start/start_scene_background.jpg", 0, 0, 1600, 900));

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("start/button_background.png", "start/button_background.png", 536, 730 , 580, 50);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Tap to Start", "komika.ttf", 28, 836, 755, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("theme.mp3", true, AudioHelper::BGMVolume);
}

void StartScene::Terminate() {
    IScene::Terminate();
}

void StartScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("menu");
    AudioHelper::PlayAudio("gravebutton.ogg");
}

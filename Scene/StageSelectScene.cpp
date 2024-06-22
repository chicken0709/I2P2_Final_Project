#include <functional>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "StageSelectScene.hpp"

void StageSelectScene::Initialize() {
    AddNewObject(new Engine::Image("play/menu_background.jpg", 0, 0, 1600, 900));
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("play/button_adventure_mode.png", "play/button_adventure_mode.png", 390, 460, 177, 48);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("ADVENTURE", "komika.ttf", 36, 480, 480, 0, 0, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("play/button_bowling_mode.png", "play/button_bowling_mode.png", 410, 590, 188, 32);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("BOWLING", "komika.ttf", 36, 500, 605, 0, 0, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("play/button_settings.png", "play/button_settings.png", 680, 515, 125, 47);
    btn->SetOnClickCallback(std::bind(&StageSelectScene::SettingsOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("SETTINGS", "komika.ttf", 28, 745, 532.5, 0, 0, 0, 255, 0.5, 0.5));
}
void StageSelectScene::Terminate() {
	IScene::Terminate();
}
void StageSelectScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("play");
    AudioHelper::PlayAudio("gravebutton.ogg");
}
void StageSelectScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
    AudioHelper::PlayAudio("gravebutton.ogg");
}

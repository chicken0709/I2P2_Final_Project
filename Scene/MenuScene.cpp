#include <functional>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "MenuScene.hpp"
#include "StartScene.hpp"
#include "UI/Component/Slider.hpp"

void MenuScene::Initialize() {
    AddNewObject(new Engine::Image("menu/menu_background.jpg", 0, 0, 1600, 900));
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("menu/button_adventure_mode.png", "menu/button_adventure_mode.png", 390, 460, 177, 48);
    btn->SetOnClickCallback(std::bind(&MenuScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("ADVENTURE", "komika.ttf", 36, 480, 480, 0, 0, 0, 255, 0.5, 0.5));
    btn = new Engine::ImageButton("menu/button_bowling_mode.png", "menu/button_bowling_mode.png", 410, 590, 188, 32);
    btn->SetOnClickCallback(std::bind(&MenuScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("BOWLING", "komika.ttf", 36, 500, 605, 0, 0, 0, 255, 0.5, 0.5));

    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(125, 105, 190, 4);
    sliderBGM->SetOnValueChangedCallback(
            std::bind(&MenuScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(
            new Engine::Label("BGM: ", "komika.ttf", 28, 80, 100, 0, 0, 0, 255, 0.5,
                              0.5));
    sliderSFX = new Slider(125, 155, 190, 4);
    sliderSFX->SetOnValueChangedCallback(
            std::bind(&MenuScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(
            new Engine::Label("SFX: ", "komika.ttf", 28, 80, 150, 0, 0, 0, 255, 0.5,
                              0.5));
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}
void MenuScene::Terminate() {
	IScene::Terminate();
}
void MenuScene::PlayOnClick(int stage) {
    PlayScene* scene = dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("play");
    AudioHelper::PlayAudio("gravebutton.ogg");
}
void MenuScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}

void MenuScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}

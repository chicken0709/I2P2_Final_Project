#include <allegro5/allegro.h>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include "Plant/PlantButton.hpp"
#include "Plant/Sunflower.hpp"
#include "Plant/TwinSunflower.hpp"
#include "Plant/Peashooter.hpp"
#include "Plant/Repeater.hpp"
#include "Plant/SnowPeashooter.hpp"
#include "Plant/GatlinPeashooter.hpp"
#include "Plant/Wallnut.hpp"
#include "PlayScene.hpp"

#include "Bullet/Mower.hpp"
#include "Zombie/BasicZombie.hpp"

bool PlayScene::DebugMode = false;
const int PlayScene::MapWidth = 9, PlayScene::MapHeight = 5;
const int PlayScene::BlockSize = 150;
const int PlantButtonImageSize = 70;
const int PlantButtonImageDiffX = 5;
const int PlantButtonImageDiffY = 27;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(MapWidth + 2, 2);
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point((MapWidth + 1) * BlockSize, MapHeight * BlockSize);
}

void PlayScene::Initialize() {
	mapState.clear();
	ticks = 0;
	for(int i = 0;i < 5;i++)
		mower_available[i] = true;
	lives = 100;
	money = 15000; // change to 50 when done
	SpeedMult = 1;
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());
	AddNewObject(TowerGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
    TileMapGroup->AddNewObject(new Engine::Image("play/yard2.jpg", 0, 0, 1600, 900));
	ReadMap();
	ReadEnemyWave();
	//mapDistance = CalculateDistance();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
    mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	lawn = std::vector<std::vector<Plant*>>(MapHeight, std::vector<Plant*>(MapWidth));
	// Start BGM.
	bgmId = AudioHelper::PlayBGM("play.mp3");
}

void PlayScene::Terminate() {
	AudioHelper::StopBGM(bgmId);
	IScene::Terminate();
}

void PlayScene::Update(float deltaTime) {
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
    bool win = false;
	for (int i = 0; i < SpeedMult; i++) {
		IScene::Update(deltaTime);
		// Check if we should create new enemy.
		ticks += deltaTime;
		if (enemyWaveData.empty()) {
			if (EnemyGroup->GetObjects().empty()) {
                if(!win) {
                    win = !win;
                    std::ofstream out;
                    out.open("Resource/scoreboard.txt", std::ios::app);
                    std::string str = "player2 " + std::to_string(PlayScene::lives);
                    out << str;
                }
				Engine::GameEngine::GetInstance().ChangeScene("win");
			}
			continue;
		}
		auto current = enemyWaveData.front();
		if (ticks < current.second)
			continue;
		ticks -= current.second;
		enemyWaveData.pop_front();
		const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize, SpawnGridPoint.y * BlockSize + 10);
		Zombie* enemy;
		switch (current.first) {
		case 1:
			EnemyGroup->AddNewObject(enemy = new BasicZombie(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 2:
			EnemyGroup->AddNewObject(enemy = new BasicZombie(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 3:
			EnemyGroup->AddNewObject(enemy = new BasicZombie(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 4:
			EnemyGroup->AddNewObject(enemy = new BasicZombie(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		default:
			continue;
		}
		//enemy->UpdatePath(mapDistance);
		// Compensate the time lost.
		enemy->Update(ticks);
	}
	if (preview) {
		preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
		// To keep responding when paused.
		preview->Update(deltaTime);
	}
}

void PlayScene::Draw() const {
	IScene::Draw();
	if (DebugMode) {
		// Draw reverse BFS distance on all reachable blocks.
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
                std::string str;
                if(mapState[i][j] == TILE_OCCUPIED) {
                    str = std::string("occupied");
                } else {
                    str = std::string("empty");
                }
                Engine::Label label(str, "komika.ttf", 12, (j + 0.5) * BlockSize + BlockSize, (i + 0.5) * BlockSize + BlockSize);
                label.Anchor = Engine::Point(0.5, 0.5);
                label.Draw();
			}
		}
	}
}

void PlayScene::OnMouseDown(int button, int mx, int my) {
	if ((button & 1) && !imgTarget->Visible && preview) {
		// Cancel turret construct.
		UIGroup->RemoveObject(preview->GetObjectIterator());
		preview = nullptr;
	}
	IScene::OnMouseDown(button, mx, my);
}

void PlayScene::OnMouseMove(int mx, int my) {
	IScene::OnMouseMove(mx, my);
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (!preview || x < 1 || x >= MapWidth + 1 || y < 1 || y >= MapHeight + 1) {
		imgTarget->Visible = false;
		return;
	}
	imgTarget->Visible = true;
	imgTarget->Position.x = x * BlockSize;
	imgTarget->Position.y = y * BlockSize - 35;
}

void PlayScene::OnMouseUp(int button, int mx, int my) {
	IScene::OnMouseUp(button, mx, my);
	if (!imgTarget->Visible)
		return;
	const int x = mx / BlockSize;
	const int y = my / BlockSize;
	if (button & 1) {
        if(x <= 0 || y <= 0) return;
		if (mapState[y - 1][x - 1] != TILE_OCCUPIED) {
			if (!preview)
				return;
            // Plant sound
            AudioHelper::PlayAudio("plant.ogg");
			// Purchase.
			EarnMoney(-preview->GetPrice());
			// Remove Preview.
			preview->GetObjectIterator()->first = false;
			UIGroup->RemoveObject(preview->GetObjectIterator());
			// Construct real turret.
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2 - 35;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 255);
			TowerGroup->AddNewObject(preview);
			// To keep responding when paused.
			preview->Update(0);
			// Remove Preview.
			lawn[y - 1][x - 1] = preview;
			preview->SetPos(y - 1,x - 1);
			preview = nullptr;

			mapState[y - 1][x - 1] = TILE_OCCUPIED;
			OnMouseMove(mx, my);
		}
	}
}

void PlayScene::OnKeyDown(int keyCode) {
	IScene::OnKeyDown(keyCode);
	if (keyCode == ALLEGRO_KEY_TAB) {
		DebugMode = !DebugMode;
	}
	else if (keyCode == ALLEGRO_KEY_Q) {
		// Hotkey for Peashooter.
		UIBtnClicked(0);
	}
	else if (keyCode == ALLEGRO_KEY_W) {
		// Hotkey for LaserTurret.
		UIBtnClicked(1);
	}
	else if (keyCode == ALLEGRO_KEY_E) {
		// Hotkey for MissileTurret.
		UIBtnClicked(2);
	}
	else if(keyCode == ALLEGRO_KEY_R) {
		UIBtnClicked(3);
	}
	else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
		// Hotkey for Speed up.
		SpeedMult = keyCode - ALLEGRO_KEY_0;
	}
}

void PlayScene::ReachHouse(int row) {
	if(mower_available[row]) {
		Engine::Point pos(row, 0);
		CreateLawnMower(pos);
		mower_available[row] = false;
	}
	else {
		Engine::GameEngine::GetInstance().ChangeScene("lose");
	}

	//Original Code
	/*
	lives--;
	if (lives <= 0) {
		Engine::GameEngine::GetInstance().ChangeScene("lose");
	}
	*/
}

int PlayScene::GetMoney() const {
	return money;
}

void PlayScene::EarnMoney(int money) {
	this->money += money;
	UIMoney->Text = std::to_string(this->money);
}

void PlayScene::ReadMap() {
	// Store map in 2d array.
	mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
}

void PlayScene::ReadEnemyWave() {
    // TODO: [HACKATHON-3-BUG] (3/5): Trace the code to know how the enemies are created.
    // TODO: [HACKATHON-3-BUG] (3/5): There is a bug in these files, which let the game only spawn the first enemy, try to fix it.
    std::string filename = std::string("Resource/enemy") + std::to_string(MapId) + ".txt";
	// Read enemy file.
	float type, wait, repeat;
	enemyWaveData.clear();
	std::ifstream fin(filename);
	while (fin >> type && fin >> wait && fin >> repeat) {
		for (int i = 0; i < repeat; i++)
			enemyWaveData.emplace_back(type, wait);
	}
	fin.close();
}

void PlayScene::ConstructUI() {
	// Background
    UIGroup->AddNewObject(new Engine::Image("play/sun_counter.png", 100, 0, 124, 136));
	UIGroup->AddNewObject(new Engine::Image("play/plant_select.png", 224, 0, 792, 136));
	// Text
	UIGroup->AddNewObject(UIMoney = new Engine::Label(std::to_string(money), "komika.ttf", 20, 132.5, 98.5));
	PlantButton* btn;
	// Button 1 Sunflower
	btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 229, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/sunflower.png", 239 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
		, 229, 8, Sunflower::Price);
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(Sunflower::Price), "komika.ttf", 16, 264, 92.5));
	// Button 2 TwinSunflower
	btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 324, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/twin_sunflower.png", 334 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
		, 324, 8, TwinSunflower::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(TwinSunflower::Price), "komika.ttf", 16, 354, 92.5));
	// Button 3 Peashooter
	btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 419, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/peashooter.png", 429 + PlantButtonImageDiffX,  PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
		, 419, 8, Peashooter::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(Peashooter::Price), "komika.ttf", 16, 449, 92.5));
	// Button 4 Repeater
	btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 514, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/repeater.png", 524 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
            , 514, 8, Repeater::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(Repeater::Price), "komika.ttf", 16, 544, 92.5));
    // Button 5 SnowPeashooter
    btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 609, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/snow_peashooter.png", 619 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
            , 609, 8, SnowPeashooter::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 4));
    UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(SnowPeashooter::Price), "komika.ttf", 16, 639, 92.5));
    // Button 6 GatlinPeashooter
    btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 704, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/gatlin_peashooter.png", 714 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
            , 704, 8, GatlinPeashooter::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 5));
    UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(GatlinPeashooter::Price), "komika.ttf", 16, 734, 92.5));
    // Button 7 Wallnut
    btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 799, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/wallnut.png", 809 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
            , 799, 8, Wallnut::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 6));
    UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(Wallnut::Price), "komika.ttf", 16, 834, 92.5));
    // Button 8 Chili
    btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 894, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/chili.png", 904 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
            , 894, 8, Peashooter::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
    UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(SnowPeashooter::Price), "komika.ttf", 16, 924, 92.5));
    // Button 8 shovel
    btn = new PlantButton("play/shovel_button.png", "play/shovel_button.png",
                          Engine::Sprite("play/shovel_button.png", 1030, 0, 0, 0, 0, 0),
                          Engine::Sprite("play/shovel.png", 1036, 6, 100, 104, 0, 0)
            , 1030, 0, SnowPeashooter::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
    UIGroup->AddNewControlObject(btn);
}

void PlayScene::UIBtnClicked(int id) {
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
	if (id == 0 && money >= Sunflower::Price)
		preview = new Sunflower(0, 0);
	else if (id == 1 && money >= TwinSunflower::Price)
		preview = new TwinSunflower(0, 0);
	else if (id == 2 && money >= Peashooter::Price)
		preview = new Peashooter(0, 0);
	else if (id == 3 && money >= Repeater::Price)
		preview = new Repeater(0, 0);
    else if (id == 4 && money >= SnowPeashooter::Price)
        preview = new SnowPeashooter(0, 0);
    else if (id == 5 && money >= GatlinPeashooter::Price)
        preview = new GatlinPeashooter(0, 0);
    else if (id == 6 && money >= Wallnut::Price)
        preview = new Wallnut(0, 0);
    //else if (id == 8)

	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}





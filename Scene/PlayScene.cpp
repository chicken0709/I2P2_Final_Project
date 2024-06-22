#include <allegro5/allegro.h>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <random>

#include "Engine/AudioHelper.hpp"
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
#include "Plant/CherryBomb.hpp"
#include "Plant/Shovel.hpp"
#include "Plant/LawnMower.hpp"
#include "PlayScene.hpp"
#include "UI/Animation/Animation.hpp"
#include "Zombie/Zombie.hpp"
#include "Zombie/BasicZombie.hpp"
#include "Zombie/ConeZombie.hpp"
#include "Zombie/BucketZombie.hpp"
#include "Zombie/FlagZombie.hpp"
#include "Zombie/FootballZombie.hpp"
#include "Zombie/NewspaperZombie.hpp"

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
	lives = 100;
	money = 15000; // change to 100 when done
	SpeedMult = 1;
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());
	AddNewObject(PlantGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
    TileMapGroup->AddNewObject(new Engine::Image("play/yard2.jpg", 0, 0, 1600, 900));
	ReadMap();
	ReadEnemyWave();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
    mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
	lawn = std::vector<std::vector<Plant*>>(MapHeight, std::vector<Plant*>(MapWidth));
	// Start BGM.
	bgmId = AudioHelper::PlayBGM("play.mp3");
    shovelClicked = false;
	win = false;
	lose = false;
	buttonAdded = false;
	win_bgm_delay = 4.5;
	lose_bgm_delay = 10.5;

	//generate lawn mowers
	for(int i = 1;i <= MapHeight;i++) {
		int x = 0;
		int y = i;
		preview = new LawnMower(0, 0);
		// Construct real turret.
		preview->Position.x = x * BlockSize + BlockSize / 2 + 25;
		preview->Position.y = y * BlockSize + BlockSize / 2;
		preview->Enabled = true;
		preview->Preview = false;
		preview->Tint = al_map_rgba(255, 255, 255, 255);
		PlantGroup->AddNewObject(preview);
		// To keep responding when paused.
		preview->Update(0);
		// Remove Preview.
		mower_available[i - 1] = preview;
		preview = nullptr;

	}
}

void PlayScene::Terminate() {
	AudioHelper::StopBGM(bgmId);
	IScene::Terminate();
}

void PlayScene::Update(float deltaTime) {
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
	if (lose) {
		lose_bgm_delay -= deltaTime;
		if(lose_bgm_delay < 0 && buttonAdded == false) {
			buttonAdded = true;
			Engine::ImageButton* btn;
			btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", 800 - 200, 450 * 7 / 4 - 50, 400, 100);
			btn->SetOnClickCallback(std::bind(&PlayScene::BackOnClick, this, 2));
			AddNewControlObject(btn);
			AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, 800, 450 * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
		}
	}
	if (win) {
		win_bgm_delay -= deltaTime;
		if(win_bgm_delay < 0 && buttonAdded == false) {
			buttonAdded = true;
			Engine::ImageButton* btn;
			btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", 800 - 200, 450 * 7 / 4 - 50, 400, 100);
			btn->SetOnClickCallback(std::bind(&PlayScene::BackOnClick, this, 2));
			AddNewControlObject(btn);
			AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, 800, 450 * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
		}
	}
	if (lose) return;
	for (int i = 0; i < SpeedMult; i++) {
		IScene::Update(deltaTime);
		// Check if we should create new enemy.
		ticks += deltaTime;
		if (zombieWaveData.empty()) {
			if (EnemyGroup->GetObjects().empty()) {
				if(win == false) {
					win = true;
					AudioHelper::StopBGM(bgmId);
					AudioHelper::PlayAudio("winmusic.ogg");
				}
			}
			continue;
		}
		auto current = zombieWaveData.front();
		if (ticks < current.wait)
			continue;
		ticks -= current.wait;
		zombieWaveData.pop_front();
		const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize, current.lane * BlockSize);
		Zombie* enemy;
		switch (current.type) {
			case -2:
				// Start empty time
				continue;
			case -1:
				// First zombie
				AudioHelper::PlayAudio("siren.ogg");
				continue;
			case 0:
				// Huge wave
				AudioHelper::PlayAudio("hugewave.ogg");
				continue;
			case 1:
				// Basic zombie
				EnemyGroup->AddNewObject(enemy = new BasicZombie(SpawnCoordinate.x, SpawnCoordinate.y));
				break;
			case 2:
				// Cone zombie
				EnemyGroup->AddNewObject(enemy = new ConeZombie(SpawnCoordinate.x, SpawnCoordinate.y));
				break;
			case 3:
				// Bucket zombie
				EnemyGroup->AddNewObject(enemy = new BucketZombie(SpawnCoordinate.x, SpawnCoordinate.y));
				break;
			case 4:
				// Football zombie
				EnemyGroup->AddNewObject(enemy = new FootballZombie(SpawnCoordinate.x, SpawnCoordinate.y));
				break;
			case 5:
				// Newspaper zombie
				EnemyGroup->AddNewObject(enemy = new NewspaperZombie(SpawnCoordinate.x, SpawnCoordinate.y));
				break;
			case 6:
				// Flag zombie
				EnemyGroup->AddNewObject(enemy = new FlagZombie(SpawnCoordinate.x, SpawnCoordinate.y));
				break;
			default:
				continue;
		}
		// Compensate the time lost.
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> id(1, 5);
		AudioHelper::PlayAudio("groan" + std::to_string(id(rng)) + ".ogg");
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
    if(shovelClicked) {
        if (mapState[y - 1][x - 1] == TILE_OCCUPIED) {
            Plant *plant = lawn[y - 1][x - 1];
            plant->TakeDamage(INT16_MAX, true);
            mapState[y - 1][x - 1] = TILE_EMPTY;
            EarnMoney(plant->GetPrice());
            AudioHelper::PlayAudio("shovel.ogg");
        }
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
        shovelClicked = false;
        return;
    }
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
			// Construct real plant
			preview->Position.x = x * BlockSize + BlockSize / 2;
			preview->Position.y = y * BlockSize + BlockSize / 2 - 35;
			preview->Enabled = true;
			preview->Preview = false;
			preview->Tint = al_map_rgba(255, 255, 255, 0);
			PlantGroup->AddNewObject(preview);

			//Add Animation
			EffectGroup->AddNewObject(new Animation(preview->GetName(),preview->frameCount,preview->frameWidth,preview->frameHeight,1,x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2 - 35,x,y));

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
	else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
		// Hotkey for Speed up.
		SpeedMult = keyCode - ALLEGRO_KEY_0;
	}
}

void PlayScene::ReachHouse() {
	if (lose == false) {
		AudioHelper::StopBGM(bgmId);
		AudioHelper::PlayAudio("losemusic.ogg");
		lose = true;
	}
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
    std::string filename = std::string("Resource/zombie.txt");
	// Read enemy file.
	float type, wait, repeat, lane;
	zombieWaveData.clear();
	std::ifstream fin(filename);
	while (fin >> type && fin >> wait && fin >> repeat && fin >> lane) {
		for (int i = 0; i < repeat; i++)
			zombieWaveData.emplace_back(type, wait, lane);
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
    // Button 8 cherrybomb
    btn = new PlantButton("play/plant_button_background.png", "play/plant_button_background.png",
                          Engine::Sprite("play/plant_button_background.png", 894, 8, 0, 0, 0, 0),
                          Engine::Sprite("play/cherrybomb.png", 904 + PlantButtonImageDiffX, PlantButtonImageDiffY, PlantButtonImageSize, PlantButtonImageSize, 0, 0)
            , 894, 8, CherryBomb::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 7));
    UIGroup->AddNewControlObject(btn);
    UIGroup->AddNewObject(new Engine::Label(std::to_string(CherryBomb::Price), "komika.ttf", 16, 924, 92.5));
    // Button 9 shovel
    btn = new PlantButton("play/shovel_button.png", "play/shovel_button.png",
                          Engine::Sprite(0,0,"play/shovel_button.png", 1030, 0, 0, 0, 0, 0,0,0),
                          Engine::Sprite("play/shovel.png", 1036, 6, 100, 104, 0, 0)
            , 1030, 0, SnowPeashooter::Price);
    btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 8));
    UIGroup->AddNewControlObject(btn);
}

void PlayScene::UIBtnClicked(int id) {
	if (lose) return;
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
    else if (id == 7 && money >= CherryBomb::Price)
        preview = new CherryBomb(0, 0);
    else if (id == 8) {
        preview = new Shovel(0, 0);
        shovelClicked = true;
    }

	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

void PlayScene::BackOnClick(int stage) {
	Engine::GameEngine::GetInstance().ChangeScene("start");
}




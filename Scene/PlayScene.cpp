#include <allegro5/allegro.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "UI/Component/Label.hpp"
#include "Plant/LaserTurret.hpp"
#include "Plant/Peashooter.hpp"
#include "Plant/MissileTurret.hpp"
#include "Plant/NewTurret.hpp"
#include "Plant/PlantButton.hpp"
#include "UI/Animation/Plane.hpp"
#include "Zombie/PlaneEnemy.hpp"
#include "PlayScene.hpp"
#include "Engine/Resources.hpp"
#include "Zombie/SoldierEnemy.hpp"
#include "Zombie/TankEnemy.hpp"
#include "Zombie/TankEnemy2.hpp"

bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 9, PlayScene::MapHeight = 5;
const int PlayScene::BlockSize = 150;
const int MapDiffX = 150;
const int MapDiffY = 150;
const float PlayScene::DangerTime = 7.61;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth - 1, MapHeight - 1);
const std::vector<int> PlayScene::code = { ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN,
									ALLEGRO_KEY_LEFT, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_RIGHT,
									ALLEGRO_KEY_B, ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, ALLEGRO_KEY_ENTER };
Engine::Point PlayScene::GetClientSize() {
	return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
	mapState.clear();
	keyStrokes.clear();
	ticks = 0;
	deathCountDown = -1;
	lives = 100;
	money = 15000;
	SpeedMult = 1;
	// Add groups from bottom to top.
	AddNewObject(TileMapGroup = new Group());
	AddNewObject(GroundEffectGroup = new Group());
	AddNewObject(DebugIndicatorGroup = new Group());
	AddNewObject(TowerGroup = new Group());
	AddNewObject(EnemyGroup = new Group());
	AddNewObject(BulletGroup = new Group());
	AddNewObject(EffectGroup = new Group());
	// Should support buttons.
	AddNewControlObject(UIGroup = new Group());
    TileMapGroup->AddNewObject(new Engine::Image("play/yard2.jpg", 0, 0, 1600, 900));
	ReadMap();
	ReadEnemyWave();
	mapDistance = CalculateBFSDistance();
	ConstructUI();
	imgTarget = new Engine::Image("play/target.png", 0, 0);
	imgTarget->Visible = false;
	preview = nullptr;
	UIGroup->AddNewObject(imgTarget);
	// Preload Lose Scene
	deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
	Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
	// Start BGM.
	//bgmId = AudioHelper::PlayBGM("play.ogg");
}
void PlayScene::Terminate() {
	AudioHelper::StopBGM(bgmId);
	AudioHelper::StopSample(deathBGMInstance);
	deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void PlayScene::Update(float deltaTime) {
	// If we use deltaTime directly, then we might have Bullet-through-paper problem.
	// Reference: Bullet-Through-Paper
    bool win = false;
	if (SpeedMult == 0)
		deathCountDown = -1;
	else if (deathCountDown != -1)
		SpeedMult = 1;
	// Calculate danger zone.
	std::vector<float> reachEndTimes;
	for (auto& it : EnemyGroup->GetObjects()) {
		reachEndTimes.push_back(dynamic_cast<Zombie*>(it)->reachEndTime);
	}
	// Can use Heap / Priority-Queue instead. But since we won't have too many enemies, sorting is fast enough.
	std::sort(reachEndTimes.begin(), reachEndTimes.end());
	float newDeathCountDown = -1;
	int danger = lives;
	for (auto& it : reachEndTimes) {
		if (it <= DangerTime) {
			danger--;
			if (danger <= 0) {
				// Death Countdown
				float pos = DangerTime - it;
				if (it > deathCountDown) {
					// Restart Death Count Down BGM.
					AudioHelper::StopSample(deathBGMInstance);
					if (SpeedMult != 0)
						deathBGMInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, pos);
				}
				float alpha = pos / DangerTime;
				alpha = std::max(0, std::min(255, static_cast<int>(alpha * alpha * 255)));
				dangerIndicator->Tint = al_map_rgba(255, 255, 255, alpha);
				newDeathCountDown = it;
				break;
			}
		}
	}
	deathCountDown = newDeathCountDown;
	if (SpeedMult == 0)
		AudioHelper::StopSample(deathBGMInstance);
	if (deathCountDown == -1 && lives > 0) {
		AudioHelper::StopSample(deathBGMInstance);
		dangerIndicator->Tint.a = 0;
	}
	if (SpeedMult == 0)
		deathCountDown = -1;
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
		const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPoint.x * BlockSize + BlockSize / 2 + MapDiffX, SpawnGridPoint.y * BlockSize + BlockSize / 2 + MapDiffY);
		Zombie* enemy;
		switch (current.first) {
		case 1:
			EnemyGroup->AddNewObject(enemy = new SoldierEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 2:
			EnemyGroup->AddNewObject(enemy = new PlaneEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 3:
			EnemyGroup->AddNewObject(enemy = new TankEnemy(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		case 4:
			EnemyGroup->AddNewObject(enemy = new TankEnemy2(SpawnCoordinate.x, SpawnCoordinate.y));
			break;
		// TODO: [CUSTOM-ENEMY]: You need to modify 'Resource/enemy1.txt', or 'Resource/enemy2.txt' to spawn the 4th enemy.
        //         The format is "[EnemyId] [TimeDelay] [Repeat]".
        // TODO: [CUSTOM-ENEMY]: Enable the creation of the enemy.
		default:
			continue;
		}
		enemy->UpdatePath(mapDistance);
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
				//if (mapDistance[i][j] != -1) {
					// Not elegant nor efficient, but it's quite enough for debugging.
                    std::string str;
                    if(mapState[i][j] == TILE_OCCUPIED) {
                        str = std::string("occupied");
                    } else {
                        str = std::string("empty");
                    }
					Engine::Label label(str, "pirulen.ttf", 12, (j + 0.5) * BlockSize + MapDiffX, (i + 0.5) * BlockSize + MapDiffY);
					label.Anchor = Engine::Point(0.5, 0.5);
					label.Draw();
				//}
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
	imgTarget->Position.y = y * BlockSize;
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
	else {
		keyStrokes.push_back(keyCode);
		if (keyStrokes.size() > code.size())
			keyStrokes.pop_front();
		if (keyCode == ALLEGRO_KEY_ENTER && keyStrokes.size() == code.size()) {
			auto it = keyStrokes.begin();
			for (int c : code) {
				if (!((*it == c) ||
					(c == ALLEGRO_KEYMOD_SHIFT &&
					(*it == ALLEGRO_KEY_LSHIFT || *it == ALLEGRO_KEY_RSHIFT))))
					return;
				++it;
			}
			EffectGroup->AddNewObject(new Plane());
			money += 10000;
		}
	}
	if (keyCode == ALLEGRO_KEY_Q) {
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
	// TODO: [CUSTOM-TURRET]: Make specific key to create the turret.
	else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
		// Hotkey for Speed up.
		SpeedMult = keyCode - ALLEGRO_KEY_0;
	}
}
void PlayScene::Hit() {
	lives--;
	UILives->Text = std::string("Life ") + std::to_string(lives);
	if (lives <= 0) {
		Engine::GameEngine::GetInstance().ChangeScene("lose");
	}
}
int PlayScene::GetMoney() const {
	return money;
}
void PlayScene::EarnMoney(int money) {
	this->money += money;
	UIMoney->Text = std::string("$") + std::to_string(this->money);
}
void PlayScene::ReadMap() {
	std::string filename = std::string("Resource/map") + std::to_string(MapId) + ".txt";
	// Read map file.
	char c;
	std::vector<bool> mapData;
	std::ifstream fin(filename);
	while (fin >> c) {
		switch (c) {
		case '0': mapData.push_back(false); break;
		case '1': mapData.push_back(true); break;
		case '\n':
		case '\r':
			if (static_cast<int>(mapData.size()) / MapWidth != 0)
				throw std::ios_base::failure("Map data is corrupted.");
			break;
		default: throw std::ios_base::failure("Map data is corrupted.");
		}
	}
	fin.close();
	// Validate map data.
	if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
		throw std::ios_base::failure("Map data is corrupted.");
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
	UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
	// Text
	UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
	UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 48));
	UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 88));
	PlantButton* btn;
	// Button 1
	btn = new PlantButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1294, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/peashooter.png", 1294, 136, 0, 0, 0, 0)
		, 1294, 136, Peashooter::Price);
	// Reference: Class Member Function Pointer and std::bind.
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 0));
	UIGroup->AddNewControlObject(btn);
	// Button 2
	btn = new PlantButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1370, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-2.png", 1370, 136 - 8, 0, 0, 0, 0)
		, 1370, 136, LaserTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 1));
	UIGroup->AddNewControlObject(btn);
	// Button 3
	btn = new PlantButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1446, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-3.png", 1446, 136, 0, 0, 0, 0)
		, 1446, 136, MissileTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 2));
	UIGroup->AddNewControlObject(btn);
	// Button 4
	btn = new PlantButton("play/floor.png", "play/dirt.png",
                          Engine::Sprite("play/tower-base.png", 1522, 136, 0, 0, 0, 0),
                          Engine::Sprite("play/turret-6.png", 1522, 136, 0, 0, 0, 0)
		, 1522, 136, NewTurret::Price);
	btn->SetOnClickCallback(std::bind(&PlayScene::UIBtnClicked, this, 3));
	UIGroup->AddNewControlObject(btn);
	// TODO: [CUSTOM-TURRET]: Create a button to support constructing the turret.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int shift = 135 + 25;
	dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
	dangerIndicator->Tint.a = 0;
	UIGroup->AddNewObject(dangerIndicator);
}

void PlayScene::UIBtnClicked(int id) {
	if (preview)
		UIGroup->RemoveObject(preview->GetObjectIterator());
    // TODO: [CUSTOM-TURRET]: On callback, create the turret.
	if (id == 0 && money >= Peashooter::Price)
		preview = new Peashooter(0, 0);
	else if (id == 1 && money >= LaserTurret::Price)
		preview = new LaserTurret(0, 0);
	else if (id == 2 && money >= MissileTurret::Price)
		preview = new MissileTurret(0, 0);
	else if (id == 3 && money >= NewTurret::Price)
		preview = new NewTurret(0, 0);
	if (!preview)
		return;
	preview->Position = Engine::GameEngine::GetInstance().GetMousePosition();
	preview->Tint = al_map_rgba(255, 255, 255, 200);
	preview->Enabled = false;
	preview->Preview = true;
	UIGroup->AddNewObject(preview);
	OnMouseMove(Engine::GameEngine::GetInstance().GetMousePosition().x, Engine::GameEngine::GetInstance().GetMousePosition().y);
}

bool PlayScene::CheckSpaceValid(int x, int y) {
	if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
		return false;
	auto map00 = mapState[y][x];
	mapState[y][x] = TILE_OCCUPIED;
	std::vector<std::vector<int>> map = CalculateBFSDistance();
	mapState[y][x] = map00;
	if (map[0][0] == -1)
		return false;
	for (auto& it : EnemyGroup->GetObjects()) {
		Engine::Point pnt;
		pnt.x = floor(it->Position.x / BlockSize);
		pnt.y = floor(it->Position.y / BlockSize);
		if (pnt.x < 0) pnt.x = 0;
		if (pnt.x >= MapWidth) pnt.x = MapWidth - 1;
		if (pnt.y < 0) pnt.y = 0;
		if (pnt.y >= MapHeight) pnt.y = MapHeight - 1;
		if (map[pnt.y][pnt.x] == -1)
			return false;
	}
	// All enemy have path to exit.
	mapState[y][x] = TILE_OCCUPIED;
	mapDistance = map;
	for (auto& it : EnemyGroup->GetObjects())
		dynamic_cast<Zombie*>(it)->UpdatePath(mapDistance);
	return true;
}
std::vector<std::vector<int>> PlayScene::CalculateBFSDistance() {
	// Reverse BFS to find path.
	std::vector<std::vector<int>> map(MapHeight, std::vector<int>(std::vector<int>(MapWidth, -1)));
	std::queue<Engine::Point> que;
	// Push end point.
	// BFS from end point.
	if (mapState[MapHeight - 1][MapWidth - 1] != TILE_DIRT)
		return map;
	que.push(Engine::Point(MapWidth - 1, MapHeight - 1));
	map[MapHeight - 1][MapWidth - 1] = 0;
	while (!que.empty()) {
		Engine::Point p = que.front();
		que.pop();

		if(p.x - 1 >= 0 && map[p.y][p.x - 1] == -1 && mapState[p.y][p.x - 1] == TILE_DIRT) {
			map[p.y][p.x - 1] = 1 + map[p.y][p.x];
			que.push(Engine::Point(p.x - 1, p.y));
		}
		if(p.y - 1 >= 0 && map[p.y - 1][p.x] == -1 && mapState[p.y - 1][p.x] == TILE_DIRT) {
			map[p.y - 1][p.x] = 1 + map[p.y][p.x];
			que.push(Engine::Point(p.x, p.y - 1));
		}
		if(p.x + 1 < MapWidth && map[p.y][p.x + 1] == -1 && mapState[p.y][p.x + 1] == TILE_DIRT) {
			map[p.y][p.x + 1] = 1 + map[p.y][p.x];
			que.push(Engine::Point(p.x + 1, p.y));
		}
		if(p.y + 1 < MapHeight && map[p.y + 1][p.x] == -1 && mapState[p.y + 1][p.x] == TILE_DIRT) {
			map[p.y + 1][p.x] = 1 + map[p.y][p.x];
			que.push(Engine::Point(p.x, p.y + 1));
		}
	}
    /*for(int i = 0; i < MapHeight; i++) {
        for(int j = 0; j < MapWidth; j++) {
            map[i][j] = j + 1;
        }
    }*/
	return map;
}
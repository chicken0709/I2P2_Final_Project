#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"

enum TileType {
	TILE_EMPTY,
	TILE_OCCUPIED,
};
class Zombie;
class Plant;
class Bullet;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class ZombieWaveData {
public:
	int type;
	int wait;
	int lane;
	ZombieWaveData(int t, int w, int l): type(t), wait(w), lane(l) {}
};

class PlayScene final : public Engine::IScene {
private:
	ALLEGRO_SAMPLE_ID bgmId;
protected:
	int lives;
	int SpeedMult;
	bool win;
	bool lose;
	bool enableBack;
	float win_bgm_delay;
	float lose_bgm_delay;
public:
	Plant* mower_available[5];
    int money;
    bool shovelClicked;
	static bool DebugMode;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const Engine::Point SpawnGridPoint;
	int MapId;
	float ticks;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* BulletGroup;
	Group* PlantGroup;
	Group* EnemyGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Engine::Label* UIMoney;
	Engine::Image* imgTarget;
	Plant* preview;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	std::list<ZombieWaveData> zombieWaveData;
	// Record plants
	std::vector<std::vector<Plant*>> plant_lawn;
	// Record zombies
	std::vector<Zombie*> allZombies;
	int nextZombieIndex = 0;
	std::vector<bool>allZombies_isDestroy;
	// Record bowlingballs
	std::vector<Bullet*> allBullets;
	int nextBulletIndex = 0;
	std::vector<bool>allBullets_isDestroy;

	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	void OnMouseDown(int button, int mx, int my) override;
	void OnMouseMove(int mx, int my) override;
	void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	void ReachHouse();
	void EarnMoney(int money);
	void ReadMap();
	void ReadEnemyWave();
	void ConstructUI();
	void UIBtnClicked(int id);
	void BackOnClick(int stage);
	int GetMoney() const;
};
#endif // PLAYSCENE_HPP

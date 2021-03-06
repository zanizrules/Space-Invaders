
#ifndef __GAME_H__
#define __GAME_H__

#include <list>

#include "fmod.hpp"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class PlayerShip;
class EnemyShip;
class Bullet;
class Explosion;
class ParticleEmitter;
class PlayerMissile;
class RechargeIndicator;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	void MoveSpaceShipLeft();
	void MoveSpaceShipRight();
	void StopSpaceShip();
	void FireSpaceShipBullet();

	void SpawnEnemy(float x, float y);
	void SpawnExplosion(float x, float y);

	void CreateParticleExplosion(float x, float y, float r);

	void FirePlayerMissile(float endX, float endY);

	void GenerateStars();
	
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const int ENEMY_ROWS = 6;
	static const int SHIP_SIZE = 32;

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	PlayerShip* m_playerShip;
	ParticleEmitter* m_ParticleEmitter;
	std::list<EnemyShip*> m_enemyShips;
	std::list<Bullet*> m_playerBullets;
	std::list<Explosion*> m_explosions;

	std::list<PlayerMissile*> m_playerMissiles;
	float m_missileTimer;
	bool m_allowMissileFire;
	RechargeIndicator* m_rechargeIndicators[7];

	// FMOD
	FMOD::System* m_fmodSystem;
	FMOD::Channel* m_channel;
	FMOD::Sound* m_bulletSound;
	FMOD::Sound* m_explosionSound;
	FMOD::Sound* m_missileSound;
	FMOD::Sound* m_detonationSound;

private:
	
};

#endif // __GAME_H__

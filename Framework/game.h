
#ifndef __GAME_H__
#define __GAME_H__

#include <list>

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class PlayerShip;
class EnemyShip;
class Bullet;
class Explosion;
class ParticleEmitter;

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
	static const int ENEMY_ROWS = 4;
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

private:
	
};

#endif // __GAME_H__


// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Bullet.h"
#include "Explosion.h"
#include "ParticleEmitter.h"
#include "AlienExplosionParticle.h"
#include "PlayerBulletTrailParticle.h"
#include "SmallStarParticle.h"
#include "BigStarParticle.h"
#include "PlayerMissile.h"
#include "RechargeIndicator.h"
#include "fmod.hpp"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <ctime>

// Static Members:
Game* Game::sm_pInstance = 0;

Game& Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;

}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_missileTimer(0)
, m_allowMissileFire(true)
, m_fmodSystem(0)
{
	srand((unsigned int)time(0));
}

Game::~Game()
{
	delete m_playerShip;
	m_playerShip = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	delete m_ParticleEmitter;
	m_ParticleEmitter = 0;

	for (Explosion* explosion : m_explosions)
	{
		delete explosion;
		explosion = 0;
	}

	for (EnemyShip* enemy : m_enemyShips)
	{
		delete enemy;
		enemy = 0;
	}
	for (Bullet* bullet : m_playerBullets)
	{
		delete bullet;
		bullet = 0;
	}
	for (PlayerMissile* missile : m_playerMissiles)
	{
		delete missile;
		missile = 0;
	}
	for (int i = 0; i < 7; i++)
	{
		delete m_rechargeIndicators[i];
		m_rechargeIndicators[i] = 0;
	}

	m_bulletSound->release();
	m_explosionSound->release();
	m_missileSound->release();
	m_detonationSound->release();

	m_fmodSystem->close();
	m_fmodSystem->release();
}

bool Game::Initialise()
{
	if (m_fmodSystem == 0)
	{
		FMOD::System_Create(&m_fmodSystem);
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		m_fmodSystem->createSound("assets\\bullet.wav", FMOD_DEFAULT, 0, &m_bulletSound);
		m_fmodSystem->createSound("assets\\explosion.wav", FMOD_DEFAULT, 0, &m_explosionSound);
		m_fmodSystem->createSound("assets\\missile.wav", FMOD_DEFAULT, 0, &m_missileSound);
		m_fmodSystem->createSound("assets\\detonation.wav", FMOD_DEFAULT, 0, &m_detonationSound);
		m_channel = 0;
	}

	if (m_pBackBuffer == 0)
	{
		m_pBackBuffer = new BackBuffer();
	}

	if (!m_pBackBuffer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	if (m_pInputHandler == 0)
	{
		m_pInputHandler = new InputHandler();
	}

	if (!m_pInputHandler->Initialise(m_pBackBuffer))
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// Create the particle emitter for [explosions, bullet trails, stars]
	m_ParticleEmitter = new ParticleEmitter();

	// Load in stars
	GenerateStars();

	// Load the player ship sprite.
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	// Create the player ship instance.
	m_playerShip = new PlayerShip();
	m_playerShip->Initialise(pPlayerSprite);

	for (int i = 0; i < 7; i++)
	{
		Sprite* pRechargeSprite = m_pBackBuffer->CreateSprite("assets\\recharge.png");
		m_rechargeIndicators[i] = new RechargeIndicator();
		m_rechargeIndicators[i]->Initialise(pRechargeSprite);
		m_rechargeIndicators[i]->SetPositionY(SCREEN_HEIGHT - 25);
		m_rechargeIndicators[i]->SetPositionX((float)(10 + i * 25));
	}

	// Spawn four rows of alien enemies.
	float paddingFromEdge = (SCREEN_WIDTH / 100) * 3;
	float shipSpacing = 10;
	float y = shipSpacing;

	for (int i = 0; i < ENEMY_ROWS; i++)
	{
		float x = paddingFromEdge;
		while (x < (SCREEN_WIDTH - paddingFromEdge))
		{
			SpawnEnemy(x, y);
			x += (SHIP_SIZE + shipSpacing);
		}
		y += (SHIP_SIZE + shipSpacing);
	}

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return true;
}

bool Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}

//	SDL_Delay(1);

	return (m_looping);
}

void Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;
	m_missileTimer += deltaTime;

	// Frame Counter:
	if (m_missileTimer > 7 && !m_allowMissileFire)
	{
		m_allowMissileFire = true;
		m_missileTimer = 0;
	}
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}
	

	// Update the game world simulation:

	// Process each alien enemy in the container.
	//for (EnemyShip* enemy : m_enemyShips)
	//{
	//	enemy->Process(deltaTime);
	//}

	// Update each bullet in the container.
	for (Bullet* bullet : m_playerBullets)
	{
		bullet->Process(deltaTime);
		if ((rand() % 1000) < 100)
		{
			PlayerBulletTrailParticle* pBulletParticle = new PlayerBulletTrailParticle();
			pBulletParticle->Initialise(m_pBackBuffer, bullet->GetPositionX(), bullet->GetPositionY());
			pBulletParticle->AddVelocity(0, 9.81f);
			m_ParticleEmitter->SpawnParticle(pBulletParticle);
		}
	}
	for (PlayerMissile* missile : m_playerMissiles)
	{
		missile->Process(deltaTime);
	}

	for (Explosion* explosion : m_explosions)
	{
		explosion->Process(deltaTime);
	}

	m_pInputHandler->Process(deltaTime);

	m_ParticleEmitter->Process(deltaTime);

	// Update player...
	m_playerShip->Process(deltaTime);

	// Check for bullet vs alien enemy collisions...
	for (Bullet* bullet : m_playerBullets)
	{
		if (bullet->GetPositionY() == 0)
		{
			bullet->SetDead(true);
		}
		else
		{
			for (EnemyShip* enemy : m_enemyShips)
			{
				// If collided, destory both and spawn explosion.
				if (bullet->IsCollidingWith(enemy))
				{
					bullet->SetDead(true);
					enemy->SetDead(true);
					SpawnExplosion((enemy->GetPositionX() - 16), (enemy->GetPositionY() - 16));
					CreateParticleExplosion((enemy->GetPositionX() + 16), (enemy->GetPositionY() + 16), 32);
					break;
				}
			}
		}
	}

	// Check for missile vs alien enemy collisions...
	for (PlayerMissile* missile : m_playerMissiles)
	{
		
		if (missile->m_explode)
		{
			m_fmodSystem->playSound(m_detonationSound, 0, false, &m_channel);
			for (EnemyShip* enemy : m_enemyShips)
			{
				// If collided, destory both and spawn explosion.
				if (missile->IsCollidingWith(enemy))
				{
					enemy->SetDead(true);
					SpawnExplosion((enemy->GetPositionX() - 16), (enemy->GetPositionY() - 16));
					CreateParticleExplosion((enemy->GetPositionX() + 16), (enemy->GetPositionY() + 16), 32);
				}
			}
			missile->SetDead(true);
		}
		else if (missile->GetPositionY() == 0
			|| missile->GetPositionX() == 0
			|| missile->GetPositionX() == SCREEN_WIDTH - 16)
		{
			missile->SetDead(true);
		}
	}

	// Remove any dead bullets from the container...
	std::list<Bullet*>::iterator bulletIter = m_playerBullets.begin();
	while (bulletIter != m_playerBullets.end())
	{
		if ((*bulletIter)->IsDead())
		{
			delete *bulletIter;
			bulletIter = m_playerBullets.erase(bulletIter);
		}
		else
		{
			++bulletIter;
		}
	}

	// Remove any dead missiles from the container...
	std::list<PlayerMissile*>::iterator missileIter = m_playerMissiles.begin();
	while (missileIter != m_playerMissiles.end())
	{
		if ((*missileIter)->IsDead())
		{
			delete *missileIter;
			missileIter = m_playerMissiles.erase(missileIter);
		}
		else
		{
			++missileIter;
		}
	}

	// Remove any dead enemy aliens from the container...
	std::list<EnemyShip*>::iterator enemyIter = m_enemyShips.begin();
	while (enemyIter != m_enemyShips.end())
	{
		if ((*enemyIter)->IsDead())
		{
			delete *enemyIter;
			enemyIter = m_enemyShips.erase(enemyIter);
		}
		else
		{
			++enemyIter;
		}
	}

	// Remove any dead explosions from the container...
	std::list<Explosion*>::iterator explosionIter = m_explosions.begin();
	while (explosionIter != m_explosions.end())
	{
		if ((*explosionIter)->IsDead())
		{
			delete *explosionIter;
			explosionIter = m_explosions.erase(explosionIter);
		}
		else
		{
			++explosionIter;
		}
	}
}


void Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	// Draw missile target
	m_pInputHandler->Draw(backBuffer);

	m_ParticleEmitter->Draw(backBuffer);

	// Draw all enemy aliens in container...
	for(EnemyShip* enemy : m_enemyShips)
	{
		enemy->Draw(backBuffer);
	}

	// Draw all bullets in container...
	for (Bullet* bullet : m_playerBullets)
	{
		bullet->Draw(backBuffer);
	}

	for (PlayerMissile* missile : m_playerMissiles)
	{
		missile->Draw(backBuffer);
	}

	// Draw all explosions
	for (Explosion* explosion : m_explosions)
	{
		explosion->Draw(backBuffer);
	}

	// Draw the player ship...
	m_playerShip->Draw(backBuffer);

	if (m_allowMissileFire || m_missileTimer > 7)
	{
		m_missileTimer = 7;
	}
	for (int i = 0; i < m_missileTimer; i++)
	{
		if (i <= m_missileTimer-1)
		{
			m_rechargeIndicators[i]->Draw(backBuffer);
		}
	}
	
	backBuffer.Present();
}

void Game::Quit()
{
	m_looping = false;
}

void Game::MoveSpaceShipLeft()
{
	// Tell the player ship to move left.
	m_playerShip->SetHorizontalVelocity(-100);
}

void Game::MoveSpaceShipRight()
{
	// Tell the player ship to move right.
	m_playerShip->SetHorizontalVelocity(100);
}

void Game::StopSpaceShip()
{
	m_playerShip->SetHorizontalVelocity(0);
}

void Game::FireSpaceShipBullet()
{
	Sprite* pBulletSprite = m_pBackBuffer->CreateSprite("assets\\playerbullet.png");

	// Create a new bullet object.
	Bullet* pPlayerBullet = new Bullet();
	pPlayerBullet->Initialise(pBulletSprite);
	pPlayerBullet->SetVerticalVelocity(-400);
	pPlayerBullet->SetPosition(m_playerShip->GetPositionX(), m_playerShip->GetPositionY());

	// Add the new bullet to the bullet container.
	m_playerBullets.push_back(pPlayerBullet);
	m_fmodSystem->playSound(m_bulletSound, 0, false, &m_channel);
}

void Game::SpawnEnemy(float x, float y)
{
	Sprite* pEnemySprite = m_pBackBuffer->CreateSprite("assets\\alienenemy.png");

	// Create a new Enemy object.
	EnemyShip* pEnemyShip = new EnemyShip();
	pEnemyShip->Initialise(pEnemySprite);
	pEnemyShip->SetPosition(x, y);

	// Add the new Enemy to the enemy container.
	m_enemyShips.push_back(pEnemyShip);
}

void Game::SpawnExplosion(float x, float y)
{
	AnimatedSprite* pExplosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\explosion.png");

	Explosion* pExplosion = new Explosion();
	pExplosion->Initialise(pExplosionSprite);
	pExplosion->SetPosition(x, y);

	m_explosions.push_back(pExplosion);
	m_fmodSystem->playSound(m_explosionSound, 0, false, &m_channel);
}

void Game::CreateParticleExplosion(float x, float y, float r)
{
	for (int i = 0; i < 10; i++)
	{
		AlienExplosionParticle* pExplosionParticle = new AlienExplosionParticle();
		pExplosionParticle->Initialise(m_pBackBuffer, x, y);
		//float degrees = (360 / 10) * i; Use * M_PI) / 180 to convert to radians
		float radians = (float)(((2.0f * M_PI) / 10.0f) * i);
		pExplosionParticle->AddVelocity(r * cos(radians), r * sin(radians));

		m_ParticleEmitter->SpawnParticle(pExplosionParticle);
	}
}

void Game::FirePlayerMissile(float endX, float endY)
{
	if (m_allowMissileFire)
	{
		PlayerMissile* pPlayerMissile = new PlayerMissile(
			m_playerShip->GetPositionX(), endX,
			m_playerShip->GetPositionY(), endY);

		Sprite* pMissileSprite = m_pBackBuffer->CreateSprite("assets\\playermissile.png");

		pPlayerMissile->Initialise(pMissileSprite);
		pPlayerMissile->SetPosition(m_playerShip->GetPositionX(), m_playerShip->GetPositionY());

		m_playerMissiles.push_back(pPlayerMissile);
		m_allowMissileFire = false;
		m_missileTimer = 0;
		m_fmodSystem->playSound(m_missileSound, 0, false, &m_channel);
	}
}

void Game::GenerateStars()
{
	for (int i = 0; i < 100; i++)
	{
		SmallStarParticle* pSmallStarParticle = new SmallStarParticle();
		pSmallStarParticle->Initialise(m_pBackBuffer, (float)(rand() % SCREEN_WIDTH), (float)(rand() % SCREEN_HEIGHT));

		pSmallStarParticle->AddVelocity(0, 1.0f + rand() % 5);

		m_ParticleEmitter->SpawnParticle(pSmallStarParticle);
	}

	for (int i = 0; i < 50; i++)
	{
		BigStarParticle* pBigStarParticle = new BigStarParticle();
		pBigStarParticle->Initialise(m_pBackBuffer, (float)(rand() % SCREEN_WIDTH), (float)(rand() % SCREEN_HEIGHT));

		pBigStarParticle->AddVelocity(0, 3.0f + rand() % 13);

		m_ParticleEmitter->SpawnParticle(pBigStarParticle);
	}
}

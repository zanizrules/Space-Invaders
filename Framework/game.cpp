
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

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <algorithm>

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
{
	
}

Game::~Game()
{
	delete m_playerShip;
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool Game::Initialise()
{
	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// Load the player ship sprite.
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	// Create the player ship instance.
	m_playerShip = new PlayerShip();
	m_playerShip->Initialise(pPlayerSprite);

	// Spawn four rows of alien enemies.
	float paddingFromEdge = (Game::SCREEN_WIDTH / 100) * 3;
	float shipSpacing = 10;
	float y = shipSpacing;

	for (int i = 0; i < Game::ENEMY_ROWS; i++)
	{
		float x = paddingFromEdge;
		while (x < (Game::SCREEN_WIDTH - paddingFromEdge))
		{
			SpawnEnemy(x, y);
			x += (Game::SHIP_SIZE + shipSpacing);
		}
		y += (Game::SHIP_SIZE + shipSpacing);
	}

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
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

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:

	// Ex003.5: Process each alien enemy in the container.

	// Update each bullet in the container.
	for (Bullet* bullet : m_playerBullets)
	{
		bullet->Process(deltaTime);
	}

	for (Explosion* explosion : m_explosions)
	{
		explosion->Process(deltaTime);
	}

	// Update player...
	m_playerShip->Process(deltaTime);

	// Check for bullet vs alien enemy collisions...
	for (Bullet* bullet : m_playerBullets)
	{
		for (EnemyShip* enemy : m_enemyShips)
		{
			// If collided, destory both and spawn explosion.
			if (bullet->IsCollidingWith(enemy))
			{
				bullet->SetDead(true);
				enemy->SetDead(true);
				SpawnExplosion((enemy->GetPositionX() - 16), enemy->GetPositionY());
				break;
			}
			else if (bullet->GetPositionY() == 0)
			{
				bullet->SetDead(true);
				break;
			}
		}
		if (bullet->GetPositionY() == 0)
		{
			bullet->SetDead(true);
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

	// Draw all explosions
	for (Explosion* explosion : m_explosions)
	{
		explosion->Draw(backBuffer);
	}

	// Draw the player ship...
	m_playerShip->Draw(backBuffer);
	
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
	Sprite* pEnemySprite = m_pBackBuffer->CreateSprite("assets\\playerbullet.png");

	// Create a new bullet object.
	Bullet* pPlayerBullet = new Bullet();
	pPlayerBullet->Initialise(pEnemySprite);
	pPlayerBullet->SetVerticalVelocity(-300);
	pPlayerBullet->SetPosition(m_playerShip->GetPositionX(), m_playerShip->GetPositionY());

	// Add the new bullet to the bullet container.
	m_playerBullets.push_back(pPlayerBullet);
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
}

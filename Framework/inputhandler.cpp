
// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"
#include "UserInput.h"
#include "entity.h"
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <Windows.h>
#include <stdio.h>

InputHandler::InputHandler()
: m_pGameController(0)
{
	Entity::Entity();
}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		//SDL_JoystickClose(m_pGameController);
		//delete m_pGameController;
		//m_pGameController = 0;
	}
	Entity::~Entity();
}

bool InputHandler::Initialise(BackBuffer* m_pBackBuffer)
{
	int numControllers = SDL_NumJoysticks();

	for (int i = 0; i < numControllers; i++)
	{
		m_pGameController = SDL_JoystickOpen(i);
	}

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	Sprite* pTargetSprite = m_pBackBuffer->CreateSprite("assets\\target.png");

	Entity::Initialise(pTargetSprite);

	m_x = Game::SCREEN_WIDTH / 2 - 32;
	m_y = Game::SCREEN_HEIGHT / 2;

	return true;
}

void InputHandler::ProcessInput(Game& game)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
		{
			game.FirePlayerMissile(e.button.x, e.button.y);
		}
		else if (e.type == SDL_KEYUP && e.key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			game.FireSpaceShipBullet();
		}
		else if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			// Controller or Keyboard Pressed

			// Tell the game to fire a player bullet...
			if (e.jbutton.button == CONTROLLER_INPUT::A)
			{
				game.FireSpaceShipBullet();
			}
			else if (e.jbutton.button == CONTROLLER_INPUT::R3)
			{
				game.FirePlayerMissile(m_x, m_y);
			}
		}
		else if (e.type == SDL_KEYDOWN || e.type == SDL_JOYHATMOTION)
		{

			// Tell the game to move the space ship left...
			if (e.key.keysym.scancode == SDL_SCANCODE_LEFT // Keyboard
				|| e.jhat.value == SDL_HAT_LEFT || e.jhat.value == SDL_HAT_LEFTDOWN || e.jhat.value == SDL_HAT_LEFTUP) 			{
				game.MoveSpaceShipLeft();
			}
			// Tell the game to move the space ship right...
			else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT ||
				e.jhat.value == SDL_HAT_RIGHT || e.jhat.value == SDL_HAT_RIGHTDOWN || e.jhat.value == SDL_HAT_RIGHTUP)
			{
				game.MoveSpaceShipRight();
			}
			else if (e.jhat.value == SDL_HAT_CENTERED 
				|| e.jhat.value == SDL_HAT_DOWN 
				|| e.jhat.value == SDL_HAT_UP)
			{
				game.StopSpaceShip();
			}
		}
		else if (e.type == SDL_JOYAXISMOTION)
		{
			if (e.jaxis.axis == 0)
			{
				/* Left-right movement code goes here */
				if (e.jaxis.value > 8000)
				{
					game.MoveSpaceShipRight();
				}
				else if (e.jaxis.value < -8000)
				{
					game.MoveSpaceShipLeft();
				}
				else
				{
					game.StopSpaceShip();
				}
			}

			if (e.jaxis.axis == 1)
			{
				/* Up-Down movement on left stick code goes here */
			}

			if (e.jaxis.axis == 3) // Sideways
			{
				if (e.jaxis.value > 8000 || e.jaxis.value < -8000)
				{
					m_velocityX = e.jaxis.value / 50.0f;
				}
				else
				{
					m_velocityX = 0;
				}
			}
			if (e.jaxis.axis == 4) // Upward
			{
				if (e.jaxis.value > 8000 || e.jaxis.value < -8000)
				{
					m_velocityY = e.jaxis.value / 50.0f;
				}
				else
				{
					m_velocityY = 0;
				}
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_LEFT || e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				// Tell the game to stop moving the space ship...
				game.StopSpaceShip();
			}
		}
	}
}

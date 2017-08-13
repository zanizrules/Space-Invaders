
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>

#include "entity.h"

// Forward Declarations:
class Game;

class InputHandler : public Entity
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise(BackBuffer * m_pBackBuffer);

	void ProcessInput(Game& game);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_Joystick* m_pGameController;

private:

};

#endif // __INPUTHANDER_H__

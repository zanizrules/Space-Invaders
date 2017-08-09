
// Library includes:
#include <SDL.h>
#include <crtdbg.h>

// Local includes:
#include "game.h"
#include "logmanager.h"

int main(int argc, char* argv[])
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*
	
	
	{194} normal block at 0x08F92498, 20 bytes long.
		 Data: < %M   M         > 80 25 4D 00 D0 AB 4D 00 20 00 00 00 20 00 00 00 
	{185} normal block at 0x08FB2C58, 20 bytes long.
		 Data: < %M   M         > 80 25 4D 00 00 AB 4D 00 20 00 00 00 20 00 00 00 
	
	*/
	Game& gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game initialise failed!");
		/*
		From LogManager:
		{182} normal block at 0x08FC9028, 1 bytes long.
				Data: < > CD 
		*/

		return (1);
	}
	
	while (gameInstance.DoGameLoop())
	{
		// No body.
	}

	Game::DestroyInstance();

	return (0);
}

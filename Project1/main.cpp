#include "Game.h"
#include <crtdbg.h>
#include <stdlib.h>
#include <time.h>
#include "Engine.h"

int main(int argc, char **argv)
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	srand((unsigned int)time(nullptr));

	Engine::CreateEngine(1920, 1080, false, "Game1");
	
	Game* pGame = (Game*)Engine::GetSingleton()->GetApplication();
	pGame->RunGame();

	Engine::DestroyEngine();

	return 0;
};
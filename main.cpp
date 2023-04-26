#include "Game.h"
#include <Windows.h>

int main()
{
	try {
		Game game;

		game.create();
		game.run();
	}
	catch(std::runtime_error error)
	{
		MessageBoxA(nullptr, error.what(), "Error", MB_OK);
	}

	return 0;
}
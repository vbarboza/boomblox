#include <exception>

#include "Game.hpp"
#include "System.hpp"

int main(int argc, char *args[])
{
	try
	{
		System::Instance()->Init();
	}
	catch (const std::exception err)
	{
		fprintf(stderr, "%s", err);
	}

	Game *game = new Game(System::Instance()->GetRenderer());
	game->Load();
	game->Start();

	return 0;
}

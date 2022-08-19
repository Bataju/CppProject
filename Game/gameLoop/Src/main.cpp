#include "Game.h"
#include"dashboard.h"

Game *game = nullptr;
Dashboard* dashboard = nullptr;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	unsigned int frameStart;
	int frameTime;

	dashboard = new Dashboard();
	dashboard->dashInit("Dashboard", 800, 640, false);
	while (dashboard->dashRunning())
	{
		frameStart = SDL_GetTicks();

		dashboard->dashHandleEvents();
		dashboard->dashUpdate();
		dashboard->dashRender();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	dashboard->dashClean();

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}
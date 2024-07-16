#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) 
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("StubbyKnight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, true);

	
	while (game->running()) {

		frameStart = SDL_GetTicks();

		if (Game::gameReset)
		{
			game->resetGame();
			
			Game::gameReset = false;
		}
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		
		
		game->GameTime = SDL_GetTicks() / 1000;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}
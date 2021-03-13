#pragma once
#include <SDL.h>

class Manager;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
	bool Running() const {return _isRunning;}

	static Manager* entityManager;
	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	bool _isRunning = false;
	SDL_Window* _window;
};




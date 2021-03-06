#pragma once
#include <SDL.h>
#include <vector>

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
	void RestartGame();
	
	bool Running() const {return _isRunning;}

	static Manager* entityManager;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	bool _isRunning = false;
	float tickRate = 0;

	enum GroupLabels : std::size_t
	{
		Player,
		Asteroids,
		Projectiles
	};

private:
	SDL_Window* _window;
};




#pragma once
#include <SDL.h>

class App
{
public:
	App();
	~App();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Render();
	void Clean();
	void DrawPlayer(int screenX, int screenY, int scale);

	bool Running() const {return _isRunning;};

private:
	bool _isRunning = false;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Texture* _playerTexture;
};




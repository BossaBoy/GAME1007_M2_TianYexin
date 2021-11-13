#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <iostream>
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
//#define SPEED 5
using namespace std;

class Engine
{
private: // private properties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	//SDL_Texture* m_pShipTexture;
	//SDL_Texture* m_pBGTexture;

	//SDL_Rect g_player; // For primitive rectangle.
	//SDL_Rect /*g_src,*/ g_dst; // For the ship sprite.

	//bool g_firing = false;

private: // private methods prototypes.
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	void Update();
	void Render();
	void Sleep();
	/*void Clean();*/

public: // public method prototypes.
	int Run();
};

#endif

// Reminder: you can ONLY have declarations (of variables and functions) in headers. What we have here is fine.

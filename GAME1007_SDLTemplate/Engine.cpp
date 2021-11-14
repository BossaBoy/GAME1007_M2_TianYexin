#include "Engine.h"
#include <SDL_image.h>

int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	cout << "Initializing engine..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If initialization is okay...
	{
		// Create the SDL window...
		cout << "First pass." << endl;
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_pWindow != nullptr)
		{
			// Create the SDL renderer...(back buffer)
			cout << "Second pass." << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);
			if (m_pRenderer != nullptr)
			{
				// Initialize subsystems later...
				cout << "Third pass." << endl;

				if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
				{
					m_pShipTexture = IMG_LoadTexture(m_pRenderer, "spaceship.png");
					m_pBGTexture = IMG_LoadTexture(m_pRenderer, "Background.png");
					
				}
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);
	m_player = { WIDTH / 2, HEIGHT / 2, 35, 55 };
	m_dst = { WIDTH / 4, HEIGHT / 2, 99, 63 };
	cout << "Initialization successful!" << endl;
	m_running = true;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}
	}
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_keystates != nullptr)
	{
		if (m_keystates[c] == 1) // Key we're testing for is down.
			return true;
	}
	return false;
}

void Engine::Update()
{
	//cout << "Updating game..." << endl;
	if (KeyDown(SDL_SCANCODE_S) && m_dst.y < (HEIGHT - m_dst.h))
		m_dst.y += SPEED;
	if (KeyDown(SDL_SCANCODE_W) && m_dst.y > 0)
		m_dst.y -= SPEED;

	if (KeyDown(SDL_SCANCODE_A) && m_dst.x > 0)
		m_dst.x -= SPEED;
	if (KeyDown(SDL_SCANCODE_D) && m_dst.x < ((WIDTH / 2) - m_dst.w))
		m_dst.x += SPEED;
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
	// Any drawing here...
	SDL_RenderCopy(m_pRenderer, m_pBGTexture, NULL, NULL);

	SDL_RenderCopy(m_pRenderer, m_pShipTexture, NULL, &m_dst);

	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start; // 1055 - 1050 = 5ms
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);
}

int Engine::Run()
{
	if (m_running == true)
	{
		return 1;
	}
	// Start and run the "engine"
	if (Init("GAME1007 M2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false)
	{
		return 2;
	}
	// We passed our initial checks, start the loop!
	while (m_running == true)
	{
		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_running == true)
			Sleep();
	}
	Clean();
	return 0;
}

void Engine::Clean()
{
	cout << "Cleaning engine..." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyTexture(m_pShipTexture);
	SDL_DestroyTexture(m_pBGTexture);
	IMG_Quit();
	SDL_Quit();
}



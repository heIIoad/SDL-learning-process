#include <SDL.h>
#include <stdio.h>
#include <iostream>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		gWindow = SDL_CreateWindow("Game name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;
	gHelloWorld = SDL_LoadBMP("image/hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		printf("unable to print %s! SDL error:%s\n", "hello_world.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void close(){
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}



int main(int argc, char* args[])
{
	if (!init())
	{
		std::cout << "failed to initialize!\n";
	}
	else
	{
		if (!loadMedia())
		{
			std::cout << "failed to load media!\n";
		}
		else
		{
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	bool quit = false;
	SDL_Event quitting;

	//game loop
	while (!quit)
	{
		while (SDL_PollEvent(&quitting) != 0)
		{
		//quit event
		if (quitting.type == SDL_QUIT) {
			quit = true;
		}
		}

		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
	}

	close();
	return 0;
}
#include <cstdlib>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

using std::cout; using std::cin; using std::endl; using std::string;

void sdl_error(string e, SDL_Window *w = NULL, SDL_Renderer *r = NULL)
{
	if(w)
		SDL_DestroyWindow(w);
	if(r)
		SDL_DestroyRenderer(r);

	cout << e << " " << SDL_GetError() << endl;
	SDL_Quit();
	exit(EXIT_FAILURE);
}

string get_current_path(string file_name = NULL)
{
	string current_path;
	char *base_path = SDL_GetBasePath();
	if(!base_path)
	{
		cout << "SDL_GetBasePath error " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}
	current_path = base_path;
	if(!file_name.empty())
		current_path = current_path + file_name;
	return current_path;
}

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO))
		sdl_error("SDL_Init error");

	SDL_Window *win = SDL_CreateWindow("My window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if(!win)
		sdl_error("SDL_CreateWindow error");

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
										   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
		sdl_error("SDL_CreateRenderer error", win);

	string image_path = get_current_path("hello.bmp");

	SDL_Surface *bmp = SDL_LoadBMP(image_path.c_str());
	if(!bmp)
		sdl_error("SDL_LoadBMP error", win, ren);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if(!texture)
		sdl_error("SDL_CreateTextureFromSurface error", win, ren);

	for(int i = 0; i < 3; ++i)
	{
		SDL_RenderClear(ren);                     // Clear
		SDL_RenderCopy(ren, texture, NULL, NULL); // Draw
		SDL_RenderPresent(ren);                   // Present
		SDL_Delay(1000);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}

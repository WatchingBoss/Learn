#include <cstdlib>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#define S_WIDTH  640
#define S_HEIGHT 480

using std::cout; using std::cin; using std::endl; using std::string;

void cleanup(SDL_Texture *back = NULL, SDL_Texture *front = NULL,
			SDL_Window *w = NULL, SDL_Renderer *r = NULL, bool terminate = false)
{
	SDL_DestroyTexture(back);
	SDL_DestroyTexture(front);
	SDL_DestroyWindow(w);
	SDL_DestroyRenderer(r);

	if(terminate)
	{
		cout << SDL_GetError() << endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
}

void sdl_log_error(std::ostream &os, const string &e, bool terminate = false,
				   SDL_Window *w = NULL, SDL_Renderer *r = NULL)
{
	if(w)
		SDL_DestroyWindow(w);
	if(r)
		SDL_DestroyRenderer(r);

	os << e << " " << SDL_GetError() << endl;

	if(terminate)
	{
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
}

string get_current_path(const string &file_name)
{
	string path;
	char *base_path = SDL_GetBasePath();
	if(base_path)
		path = base_path;
	else
		sdl_log_error(cout, "SDL_GetBasePath error");
	path = path + file_name;
	return path;
}

SDL_Texture *load_texture(const string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if(loadedImage)
	{
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if(!texture)
			sdl_log_error(cout, "CreateTextureFromSurface error");
	}
	else
		sdl_log_error(cout, "LoadBMP error");

	return texture;
}

void render_texture(SDL_Texture *texture, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(ren, texture, NULL, &dest);
}

void draw(SDL_Texture *back, SDL_Texture *front, SDL_Renderer *ren)
{
	SDL_RenderClear(ren);

	int bw, bh;
	SDL_QueryTexture(back, NULL, NULL, &bw, &bh);
	render_texture(back, ren, 0, 0);
	render_texture(back, ren, bw, 0);
	render_texture(back, ren, 0, bh);
	render_texture(back, ren, bw, bh);

	int fw, fh;
	SDL_QueryTexture(front, NULL, NULL, &fw, &fh);
	int x = S_WIDTH / 2 - fw / 2;
	int y = S_HEIGHT / 2 - fh / 2;
	render_texture(front, ren, x, y);

	SDL_RenderPresent(ren);
	SDL_Delay(5000);
}

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO))
		sdl_log_error(cout, "SDL_Init error", true);

	SDL_Window *win = SDL_CreateWindow("My window", 100, 100, S_WIDTH, S_HEIGHT,
									   SDL_WINDOW_SHOWN);
	if(!win)
		sdl_log_error(cout, "SDL_CreateWindow error", true, win);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
										   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
		sdl_log_error(cout, "SDL_CreateRenderer error", true, win, ren);

	SDL_Texture *back = load_texture(get_current_path("back.bmp"), ren);
	SDL_Texture *front = load_texture(get_current_path("front.bmp"), ren);

	if(!back || !front)
		cleanup(back, front, win, ren, true);

	draw(back, front, ren);

	cleanup(back, front, win, ren);
	
	SDL_Quit();
	return 0;
}


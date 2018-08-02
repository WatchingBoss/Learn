#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_W 640
#define SCREEN_H 480

static std::string base_path;

void sys_error(const char *e)
{
	std::cout << e << " " << SDL_GetError() << std::endl;
	IMG_Quit();
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void cleanup(SDL_Window *win, SDL_Renderer *ren, std::vector<SDL_Texture *> *tex)
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	for(auto t : *tex)
		SDL_DestroyTexture(t);
}

void init_window(SDL_Window **mywin, SDL_Renderer **myrend)
{
	SDL_Window *win = SDL_CreateWindow("This win", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										 SCREEN_W, SCREEN_H, 0);
	if(!mywin)
	{
		SDL_DestroyWindow(win);
		sys_error("mainWin: sdl_createwindow");
	}
	SDL_Renderer *rend = SDL_CreateRenderer(win, -1,
											  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!myrend)
	{
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		sys_error("mainWin: sdl_createrenderer");
	}

	*mywin = win;
	*myrend = rend;
}

SDL_Texture * load_texture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if(!texture)
	{
		std::cout << IMG_GetError() << std::endl;
		SDL_Quit();
		IMG_Quit();
		exit(EXIT_FAILURE);
	}
	return texture;
}

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dest);
}
void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	render_texture(tex, ren, x, y, w, h);
}

void draw(SDL_Renderer *rend, std::vector<SDL_Texture *> *tex)
{
	SDL_RenderClear(rend);

	int back_x = 10, back_y = 10;
	int bw, bh;
	for(int i = 0; i < back_x * back_y; ++i)
	{
		int x = i % back_x;
		int y = i / back_x;
		render_texture((*tex)[0], rend, x * 64, y * 48, 64, 48);
	}

	int fw, fh;
	SDL_QueryTexture((*tex)[1], NULL, NULL, &fw, &fh);
	render_texture((*tex)[1], rend, 10, 250);

	int gw, gh;
	SDL_QueryTexture((*tex)[2], NULL, NULL, &gw, &gh);
	render_texture((*tex)[2], rend, 260, 20);

	SDL_RenderPresent(rend);
}

void mainWin()
{
	if(SDL_Init(SDL_INIT_VIDEO))
		sys_error("mainWin: sdl_init");
	int img_init_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if( (IMG_Init(img_init_flags) & img_init_flags) != img_init_flags)
		sys_error("mainWin:img_init");

	SDL_Window *mywin = NULL;
	SDL_Renderer *myrend = NULL;

	init_window(&mywin, &myrend);

	SDL_Texture *front = load_texture(base_path + "img/front.png", myrend);
	SDL_Texture *back = load_texture(base_path + "img/back.jpeg", myrend);
	SDL_Texture *gif = load_texture(base_path + "img/gif_1.gif", myrend);
	std::vector <SDL_Texture *> textures = {back, front, gif};

	if(!front || !back || !gif)
	{
		cleanup(mywin, myrend, &textures);
		sys_error("mainWin: load_texture");
	}

	draw(myrend, &textures);
	SDL_Delay(10000);

	cleanup(mywin, myrend, &textures);
	IMG_Quit();
	SDL_Quit();
}

int main()
{
	base_path = SDL_GetBasePath();

	mainWin();

	return 0;
}

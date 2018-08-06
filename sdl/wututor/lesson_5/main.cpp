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

void cleanup(SDL_Window *win, SDL_Renderer *ren, std::vector<SDL_Texture *> &tex)
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	for(auto t : tex)
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

void render_texture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dest,
					SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dest);
}
void render_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
					SDL_Rect *clip = nullptr)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	if(clip)
	{
		dest.w = clip->w;
		dest.h = clip->h;
	}
	else
		SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	render_texture(tex, ren, dest, clip);
}

struct position
{
	int x, y;
} mypic;

#define RECSIDE 500
void init_start_pos()
{
	mypic.x = SCREEN_W / 2 - RECSIDE / 2;
	mypic.y = SCREEN_H / 2 - RECSIDE / 2;
}

void draw(SDL_Renderer *rend, std::vector<SDL_Texture *> &tex, SDL_Rect *clip)
{
	int red = 255, green = 255, blue = 255, alpha = 255;
	SDL_SetRenderDrawColor(rend, red, green, blue, alpha);
	SDL_RenderClear(rend);
	
	render_texture(tex[0], rend, mypic.x, mypic.y, clip);

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

	SDL_Texture *pic = load_texture(base_path + "img/pic.jpg", myrend);
	std::vector <SDL_Texture *> textures = {pic};

	for(auto tex : textures)
		if(!tex)
		{
			cleanup(mywin, myrend, textures);
			sys_error("mainWin: load_texture");
		}

	int useclip = 0, preclip = 0;

	SDL_Rect clips[4];
	for(int i = 0; i < 4; ++i)
	{
		clips[i].x = i / 2 * RECSIDE;
		clips[i].y = i % 2 * RECSIDE;
		clips[i].w = RECSIDE;
		clips[i].h = RECSIDE;
	}

	init_start_pos();

	SDL_Event evn;
	bool quit = false;
	while(!quit)
	{
		while(SDL_PollEvent(&evn))
		{
			switch(evn.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
				{
					switch(evn.key.keysym.sym)
					{
						case SDLK_1:
							preclip = 0;
							break;
						case SDLK_2:
							preclip = 1;
							break;
						case SDLK_3:
							preclip = 2;
							break;
						case SDLK_4:
							preclip = 3;
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;
					}
				} break;
				case SDL_KEYUP:
					useclip = preclip;
					break;
			}
		}

		draw(myrend, textures, &clips[useclip]);
	}

	cleanup(mywin, myrend, textures);
	IMG_Quit();
	SDL_Quit();
}

int main()
{
	base_path = SDL_GetBasePath();

	mainWin();

	return 0;
}

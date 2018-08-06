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

struct position
{
	int x, y;
} mypic, mytext;

void init_start_pos()
{
	mypic.x = 245;
	mypic.y = 130;

	mytext.x = SCREEN_W / 2 - 200;
	mytext.y = 20;
}

void draw(SDL_Renderer *rend, std::vector<SDL_Texture *> &tex)
{
	int red = 255, green = 255, blue = 255, alpha = 255;
	SDL_SetRenderDrawColor(rend, red, green, blue, alpha);
	SDL_RenderClear(rend);
	
	render_texture(tex[1], rend, mytext.x, mytext.y);
	render_texture(tex[0], rend, mypic.x, mypic.y);

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

	SDL_Texture *pic = load_texture(base_path + "img/pic.png", myrend);
	SDL_Texture *text = load_texture(base_path + "img/text.png", myrend);
	std::vector <SDL_Texture *> textures = {pic, text};

	if(!pic || !text)
	{
		cleanup(mywin, myrend, textures);
		sys_error("mainWin: load_texture");
	}

	init_start_pos();

	SDL_Event evn;
	bool quit = false;
	bool keyup = false;
	int mvx = 0, mvy = 0;
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
					int pos_change = 5;
					switch(evn.key.keysym.sym)
					{
						case SDLK_UP:
							mvy = -pos_change;
							break;
						case SDLK_DOWN:
							mvy = pos_change;
							break;
						case SDLK_RIGHT:
							mvx = pos_change;
							break;
						case SDLK_LEFT:
							mvx = -pos_change;
							break;
					}
				} break;
				case SDL_KEYUP:
				{
					keyup = true;
					switch(evn.key.keysym.sym)
					{
						case SDLK_UP:
							if(mvy < 0)
								mvy = 0;
							break;
						case SDLK_DOWN:
							if(mvy > 0)
								mvy = 0;
							break;
						case SDLK_RIGHT:
							if(mvx > 0)
								mvx = 0;
							break;
						case SDLK_LEFT:
							if(mvx < 0)
								mvx = 0;
							break;
					}
				} break;
			}
		}

		mypic.x += mvx;
		mypic.y += mvy;
		if(keyup)
		{
			printf("X: %d\tY: %d\n", mypic.x, mypic.y);
			keyup = false;
		}

		draw(myrend, textures);
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

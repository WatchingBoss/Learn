#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_W 640
#define SCREEN_H 480

static std::string base_path;

void sys_error(const char *e)
{
	std::cout << e << " " << SDL_GetError() << std::endl;

	TTF_Quit();
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

SDL_Texture * load_texture(const char *text, int length, const std::string &font_ttf_file,
							SDL_Color color, int fontSize, SDL_Renderer *ren)
{
	TTF_Font *font = TTF_OpenFont(font_ttf_file.c_str(), fontSize);
	if(!font)
		sys_error("load_texture: ttf_openfont");

	SDL_Surface *sur = TTF_RenderText_Blended_Wrapped(font, text, color, length);
	if(!sur)
	{
		TTF_CloseFont(font);
		sys_error("load_texture: ttf_rendertext_blended");
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, sur);
	if(!texture)
		sys_error("load_texture: sdl_createTextureFromSurface");

	SDL_FreeSurface(sur);
	TTF_CloseFont(font);
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
} mytext;

void init_start_pos(std::vector<SDL_Texture *> texture)
{
	int width, height;
	SDL_QueryTexture(texture[0], NULL, NULL, &width, &height);
	mytext.x = SCREEN_W / 2 - width / 2;
	mytext.y = SCREEN_H / 2 - height / 2;
}

void draw(SDL_Renderer *rend, std::vector<SDL_Texture *> &tex)
{
	int red = 255, green = 255, blue = 255, alpha = 255;
	SDL_SetRenderDrawColor(rend, red, green, blue, alpha);
	SDL_RenderClear(rend);
	
	render_texture(tex[0], rend, mytext.x, mytext.y);

	SDL_RenderPresent(rend);
}

#define T_LENGTH(a, b) (((a) * 20) < (b) ? ((a) * 20) : (b))

void mainWin()
{
	if(SDL_Init(SDL_INIT_VIDEO))
		sys_error("mainWin: sdl_init");
	if(TTF_Init())
		sys_error("mainWin: ttf_init");

	SDL_Window *mywin = NULL;
	SDL_Renderer *myrend = NULL;

	init_window(&mywin, &myrend);
	SDL_Color color = {0, 255, 0, 255};

	std::vector <SDL_Texture *> textures;

	char const *text_1 = "Sample text for drawing";
	textures.push_back(load_texture(text_1, T_LENGTH(strlen(text_1), SCREEN_W - 40),
									base_path + "font/DejaVuSans-Bold.ttf",
									color, 60, myrend));

	for(auto tex : textures)
		if(!tex)
		{
			cleanup(mywin, myrend, textures);
			sys_error("mainWin: load_texture");
		}

	init_start_pos(textures);

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
						case SDLK_ESCAPE:
							quit = true;
							break;
					}
				} break;
			}
		}

		draw(myrend, textures);
	}

	cleanup(mywin, myrend, textures);
	TTF_Quit();
	SDL_Quit();
}

int main()
{
	base_path = SDL_GetBasePath();

	mainWin();

	return 0;
}

#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win, char h);
void window();

int main()
{
	window();

	return 0;
}

void window()
{
	WINDOW *my_win;
	int startx, starty, width, height,
		ch;
	char h;

	initscr();
	cbreak();

	keypad(stdscr, TRUE);

	height = 1;
	width = 1;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;

	printw("Press wq to exit");
	printw("\nChoose symbol which want use to draw (except q and w): ");

	refresh();

	my_win = create_newwin(height, width, starty, startx);

	while((h = getch()) != 'q')
	{
		while((ch = getch()) != 'w')
		{
			if(ch == 'c')
			{
				height = 10;
				width = 10;
				h = ' ';
			}
			if(ch == 'd')
			{
				height = 1;
				width = 1;
			}
			switch(ch)
			{
				case KEY_LEFT:
				{
					destroy_win(my_win, h);
					my_win = create_newwin(height, width, starty, --startx);
				} break;
				case KEY_RIGHT:
				{
					destroy_win(my_win, h);
					my_win = create_newwin(height, width, starty, ++startx);
				} break;
				case KEY_UP:
				{
					destroy_win(my_win, h);
					my_win = create_newwin(height, width, --starty, startx);
				} break;
				case KEY_DOWN:
				{
					destroy_win(my_win, h);
					my_win = create_newwin(height, width, ++starty, startx);
				} break;
				default:
					break;
			}
		}
	}

	endwin();
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);

	box(local_win, 0, 0);

	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win, char h)
{
	wborder(local_win, h, h, h, h, h, h, h, h);

	wrefresh(local_win);

	delwin(local_win);
}

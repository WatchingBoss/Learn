#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define HEIGHT 10
#define WIDTH 40

char *choices[] = {"Choice 1",
				   "Choice 2",
				   "Choice 3",
				   "Choice 4",
				   "Exit"};
void printMiddle(WINDOW *, int, int, int, char *, chtype);

int main()
{
	ITEM **items;
	int c, nChoices;
	MENU *menu;
	WINDOW *menuWin;

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	nChoices = ARRAY_SIZE(choices);

	items = (ITEM **)calloc(nChoices + 1, sizeof(ITEM *));
	for(int i = 0; i < nChoices; ++i)
		items[i] = new_item(choices[i], NULL);

	menu = new_menu((ITEM **)items);

	menuWin = newwin(HEIGHT, WIDTH, 4, 4);
	keypad(menuWin, TRUE);

	/* Set main window and su window */
	set_menu_win(menu, menuWin);
	set_menu_sub(menu, derwin(menuWin, 6, 38, 3, 1));

	/* Set menu mark to the string " * " */
	set_menu_mark(menu, " * ");

	box(menuWin, 0, 0);
	printMiddle(menuWin, 1, 0, WIDTH, "My Menu", COLOR_PAIR(1));
	mvwaddch(menuWin, 2, 0, ACS_LTEE);
	mvwhline(menuWin, 2, 1, ACS_HLINE, WIDTH - 2);
	mvwaddch(menuWin, 2, WIDTH - 1, ACS_RTEE);
	mvprintw(LINES - 2, 0, "\'q\' to exit");
	refresh();

	post_menu(menu);
	wrefresh(menuWin);
	
	while((c = wgetch(menuWin)) != 'q')
	{
		switch(c)
		{
			case KEY_DOWN:
				menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			default:
				break;
		}
		wrefresh(menuWin);
	}

	unpost_menu(menu);
	free_menu(menu);
	curs_set(FALSE);
	endwin();
	return(0);
}

void printMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
	int x, y;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	x = startx + ((width - (strlen(string))) / 2);
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
}

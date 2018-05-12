#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define HEIGHT 10
#define WIDTH 40

char *choices[] = {"Choice 1",
				   "Choice 2",
				   "Choice 3",
				   "Choice 4",
				   "Choice 5",
				   "Choice 6",
				   "Choice 7",
				   "Choice 8",
				   "Choice 9",
				   "Choice 10",
				   "Exit",
				   (char *)NULL};
void printMiddle(WINDOW *, int, int, int, char *, chtype);

int main()
{
	ITEM **myItems;
	int c, nChoices;
	MENU *myMenu;
	WINDOW *menuWin;

	initscr();
	start_color();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	nChoices = ARRAY_SIZE(choices);
	myItems = (ITEM **)calloc(nChoices, sizeof(ITEM *));
	for(int i = 0; i < nChoices; ++i)
		myItems[i] = new_item(choices[i], NULL);

	myMenu = new_menu((ITEM **)myItems);

	menuWin = newwin(HEIGHT, WIDTH, 4, 4);
	keypad(menuWin, TRUE);

	set_menu_win(myMenu, menuWin);
	set_menu_sub(myMenu, derwin(menuWin, HEIGHT - 4, WIDTH - 2, 3, 1));
	set_menu_format(myMenu, 5, 1);

	set_menu_mark(myMenu, " * ");

	box(menuWin, 0, 0);
	printMiddle(menuWin, 1, 0, WIDTH, "My Menu", COLOR_PAIR(1));
	mvwaddch(menuWin, 2, 0, ACS_LTEE);
	mvwhline(menuWin, 2, 1, ACS_HLINE, WIDTH - 2);
	mvwaddch(menuWin, 2, WIDTH - 1, ACS_RTEE);

	post_menu(myMenu);
	wrefresh(menuWin);

	attron(COLOR_PAIR(2));
	mvprintw(LINES - 2, 0, "Use PageUp and PageDown to scroll up or down a page of items");
	mvprintw(LINES - 1, 0, "Arrow Keys to navigate (\'q\' to Exit)");
	attroff(COLOR_PAIR(2));
	refresh();

	while((c = wgetch(menuWin)) != 'q')
	{
		switch(c)
		{
			case KEY_DOWN:
				menu_driver(myMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(myMenu, REQ_UP_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(myMenu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(myMenu, REQ_SCR_UPAGE);
				break;
		}
		wrefresh(menuWin);
	}

	unpost_menu(myMenu);
	free_menu(myMenu);
	
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
		width == 40;

    x = startx + ((width - strlen(string)) / 2);
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

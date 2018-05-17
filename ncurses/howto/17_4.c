#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define HEIGHT 10
#define WIDHT 70
#define wY 4
#define wX 4

char *choices[] = {"Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
				   "Choice 6", "Choice 7", "Choice 8", "Choice 9", "Choice 10",
				   "Choice 11", "Choice 12", "Choice 13", "Choice 14", "Choice 15",
				   "Choice 16", "Choice 17", "Choice 18", "Choice 19", "Choice 20",
				   "Exit", (char *)NULL};

int main()
{
	ITEM **myItems;
	int c, nChoices;
	MENU *myMenu;
	WINDOW *myWin;

	initscr();
	noecho();
	cbreak();
	start_color();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	curs_set(FALSE);

	nChoices = ARRAY_SIZE(choices);
	myItems = (ITEM **)calloc(nChoices, sizeof(ITEM *));
	for(int i = 0; i < nChoices; ++i)
		myItems[i] = new_item(choices[i], NULL);

	myMenu = new_menu((ITEM **)myItems);

	menu_opts_off(myMenu, O_SHOWDESC);

	myWin = newwin(HEIGHT, WIDHT, wY, wX);
	keypad(myWin, TRUE);

	set_menu_win(myMenu, myWin);
	set_menu_sub(myMenu, derwin(myWin, HEIGHT - 3, WIDHT - 2, wY - 1, wX - 3));
	set_menu_format(myMenu, 5, 3);
	set_menu_mark(myMenu, " * ");

	box(myWin, 0, 0);

	attron(COLOR_PAIR(2));
	mvprintw(LINES - 3, 0, "Use PageUp and PageDown to scroll");
	mvprintw(LINES - 3, 0, "Use Arrow Keys to navigate (\'q\' to Exit)");	
	attroff(COLOR_PAIR(2));
	refresh();

	post_menu(myMenu);
	wrefresh(myWin);

	while((c = wgetch(myWin)) != 'q')
	{
		switch(c)
		{
			case KEY_DOWN:
				menu_driver(myMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(myMenu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(myMenu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(myMenu, REQ_RIGHT_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(myMenu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(myMenu, REQ_SCR_UPAGE);
				break;
		}
		wrefresh(myWin);
	}

	unpost_menu(myMenu);
	free_menu(myMenu);
	for(int i = 0; i < nChoices; ++i)
		free_item(myItems[i]);
	curs_set(FALSE);
	endwin();
	return(0);
}

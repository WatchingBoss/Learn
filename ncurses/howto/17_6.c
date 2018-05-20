#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

char *choices[] = {"Choice 1", "Choice 2", "Choice 3", "Choice 4", "Choice 5",
				   "Choice 6", "Choice 7", "Exit"};

int main()
{
	ITEM **myItems;
	int c, nChoices;
	MENU *myMenu;

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

	nChoices = ARRAY_SIZE(choices);
	myItems = (ITEM **)calloc(nChoices + 1, sizeof(ITEM **));
	for(int i = 0; i < nChoices; ++i)
		myItems[i] = new_item(choices[i], NULL);
	myItems[nChoices] = (ITEM *)NULL;
	item_opts_off(myItems[3], O_SELECTABLE);
	item_opts_off(myItems[6], O_SELECTABLE);

	myMenu = new_menu((ITEM **)myItems);

	set_menu_fore(myMenu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(myMenu, COLOR_PAIR(2));
	set_menu_grey(myMenu, COLOR_PAIR(3));

	mvprintw(LINES - 3, 0, "Press <ENTER> to see the option selected");
	mvprintw(LINES - 2, 0, "Up and Down arrow keys to navigate (\'q\' to Exit)");
	post_menu(myMenu);
	refresh();

	while((c = getch()) != 'q')
	{
		switch(c)
		{
			case KEY_DOWN:
				menu_driver(myMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(myMenu, REQ_UP_ITEM);
				break;
			case 10:
				move(20, 0);
				clrtoeol();
				mvprintw(20, 0, "Item selected is: %s", item_name(current_item(myMenu)));
				pos_menu_cursor(myMenu);
				break;
		}
	}

	unpost_menu(myMenu);
	for(int i = 0; i < nChoices; ++i)
		free_item(myItems[i]);
	free_menu(myMenu);

	curs_set(TRUE);
	endwin();
	return(0);
}

#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {"Choice 1",
				   "Choice 2",
				   "Choice 3",
				   "Choice 4",
				   "Exit"};

int main()
{
	ITEM **items;
	int c;
	MENU *menu;
	int nChoices;
	ITEM *curItem;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);

	nChoices = ARRAY_SIZE(choices);
	items = (ITEM **)calloc(nChoices + 1, sizeof(ITEM *));

	for(int i = 0; i < nChoices; ++i)
		items[i] = new_item(choices[i], NULL);
	items[nChoices] = (ITEM *)NULL;

	menu = new_menu((ITEM **)items);
	mvprintw(LINES - 2, 0, "\'q\' to Exit");
	post_menu(menu);
	refresh();

	while((c = getch()) != 'q')
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
	}

	for(int i = 0; i < nChoices; ++i)
		free_item(items[i]);
	free_menu(menu);
	curs_set(FALSE);
	endwin();
	return(0);
}

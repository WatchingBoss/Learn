#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

char *choices[] = {"Choice 1", "Choice 2", "Choice 3", "Choice 4",
				   "Choice 5", "Choice 6", "Choice 7", "Exit"};

void print(char *);

int main()
{
	ITEM **myItems;
	int c, nChoices;
	MENU *myMenu;

	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);	

	nChoices = ARRAY_SIZE(choices);
	myItems = (ITEM **)calloc(nChoices, sizeof(ITEM *));
	for(int i = 0; i < nChoices; ++i)
	{
		myItems[i] = new_item(choices[i], NULL);
		set_item_userptr(myItems[i], print);
	}
	myItems[nChoices] = (ITEM *)NULL;

	myMenu = new_menu((ITEM **)myItems);

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
			{
				ITEM *curs;
				void (*p)(char *);
				curs = current_item(myMenu);
				p = item_userptr(curs);
				p((char *)item_name(curs));
				pos_menu_cursor(myMenu);
				break;
			}
		}
	}

	unpost_menu(myMenu);
	for(int i = 0; i < nChoices; ++i)
		free_item(myItems[i]);
	free_menu(myMenu);

	curs_set(FALSE);
	endwin();
	return(0);
}

void print(char *name)
{
	move(20, 0);
	clrtoeol();
	mvprintw(20, 0, "Item selected is : %s", name);
}

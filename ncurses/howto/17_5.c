#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {"Choice 1", "Choice 2", "Choice 3",
				   "Choice 4", "Choice 5", "Choice 6",
				   "Choice 7", "Exit"};

int main()
{
	ITEM **myItem;
	int c, nChoices;
	MENU *myMenu;
	ITEM *curItem;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);

	nChoices = ARRAY_SIZE(choices);

	myItem = (ITEM **)calloc(nChoices + 1, sizeof(ITEM *));
	for(int i = 0; i < nChoices; ++i)
		myItem[i] = new_item(choices[i], NULL);
	myItem[nChoices] = (ITEM *)NULL;

	myMenu = new_menu((ITEM **)myItem);

	menu_opts_off(myMenu, O_ONEVALUE);

	mvprintw(LINES - 3, 0, "Use <SPACE> to select or unselect an item");
	mvprintw(LINES - 2, 0, "<ENTER> to see presently selected items (\'q\' to Exit)");
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
			case ' ':
				menu_driver(myMenu, REQ_TOGGLE_ITEM);
				break;
			case 10:
			{
				char temp[200];
				ITEM **items;

				items = menu_items(myMenu);
				temp[0] = '\0';
				
				for(int i = 0; i < item_count(myMenu); ++i)
				{
					if(item_value(items[i]) == TRUE)
					{
						strcat(temp, item_name(items[i]));
						strcat(temp, " ");

						if(item_value(items[nChoices - 1]) == TRUE)
							goto exit;
					}
				}
				
				move(20, 0);
				clrtoeol();
				mvprintw(20, 0, temp);
				refresh();
			} break;
		}
	}

	goto exit;
	
exit:
	free_item(myItem[0]);
	free_item(myItem[1]);
	free_menu(myMenu);

	curs_set(TRUE);
	endwin();
	return(0);
}

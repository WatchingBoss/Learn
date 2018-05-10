#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0,
	starty = 0;

char *choices[] = {"Choice 1",
				   "Choice 2",
				   "Choice 3",
				   "Choice 4",
				   "Exit"};

int nChoices = sizeof(choices) / sizeof(char *);
void printMenu(WINDOW *, int);

int main()
{
	WINDOW *win;
	int highlight = 1,
		choice = 0,
		c;

	initscr();
	clear();
	noecho();
	cbreak();
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	curs_set(FALSE);

	win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(win, TRUE);
	mvprintw(0, 0, "Use arrow keys to fo up and down, Press enter to select a choice");
	refresh();
	printMenu(win, highlight);

	while(1)
	{
		c = wgetch(win);
		switch(c)
		{
			case KEY_UP:
				if(highlight == 1)
					highlight = nChoices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == nChoices)
					highlight = 2;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Character pressed is = %3d Hopefully it can be printed as %c", c, c);
				refresh();
				break;
		}

		printMenu(win, highlight);
		if(choice != 0)
			break;
	}

	mvprintw(23, 0, "You chose choice %d with choice string %s \n", choice, choices[choice - 1]);
	clrtoeol();
	refresh();
	if(choice != 5)
		getch();
	curs_set(TRUE);
	endwin();

	return(0);
}

void printMenu(WINDOW *win, int highlight)
{
	int x = 2, y = 2;

	box(win, 0, 0);
	for(int i = 0; i < nChoices; ++i)
	{
		if(highlight == i + 1)
		{
			wattron(win, A_REVERSE);
			mvwprintw(win, y, x, "%s", choices[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(win);
}

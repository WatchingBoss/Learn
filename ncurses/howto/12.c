#include <ncurses.h>
#include <string.h>

#define HEIGHT 10
#define WIDTH 20

int starty = 0,
	startx = 0;

char *choices[] = {"Choice 1",
				   "Choice 2", 
				   "Choice 3", 
				   "Choice 4", 
				   "Exit"};
int nChoices = sizeof(choices) / sizeof(char *);

void printMenu(WINDOW *, int);
void reportChoice(int, int, int *);

int main()
{
	int c, choice = 0;
	WINDOW *win;
	MEVENT event;

	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(FALSE);

	starty = (24 - HEIGHT) / 2;
	startx = (80 - WIDTH) / 2;

	attron(A_REVERSE);
	mvprintw(23, 1, "Click on Exit to quit");
	refresh();
	attron(A_REVERSE);
	
	win = newwin(HEIGHT, WIDTH, starty, startx);
	printMenu(win, 1);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	keypad(win, TRUE);

	while(1)
	{
		c = wgetch(win);
		switch(c)
		{
			case KEY_MOUSE:
				if(getmouse(&event) == OK)
				{
					if(event.bstate & BUTTON1_CLICKED)
					{
						reportChoice(event.x + 1, event.y + 1, &choice);
						if(choice == -1)
							goto end;
						mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"",
								 choice, choices[choice - 1]);
						refresh();
					}
				}
				printMenu(win, choice);
				break;
			default:
				break;
		}
	}
	
end:
	curs_set(TRUE);
	endwin();
	return(0);
}

void printMenu(WINDOW *win, int highlight)
{
	int y = 2,
		x = (WIDTH - strlen(choices[0])) / 2;

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
}

void reportChoice(int mouseX, int mouseY, int *pChoice)
{
	int i = starty + 3,
		j = startx + ((WIDTH - strlen(choices[0])) / 2);

	for(int ch = 0; ch < nChoices; ++ch)
	{
		if(mouseY == i + ch && mouseX >= j && mouseX <= j + strlen(choices[ch]))
		{
			if(ch == nChoices - 1)
				*pChoice = -1;
			else
				*pChoice = ch + 1;
			break;
		}
	}
}

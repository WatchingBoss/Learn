#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void printMiddle(WINDOW *, int, int, char *);

int main()
{
	initscr();
	if(has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	printMiddle(stdscr, LINES / 2, 0, "This text is green color");
	attroff(COLOR_PAIR(1));

	getch();
	endwin();
	return(0);
}

void printMiddle(WINDOW *win, int starty, int startx, char *string)
{
	int x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);

	y = starty;

	temp = (COLS - (strlen(string))) / 2;
 	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

#include <ncurses.h>
#include <string.h>

void ex()
{
	char mesg[] = "This string takes place on center of screen";
	int row, col;

	initscr();
	getmaxyx(stdscr, row, col);
	mvprintw(row/2, (col-strlen(mesg)) / 2, "%s", mesg);           // center

	mvprintw(row - 2, 0, "This screen has %d rows and %d columns\n", row, col);       
	printw("Try resizing your window (if possible) and then run this program again");

	refresh();

	getch();
	endwin();
}

int main()
{
	ex();

	return 0;
}

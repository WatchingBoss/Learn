#include <ncurses.h>
#include <string.h>

void ex()
{
	char *mesg = "Enter a string: ";
	char str[80];
	int row, col;

	initscr();
	getmaxyx(stdscr, row, col);
	mvprintw(row / 2, (col - strlen(mesg)) / 2, "%s", mesg);

	getstr(str);
	mvprintw(LINES - 3, 0, "You Entered: %s", str);

	getch();
    endwin();
}

int main()
{
    ex();

    return 0;
}

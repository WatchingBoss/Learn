#include <ncurses.h>

int hello()
{
	initscr();               // start curses mode
	printw("Hello World!");	 // printf
	refresh();				 // print it on to the real screen
	getch(); 				 // wait for user input
	endwin();				 // end curses mode

	return(0);
}


int main()
{
    hello();

    return(0);
}

#include <ncurses.h>
#include <stdlib.h>

void ex(int numAr, char *ar[])
{
	int ch, prev, row, col;
	prev = EOF;
	FILE *fp;
	int y, x;

	if(numAr != 2)
	{
		printf("Usage: %s <a c file name>\n", ar[0]);
		exit(1);
	}

	fp = fopen(ar[1], "r");
	
	if(fp == NULL)
	{
		perror("Cannot open input file");
		exit(1);
	}

	initscr();                              /* Start curses mode */
	getmaxyx(stdscr, row, col);             /* fine the boundaries of the screen */

	while((ch = fgetc(fp)) != EOF)
	{
		getyx(stdscr, y, x);                /* get the current curser position */

		if(y == (row - 1))
		{
			printw("<-Press Any Key->");    /* tell the user to press a key */
			getch();
			clear();
			move(0, 0);
		}

		if(prev == '/' && ch == '*')
		{
			attron(A_BOLD);
			getyx(stdscr, y, x);
			move(y, x - 1);
			printw("%c%c", '/', ch);
		}
		else
			printw("%c", ch);

		refresh();

		if(prev == '*' && ch == '/')
			attroff(A_BOLD);

		prev = ch;
	}

	endwin();
	fclose(fp);
}

void gat()
{
	initscr();
	start_color();                  /* Start color functionality */

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	printw("A Big string which I did not care to type fully");
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	/* 0, 0 - position to Start                                           *
	 * -1 - number of character to update, -1 means till end of line      *
	 * A_BLINK attribute we want to give to the character                 *
	 * 1 - color index, given during init_pair. 0 if we do not want color *
	 * NULL - always same                                                 * 
	 */

	refresh();

	getch();
	endwin();
}

void gatgat()
{
	initscr();
	start_color();                  

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	for(int i = 0; i < 10; ++i)
		printw("  A Big string which I did not care to type fully\n");

	printw("\n\nDo you want to chang the color? y/n: ");
	for(int i = 0; i < 10; ++i)
	{
		if(getch() == 'y')
		{
			move(50, 50);
			mvchgat(i, 0, -1, A_BLINK, 1, NULL);
	
			refresh();
		}
		else
		{
			move(50, 50);
			printw("\nPress any button to way out\n");
			break;
		}
	}
	
	refresh();

	getch();
	endwin();
}

int main(int argc, char *argv[])
{
	gatgat();
	
	return 0;
}

#include <ncurses.h>
#include <panel.h>
#include <string.h>

#define NLINES 10
#define NCOLS 40
#define NWINS 4

void initWins(WINDOW **);
void showWin(WINDOW *, char *, int);
void printMiddle(WINDOW *, int, int, int, char *, chtype);

int main()
{
	WINDOW *wins[NWINS];
	PANEL *panels[NWINS];
	PANEL *top;
	int ch;

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	initWins(wins);

	for(int i = 0; i < NWINS; ++i)
		panels[i] = new_panel(wins[i]);

	for(int i = 0, j = i + 1; i < NWINS; ++i, ++j)
	{
		if(NWINS - i == 1)
			j = 0;
		set_panel_userptr(panels[i], panels[j]);
	}

	update_panels();

	attron(COLOR_PAIR(4));
	mvprintw(LINES - 3, 2, "Use tab to browse through the windows ('q' to Exit)");
	attroff(COLOR_PAIR(4));
	doupdate();

	top = panels[NWINS - 1];
	while((ch = getch()) != 'q')
	{
		switch(ch)
		{
			case 9:
				top = (PANEL *)panel_userptr(top);
				top_panel(top);
				break;
			default:
				break;
		}
		update_panels();
		doupdate();
	}
	
	curs_set(TRUE);
	endwin();
	return(0);
}


void initWins(WINDOW **wins)
{
	int y = 2,
		x = 10;
	char label[80];

	for(int i = 0; i < NWINS; ++i)
	{
		wins[i] = newwin(NLINES, NCOLS, y, x);
		sprintf(label, "Window Number %d", i + 1);
		showWin(wins[i], label, i + 1);
		y += 5;
		x += 10;
	}	
}

void showWin(WINDOW *win, char *label, int labelColor)
{
	int starty, startx, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	printMiddle(win, 1, 0, width, label, COLOR_PAIR(labelColor));
}

void printMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
	int x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	temp = (width - (strlen(string))) / 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}


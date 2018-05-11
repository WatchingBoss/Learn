#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>

typedef struct _PANEL_DATA
{
	int x, y, w, h;
	char label[80];
	int labelColor;
	PANEL *next;
} PANEL_DATA;

#define NLINES 10
#define NCOLS 40
#define NWINS 4

void initWins(WINDOW **);
void setUserPtrs(PANEL **);
void showWin(WINDOW *, char *, int);
void printMiddle(WINDOW *, int, int, int, char *, chtype);

int main()
{
	WINDOW *wins[NWINS];
	PANEL *panels[NWINS];
	PANEL_DATA *top;
	PANEL *stackTop;
	WINDOW *tempWin, *oldWin;
	int ch,
		newx, newy, neww, newh,
		size = FALSE,
		move = FALSE;

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

	setUserPtrs(panels);

	update_panels();

	attron(COLOR_PAIR(4));
	mvprintw(LINES - 4, 2, "Use 'm' for moving, 'r' for resizing");
	mvprintw(LINES - 3, 2, "Use tab to browse through the windows ('q' to Exit)");
	attroff(COLOR_PAIR(4));
	doupdate();

	stackTop = panels[NWINS - 1];
	top = (PANEL_DATA *)panel_userptr(stackTop);
	newx = top->x;
	newy = top->y;
	neww = top->w;
	newh = top->h;
	while((ch = getch()) != 'q')
	{
		switch(ch)
		{
			case 9:
				top = (PANEL_DATA *)panel_userptr(stackTop);
				top_panel(top->next);
				stackTop = top->next;
				top = (PANEL_DATA *)panel_userptr(stackTop);
				newx = top->x;
				newy = top->y;
				neww = top->w;
				newh = top->h;
				break;
			case 'r':
				size = TRUE;
				attron(COLOR_PAIR(4));
				mvprintw(LINES - 5, 0, "Entered Resizing: Use Arrow Keys to Resize and press <ENTER> "
						 "to end Resizing");
				refresh();
				attroff(COLOR_PAIR(4));
			case 'm':
				move = TRUE;
				attron(COLOR_PAIR(4));
				mvprintw(LINES - 5, 0, "Entered Moving: Use Arrow Keys to Move and press <ENTER> "
						 "to end Moving");
				refresh();
				attroff(COLOR_PAIR(4));
			case KEY_LEFT:
				if(size == TRUE)
				{
					--newx;
					++neww;
				}
				if(move == TRUE)
					--newx;
				break;
			case KEY_RIGHT:
				if(size == TRUE)
				{
					++newx;
					--neww;
				}
				if(move == TRUE)
					++newx;
				break;
			case KEY_UP:
				if(size == TRUE)
				{
					--newy;
					++newh;
				}
				if(move == TRUE)
					--newy;
				break;
			case KEY_DOWN:
				if(size == TRUE)
				{
					++newy;
					--newh;
				}
				if(move == TRUE)
					++newy;
				break;
			case 10:
				move(LINES - 4, 0);
				clrtoeol();
				refresh();
				if(size == TRUE)
				{
					oldWin = panel_window(stackTop);
					tempWin = newwin(newh, neww, newy, newx);
					replace_panel(stackTop, tempWin);
					showWin(tempWin, top->label, top->labelColor);
					delwin(oldWin);
					size = FALSE;
				}
				if(move == TRUE)
					{
						move_panel(stackTop, newy, newx);
						move = FALSE;
					}
				break;
			default:
				break;
		}
		attron(COLOR_PAIR(4));
		mvprintw(LINES - 4, 2, "Use 'm' for moving, 'r' for resizing");
		mvprintw(LINES - 3, 2, "Use tab to browse through the windows ('q' to Exit)");
		attroff(COLOR_PAIR(4));
		refresh();
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

void setUserPtrs(PANEL **panels)
{
	PANEL_DATA *ptrs;
	WINDOW *win;
	int x, y, w, h;
	char temp[80];

	ptrs = (PANEL_DATA *)calloc(NWINS, sizeof(PANEL_DATA));

	for(int i = 0; i < NWINS; ++i)
	{
		win = panel_window(panels[i]);
		getbegyx(win, y, x);
		getmaxyx(win, h, w);
		ptrs[i].x = x;
		ptrs[i].y = y;
		ptrs[i].w = w;
		ptrs[i].h = h;
		sprintf(temp, "Window Number %d", i + 1);
		strcpy(ptrs[i].label, temp);
		ptrs[i].labelColor = i + 1;
		if(i + 1 == NWINS)
			ptrs[i].next = panels[0];
		else
			ptrs[i].next = panels[i + 1];
		set_panel_userptr(panels[i], &ptrs[i]);
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


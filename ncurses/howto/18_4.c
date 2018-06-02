/*
 * Form windows example
 */

#include <ncurses.h>
#include <form.h>
#include <string.h>

void printMiddle(WINDOW *, int, int, int, char *, chtype);

int main()
{
	FIELD *myField[3];
	FORM *myForm;
	WINDOW *myWin;
	int choose,
		rows,
		cols;

	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	init_pair(1, COLOR_RED, COLOR_BLACK);

	myField[0] = new_field(1, 10, 6, 1, 0, 0);
	myField[1] = new_field(1, 10, 8, 1, 0, 0);
	myField[2] = NULL;

	for(int i = 0; i < 2; ++i)
	{
		set_field_back(myField[i], A_UNDERLINE);
		field_opts_off(myField[i], O_AUTOSKIP);
	}

	myForm = new_form(myField);

	scale_form(myForm, &rows, &cols);

	myWin = newwin(rows + 4, cols + 4, 4, 4);
	keypad(myWin, TRUE);

	set_form_win(myForm, myWin);
    set_form_sub(myForm, derwin(myWin, rows, cols, 2, 2));

	mvprintw(LINES - 3, 0, "Use UP and DOWN arrow keys to switch between fields");
	mvprintw(LINES - 2, 0, "Press F2 to exit");
	refresh();

	box(myWin, 0, 0);
	printMiddle(myWin, 1, 0, cols + 4, "My Form", COLOR_PAIR(1));

	post_form(myForm);
	wrefresh(myWin);

	while((choose = getch()) != KEY_F(2))
	{
		switch(choose)
		{
			case KEY_DOWN:
				form_driver(myForm, REQ_NEXT_FIELD);
				form_driver(myForm, REQ_END_LINE);
				break;
			case KEY_UP:
				form_driver(myForm, REQ_PREV_FIELD);
				form_driver(myForm, REQ_END_LINE);
				break;
			default:
				form_driver(myForm, choose);
				break;
		}
		wrefresh(myWin);
	}

	unpost_form(myForm);
	free_form(myForm);
	for(int i = 0; i < 2; ++i)
		free_field(myField[i]);

	endwin();
	return(0);
}

void printMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
	int x, y;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	x = startx + ((width - (strlen(string))) / 2);
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

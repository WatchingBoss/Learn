/*
 * Attributes example
 */

#include <ncurses.h>
#include <form.h>

int main()
{
	FIELD *myField[3];
	FORM *myForm;
	int choose;

	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, TRUE);

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);

	myField[0] = new_field(1, 10, 4, 18, 0, 0);
	myField[1] = new_field(1, 10, 6, 18, 0, 0);
	myField[2] = NULL;

	set_field_fore(myField[0], COLOR_PAIR(1));
	set_field_back(myField[0], COLOR_PAIR(2));

	field_opts_off(myField[0], O_AUTOSKIP);

	set_field_back(myField[1], A_UNDERLINE);
	field_opts_off(myField[1], O_AUTOSKIP);

	myForm = new_form(myField);
	post_form(myForm);
	refresh();

	set_current_field(myForm, myField[0]);
	mvprintw(LINES - 3, 0, "Use UP, DOWN arrows to switch between fields");
	mvprintw(LINES - 2, 0, "Press F2 to exit");
	mvprintw(4, 10, "Value 1:");
	mvprintw(6, 10, "Value 2:");
	refresh();

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
	}

	unpost_form(myForm);
	free_form(myForm);
	for(int i = 0; i < 2; ++i)
		free_field(myField[i]);

	endwin();
	return(0);
}

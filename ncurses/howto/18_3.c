/*
 * Sample using field options
 */

#include <ncurses.h>
#include <form.h>

#define STARTY   4
#define STARTX   15
#define WIDTH    25
#define N_FIELDS 3

int main()
{
	FIELD *myField[N_FIELDS];
	FORM *myForm;
	int choose;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	for(int i = 0; i < N_FIELDS - 1; ++i)
		myField[i] = new_field(1, WIDTH, STARTY + i * 2, STARTX, 0, 0);
	myField[N_FIELDS - 1] = NULL;

	set_field_back(myField[1], A_UNDERLINE); // print line for the option

	field_opts_off(myField[0], O_ACTIVE);   // static lable 
	field_opts_off(myField[1], O_PUBLIC);   // like password field
	field_opts_off(myField[1], O_AUTOSKIP); // after last character is entered

	myForm = new_form(myField);
	post_form(myForm);
	refresh();

	set_field_just(myField[0], JUSTIFY_CENTER);
	set_field_buffer(myField[0], 0, "This is a static field");
	mvprintw(LINES - 3, 1, "Use Up and Down arrow keys to move throughj fields");
	mvprintw(LINES - 2, 1, "Press F2 to exit");
	mvprintw(STARTY, STARTX - 9, "Field 1:");
	mvprintw(STARTY + 2, STARTX - 9, "Field 2:");
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
	for(int i = 0; i < N_FIELDS - 1; ++i)
		free_field(myField[i]);

	endwin();
	return(0);
}

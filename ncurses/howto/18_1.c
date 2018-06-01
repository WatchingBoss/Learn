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
	keypad(stdscr, TRUE);

	myField[0] = new_field(1, 10, 4, 18, 0, 0);
	myField[1] = new_field(1, 10, 6, 18, 0, 0);
	myField[2] = NULL;

	for(int i = 0; i < 2; ++i)
	{
		set_field_back(myField[i], A_UNDERLINE); // Print a line for the option
		field_opts_off(myField[i], O_AUTOSKIP);  // Don't go to next field when this
	}

	myForm = new_form(myField);
	post_form(myForm);
	refresh();

	mvprintw(4, 10, "Value 1: ");
	mvprintw(6, 10, "Value 2: ");
	refresh();

	while((choose = getch()) != KEY_F(2))
	{
		switch(choose)
		{
			case KEY_DOWN:
				form_driver(myForm, REQ_NEXT_FIELD); // Go to next line
				/*Go to end of the present buffer, leaves at the last character*/
				form_driver(myForm, REQ_END_LINE); 
				break;
			case KEY_UP:
				form_driver(myForm, REQ_PREV_FIELD);
				form_driver(myForm, REQ_END_LINE);
				break;
			default:
				form_driver(myForm, choose); // Print normal character
				break;
		}
	}

	unpost_form(myForm);
	free_form(myForm);
	for(int i = 0; i < 2; ++i)
		free_field(myField[i]);

	endwin();
}

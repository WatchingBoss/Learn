#include <ncurses.h>
#include <panel.h>

#define WINS 3

int main()
{
	WINDOW *wins[WINS];
	PANEL *panels[WINS];
	int lines = 10,
		cols = 40,
		y = 2,
		x = 4;
	initscr();
	cbreak();
	noecho();
	curs_set(FALSE);

	for(int i = 0; i < WINS; ++i)
		wins[i] = newwin(lines, cols, y + i, x + i * 5);

	for(int i = 0; i < WINS; ++i)
		box(wins[i], 0, 0);

	for(int i = 0; i < WINS;  ++i)
		panels[i] = new_panel(wins[i]);

	update_panels();
	doupdate();

	curs_set(TRUE);
	getch();
	endwin();
	return(0);
}

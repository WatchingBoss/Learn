#include <sys/ioctl.h>
#include <stdio.h>

int main()
{
	struct winsize windowSize;
	unsigned short row, col, x, y;

	/* call ioctl() to get dimensions of terminal.*
	 * This function return 0 or -1 for TIOCFWINS.*
     * And defines elements of winsize structure. */
	ioctl(0, TIOCGWINSZ, &windowSize); // call ioctl () to get dimensions of terminal

	row = windowSize.ws_row;
	col = windowSize.ws_col;
	x   = windowSize.ws_xpixel;
	y   = windowSize.ws_ypixel;
	
	printf("rows       is %d in characters\n"
		   "cols       is %d in characters\n"
		   "horizontal is %d in pixels\n"
		   "vertical   is %d in pixels\n",
		   row, col, x, y);

	return(0);
}

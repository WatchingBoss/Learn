#include "include/inc.h"

void run_tests()
{
	common_test();
	lex_test();
	print_test();
}

int main(int argc, char **argv)
{
	run_tests();
	
	return(0);
}

#include "include/inc.h"

void main_test()
{
	common_test();
	lex_test();
	parse_test();
}

int main(int argc, char **argv)
{
	main_test();
	
	return(0);
}

/*         
 * Learn to use crypt() in unistd of X/Open System Interface         
 */

#define _XOPEN_SOURCE

#include <stdio.h>
#include <unistd.h> // Use crypt()
#include <stdlib.h> // Use srand(), rand(), calloc()
#include <time.h>   // Use time()

#define NUM 5

int main()
{
	srand(time(NULL));

	char *simple = "My own plant text";
	char *after_crypt;
	char this_salt[NUM];

	for(int i = 0; i < NUM; ++i)
		this_salt[i] = (char)((rand() % (92 - 65)) + 65); // rand % (max + 1 - min) + min

	printf("This is salt: %s\n", this_salt);

	after_crypt = (char *)calloc((sizeof(simple) / sizeof(char *)), sizeof(char));

	after_crypt = crypt(simple, this_salt);

	printf("This is old string: %s\n"
		   "This is new string: %s\n", simple, after_crypt);
	
//	free(after_crypt);
	return(0);
}

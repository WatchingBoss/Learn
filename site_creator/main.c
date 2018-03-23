#include <stdio.h>
#include <sys/stat.h>
#include "template.h"


void indexCreate()
{
    FILE *index = fopen("site/index.html", "w");

    fprintf(index, "<!DOCTYPE html>\n");
    fprintf(index, "<html lang=\'ru\'>\n");
    fprintf(index, "<head>\n");
    fprintf(index, "\t<meta charset=\"UTF-8\">\n");
    fprintf(index, "\t<title>%s\t</title>\n", titleC());
    fprintf(index, "\t<link rel=\"srylesheet\" href=\"main.css\">\n");
    fprintf(index, "</head>\n");
    fprintf(index, "<body>\n");
    fprintf(index, "\t<header>\n");
    fprintf(index, "\t\t<h1>%s\t\t</h1>\n", header1());
    fprintf(index, "\t\t<h2>%s\t\t</h2>\n", header2());

    puts("Do you want to print text to tag p? Y/N");
    if (fgetc(stdin) == 'y' || fgetc(stdin) == 'Y')
    {
        fprintf(index, "\t\t<p>%s\t\t</p>\n", paragraphC());
    }

    fprintf(index, "\t</header>\n");
    fprintf(index, "</body>\n");
    fprintf(index, "</html>\n");

    fclose(index);
}

int main() {
    mkdir("site", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    indexCreate();

    return 0;
}
//
// Created by ubu on 2/7/18.
//

#ifndef SITE_CREATOR_TEMPLATE_H
#define SITE_CREATOR_TEMPLATE_H

char title[20], h1[80], h2[130], paragraph[255];


char *titleC()
{
    puts("Prompt title for you site\'s tab");
    fgets(title, sizeof(title), stdin);
    return title;
}

char *header1()
{
    puts("Prompt h1 for you page");
    fgetc(stdin);
    fgets(h1, sizeof(h1), stdin);
    return h1;
}

char *header2()
{
    puts("Prompt h2");
    fgetc(stdin);
    fgets(h2, sizeof(h2), stdin);
    return h2;
}

char *paragraphC()
{
    puts("Prompt text for tag p");
    fgetc(stdin);
    fgets(paragraph, sizeof(paragraph), stdin);
    return paragraph;
}


#endif //SITE_CREATOR_TEMPLATE_H

/* Some part of the code is NOT directly written by me.
Copyright © 2001 by Pradeep Padala.
https://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/html_single/NCURSES-Programming-HOWTO.html#COPYRIGHT
*/

#include <stdio.h>
#include <ncurses.h>
#include <string.h>
// #include <curses.h>
#include <stdlib.h>
#include <menu.h>
#include <panel.h>

#include <form_functions.h>

// char menu_items_[100][100] = {
//     {"Choice 1"},
//     {"Choice 2"},
//     {"license"},
//     {"Choice 4"},
//     {"Exit"},
// };
// ======================

int main()
{
    initscr();
    start_color();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    /* check if terminal supports color */
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color.\n Bye bye.\n");
        exit(1);
    }

    start_color();

    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);

    menu_();

    endwin();
    return 0;
}
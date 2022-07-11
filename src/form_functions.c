/*
====================
NOTE: Some part of the code is NOT directly written by me.
Copyright © 2001 by Pradeep Padala.
For these part, I'll use "LEARNED" in the comment. Which means I have learned this from:
https://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/html_single/NCURSES-Programming-HOWTO.html#COPYRIGHT
====================

*/

#include <stdio.h>
#include <stdlib.h>
#include <menu.h>
#include <ncurses.h>
#include <string.h>
#include <string.h>
#include <form_functions.h>

char *menu_items_[] = {
    "Nothing...",
    "Nothing...",
    "license",
    "Privacy Policy",
    "Exit",
    (char *)NULL,
};

void menu_()
{
    clear();
    attron(COLOR_PAIR(CYAN));
    mvprintw(LINES - 3, 2, "Use arrow keys to change the choice and press Enter to select!");
    refresh();
    attroff(COLOR_PAIR(CYAN));
    ITEM **items_;
    int c;
    MENU *menu_;
    WINDOW *menu_win;
    int n_choices, i;

    // Create items
    n_choices = 6;
    items_ = (ITEM **)calloc(n_choices, sizeof(ITEM *));
    for (i = 0; i < n_choices; ++i)
        items_[i] = new_item(menu_items_[i], NULL);

    // Crate menu
    menu_ = new_menu((ITEM **)items_);

    // menu items color
    set_menu_fore(menu_, COLOR_PAIR(CYAN) | A_REVERSE);
    set_menu_back(menu_, COLOR_PAIR(YELLOW));
    set_menu_grey(menu_, COLOR_PAIR(GREEN));

    // window cordinates and height and width
    int height = 5 + 6;
    int width = strlen(menu_items_[2]) + 32; // MAAAAXXXXX
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);

    // create main and sub windows
    set_menu_win(menu_, menu_win);
    set_menu_sub(menu_, derwin(menu_win, height - 4, width - 2, 3, 1));
    set_menu_mark(menu_, " -> ");

    /* LEARNED: Print a border around the main window and print a title */
    box(menu_win, 0, 0);
    print_in_middle(menu_win, 1, 0, width, "Menu", COLOR_PAIR(CYAN));
    mvwaddch(menu_win, 2, 0, ACS_LTEE);            // border line in the top left corner
    mvwhline(menu_win, 2, 1, ACS_HLINE, COLS - 5); // border line in the top
    mvwaddch(menu_win, 2, width - 1, ACS_RTEE);    // border line in the top right corner

    refresh();

    post_menu(menu_);
    wrefresh(menu_win);

    int cur_item;
    while ((c = wgetch(menu_win)) != ESC_KEY)
    {
        // c = wgetch(menu_win);
        switch (c)
        {
        case KEY_DOWN:
            menu_driver(menu_, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(menu_, REQ_UP_ITEM);
            break;
        case ENTER_KEY:
        {
            cur_item = item_index(current_item(menu_));
            switch (cur_item)
            {
            case 0:
                // item 1
                break;
            case 1:
                // item 2
                break;
            case 2:
                license(menu_win);
                break;
            case 3:
                privacyPolicy(menu_win);
                break;
            case 4:
                goto end;
                break;
            }
        }
        }
        wrefresh(menu_win);
    }
end:
    for (i = 0; i < n_choices; i++)
        free_item(items_[i]);
    delwin(menu_win);
    unpost_menu(menu_);
    free_menu(menu_);
    clear();
    refresh();
}

void license(WINDOW *menu_win)
{
    clear();
    refresh();
    // free software license
    char *text[] = {
        "Some of the code is not written by me. I have learned it from:",
        "https://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/html_",
        "single/NCURSES-Programming-HOWTO.html#COPYRIGHT",
        "Copyright © 2001 by Pradeep Padala.  (MIT License)",
        "For the rest of the code, I have used the following licenses:",
        "The MIT License (MIT)",

        "Copyright © 2022 <copyright holders>",

        "Permission is hereby granted, free of charge, to any person",
        "obtaining a copy of this software and associated documentation",
        "files (the \"Software\"), to deal in the Software without",
        "restriction, including without limitation the rights to use, copy,",
        "modify, merge, publish, distribute, sublicense, and/or sell copies",
        "of the Software, and to permit persons to whom the Software is furnished",
        "to do so, subject to the following conditions:",

        "The above copyright notice and this permission notice shall be included",
        "in all copies or, substantial portions of the Software. THE SOFTWARE IS",
        "PROVIDED \"AS IS\", WITHOUT WARRANTY, OF ANY KIND, EXPRESS OR IMPLIED",
        "INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS",
        "FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL",
        "THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR",
        "OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,",
        "ARISING FROM, OUT OF OR IN CONNECTION , WITH THE SOFTWARE OR THE USE",
        "OR OTHER DEALINGS IN THE SOFTWARE. You can find the full license at:",
        "https://mit-license.org/",
        (char *)NULL,
    };

    int height = ARRAY_SIZE(text) + 5;
    int width = strlen("https://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/html_") + 20; // MAAAAXXXXX
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW *win = newwin(height, width, starty, startx);
    attron(COLOR_PAIR(YELLOW));
    box(win, 0, 0);
    attroff(COLOR_PAIR(YELLOW));

    wattron(win, COLOR_PAIR(CYAN));
    // mvwprintw(win, 1, 1, "%s", text);
    for (int i = 0; *(text + i); i++)
    {
        mvwprintw(win, i + 1, 5, "%s", *(text + i));
    }

    wattroff(win, COLOR_PAIR(CYAN));
    wrefresh(win);

    attron(COLOR_PAIR(CYAN) | A_REVERSE);
    mvprintw(LINES - 2, 0, "Press any key to continue");
    attroff(COLOR_PAIR(CYAN) | A_REVERSE);
    refresh();
    getch();
    delwin(win);
    clear();
    /* LEARNED: Print a border around the main window and print a title */
    box(menu_win, 0, 0);
    print_in_middle(menu_win, 1, 0, width, "Menu", COLOR_PAIR(CYAN));
    mvwaddch(menu_win, 2, 0, ACS_LTEE);            // border line in the top left corner
    mvwhline(menu_win, 2, 1, ACS_HLINE, COLS - 5); // border line in the top
    mvwaddch(menu_win, 2, width - 1, ACS_RTEE);    // border line in the top right corner

    // refresh();
    refresh();
    // menu_();
}

void privacyPolicy(WINDOW *menu_win)
{
    clear();
    refresh();
    char *text[] = {
        "No information is collected by me. Literally no infromation!",
        "No personal, no non-personal!",
        (char *)NULL,
    };
    int height = ARRAY_SIZE(text) + 5;
    int width = strlen("No information is collected by me. Literally no infromation!") + 20; // MAAAAXXXXX
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW *win = newwin(height, width, starty, startx);
    attron(COLOR_PAIR(YELLOW));
    box(win, 0, 0);
    attroff(COLOR_PAIR(YELLOW));

    wattron(win, COLOR_PAIR(CYAN));
    // mvwprintw(win, 1, 1, "%s", text);
    for (int i = 0; *(text + i); i++)
    {
        mvwprintw(win, i + 1, 5, "%s", *(text + i));
    }

    wattroff(win, COLOR_PAIR(CYAN));
    wrefresh(win);

    attron(COLOR_PAIR(CYAN) | A_REVERSE);
    mvprintw(LINES - 2, 0, "Press any key to continue");
    attroff(COLOR_PAIR(CYAN) | A_REVERSE);

    refresh();
    getch();

    delwin(win);
    clear();
    /* LEARNED: Print a border around the main window and print a title */
    box(menu_win, 0, 0);
    print_in_middle(menu_win, 1, 0, width, "Menu", COLOR_PAIR(CYAN));
    mvwaddch(menu_win, 2, 0, ACS_LTEE);            // border line in the top left corner
    mvwhline(menu_win, 2, 1, ACS_HLINE, COLS - 5); // border line in the top
    mvwaddch(menu_win, 2, width - 1, ACS_RTEE);    // border line in the top right corner
    refresh();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
    /* LEARNED:
    This is not written by me. I got it from
    https://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/html_single/NCURSES-Programming-HOWTO.html#COPYRIGHT
    Copyright © 2001 by Pradeep Padala.
    */
    int length, x, y;
    float temp;

    if (win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    length = strlen(string);
    temp = (width - length) / 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}
/* Some part of the code is not directly written by me.
Copyright © 2001 by Pradeep Padala. */

#define CYAN 1
#define GREEN 2
#define YELLOW 3
#define MAGENTA 4
#define RED 5
#define WHITE 6
#define BLACK 7
#define ESC_KEY 27

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define CTRLD 4

extern char *menu_items_[];

void menu_();
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void license();

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


#define MAX_COL_LEN 35 //35
#define MAX_ROW_LEN 100 //100
#define ESC 27

int get_open(WINDOW *wnd, FILE *file);

int save_file(WINDOW *wnd, FILE *file);

int dectobit(WINDOW *wnd, int flags);

int editor(WINDOW *wnd, FILE *file);

int menu();
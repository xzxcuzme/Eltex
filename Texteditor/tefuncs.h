#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <fcntl.h>

#define MAX_COL_LEN 35 //35
#define MAX_ROW_LEN 100 //100

FILE *create_f();

FILE *open_f();

int editor(WINDOW *wnd, FILE *file);
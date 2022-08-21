#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "tefuncs.h"

void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
	nodelay(stdscr, 1);
	while (wgetch(stdscr) != ERR);
	nodelay(stdscr, 0); 
}

int main()
{
	enum GET {
		GET_OPEN=1,
		GET_CLOSE,
		GET_SAVE,
		GET_LEFT,
		GET_RIGHT,
		GET_EXIT
	};
	// extern void perror(), exit();
	initscr();

	signal(SIGWINCH, sig_winch);
	curs_set(0);
	start_color();
	move(0, 0);
	printw("F1 - save and exit  F2 - new file  F3 - open file\n");
	
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	WINDOW *wnd=NULL;
	//FILE *file=NULL;
	wnd = newwin(MAX_COL_LEN, MAX_ROW_LEN, 2, 2);
	if (!wnd)
	{
		printf("wnd error\n");	
		wprintw(wnd, "wnd error\n");
	}
	box(wnd, '|', '-');
	wbkgd(wnd, COLOR_PAIR(1));
	keypad(wnd, TRUE); //KEY_F1-KEY_F12, клавиши со стрелками – коды KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, а клавиша [BackSpace] – код KEY_BACKSPACE
	keypad(stdscr, TRUE);
	cbreak();

	idlok(wnd, TRUE);

	int ch = 0;
	ch = getch();
	switch(ch)
	{
		case KEY_F(2):
		{
			FILE *file = create_f();
			editor(wnd, file);

			break;
		}

		case KEY_F(3):
		{

			FILE *file = open_f();
			editor(wnd, file);
			break;
		}

		default: {
			break;
		}

		break;
	}
	
	

	//if (fclose(file) == EOF) wprintw(wnd, "error\n");

 	//delwin(wnd);
	curs_set(FALSE);
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS); 
} 


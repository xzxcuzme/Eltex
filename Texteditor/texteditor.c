#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_NAME_LEN 15

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
	WINDOW * wnd;
	char name[MAX_NAME_LEN + 1];
	while(1) 
	{
	
	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(TRUE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);

	wnd = newwin(35, 65, 2, 2);
	wbkgd(wnd, COLOR_PAIR(1));

	keypad(wnd, TRUE); //KEY_F1-KEY_F12, клавиши со стрелками – коды KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, а клавиша [BackSpace] – код KEY_BACKSPACE
	
	
	mousemask(BUTTON1_CLICKED, NULL);
	move(0,0);
	refresh();
	while (wgetch(wnd) == KEY_MOUSE) 
	{
		MEVENT event;
		getmouse(&event);
		move(0, 0);
		printw("Mouse button pressed at %i, %i\n", event.x, event.y);
		refresh();
		move(event.y, event.x);
	}

	wattron(wnd, A_BOLD);
	//wprintw(wnd, "Enter your name...\n");
	wgetnstr(wnd, name, MAX_NAME_LEN);
	//name[MAX_NAME_LEN] = 0;

	delwin(wnd);
	curs_set(FALSE);
	//move(8, 4);
	//printw("Press any key to continue...");
	refresh();
	getch();
	
	

	endwin();
	
	}
	exit(EXIT_SUCCESS);
} 


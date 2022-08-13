#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_COL_LEN 35
#define MAX_ROW_LEN 65

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
	FILE *fd;
	char name[MAX_ROW_LEN];
	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(TRUE);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	wnd = newwin(MAX_COL_LEN, MAX_ROW_LEN, 2, 2);
	box(wnd, '|', '-');
	wbkgd(wnd, COLOR_PAIR(1));
	while(1) 
	{
		keypad(wnd, TRUE); //KEY_F1-KEY_F12, клавиши со стрелками – коды KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, а клавиша [BackSpace] – код KEY_BACKSPACE
		
		// mousemask(BUTTON1_CLICKED, NULL);
		// wmove(wnd, 1, 1);
		// refresh();
		// while (wgetch(wnd) == KEY_MOUSE) 
		// {
		// 	MEVENT event;
		// 	getmouse(&event);
		// 	wmove(wnd, 1, 1);
		// 	wprintw(wnd, "Mouse button pressed at %i, %i\n", event.x-3, event.y-3);
		// 	refresh();
		// 	wmove(wnd, event.y-2, event.x-2);
		// }
		//for (int i = 1; i < MAX_COL_LEN-1; ++i)
		//{
			
		
			wmove(wnd, 1, 1);
			wgetnstr(wnd, name, MAX_ROW_LEN-2);
     	//}
         fd = fopen("./newfile.txt", "w");
         for (int l = 1; l < MAX_ROW_LEN; l++) {
           for (int i = 0; i < MAX_COL_LEN; i++)
           putc (mvinch (l, i) & A_CHARTEXT, fd);
           putc('\n', fd);
         }
         fclose(fd);

	delwin(wnd);
	curs_set(FALSE);
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
	}
} 


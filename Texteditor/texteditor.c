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
	printw("F1 - save and exit");
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
	WINDOW *wnd=NULL;
	FILE *file=NULL;
	wnd = newwin(MAX_COL_LEN, MAX_ROW_LEN, 2, 2);
	box(wnd, '|', '-');
	wbkgd(wnd, COLOR_PAIR(1));
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

	while(1) 
	{
		file = fopen("./file_output.txt_tmp", "w");
		char input[MAX_ROW_LEN];
		curs_set(TRUE);
		int ch;
		uint8_t flags;

		for (int i = 1; i < MAX_COL_LEN-1; ++i)
		{
			for (int j = 1; j < MAX_ROW_LEN-1; ++j)
			{
				flags = 0;
				//wmove(wnd, 10, 1);
				//wprintw(wnd, "Mouse button pressed at %i, %i\n", i, j);
				wmove(wnd, i, j);
				//dectobit(wnd, flags);
				ch = wgetch(wnd);
				fputc(ch, file);
				switch(ch)
				{
					case GET_OPEN:
					{
						get_open(wnd, file);
					}

					case '\n':
					{
						flags |= (1 << 0);
						break;
					}
					
					case KEY_F(1):
					{
						flags |= (1 << 1);
						break;
					}

					case KEY_LEFT:
					{	
						getyx(wnd, i, j);
						
						if(j > 0) 
						{
							wrefresh(wnd);
							wmove(wnd, i, j--);
							if(j == 0);
								else j--;
							continue;
						} else flash ();
					}

					case KEY_RIGHT:
					{	
						getyx(wnd, i, j);
						if(j == MAX_ROW_LEN-2) wmove(wnd, i, j--);
						if(j > 0) 
						{
							wrefresh(wnd);
							wmove(wnd, i, j);
							continue;
						} else flash ();
					}

					case KEY_UP:
					{	
						getyx(wnd, i, j);
						if(i > 0) 
						{
							wrefresh(wnd);
							wmove(wnd, i, j--);
							if(i == 1);
								else i--;
							continue;
						} else flash ();
					}

					case KEY_DOWN:
					{	
						getyx(wnd, i, j);
						if(i == MAX_COL_LEN-2) wmove(wnd, i--, j);
						if(i > 0) 
						{
							wrefresh(wnd);
							wmove(wnd, i, j--);
							
							i++;
							continue;
						} else flash ();
					}

					case KEY_DL:
					{	
						
					}

					case KEY_BACKSPACE:
					{
						getyx(wnd, i, j);
						if(j > 0) 
						{
							wdelch(wnd);
							mvwinsch (wnd, i, MAX_COL_LEN-1, ' ');
							//waddch(wnd, ' '); //
							wrefresh(wnd);
							wmove(wnd, i, j);
							j--;
							continue;
						} 
					}

					default:
					{
						
					}
				}
				if (flags & (1 << 0)) break;
				if (flags & (1 << 1))
				{
					if(1) rename("file_output.txt_tmp", "file_output.txt");
						else remove("file_output.txt_tmp");
					break;
				}
			}
			if (flags & (1 << 1)) break;
		}
		if (fclose(file) == EOF) wprintw(wnd, "error\n");
		break;
	}

 	delwin(wnd);
	curs_set(FALSE);
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS); 
} 


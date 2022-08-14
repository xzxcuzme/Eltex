#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>



#define MAX_COL_LEN 35
#define MAX_ROW_LEN 100

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
	FILE *file;
	enum GET {
		GET_OPEN=1,
		GET_CLOSE,
		GET_WRITE,
		GET_LEFT,
		GET_RIGHT,
		GET_EXIT
	};
		// char name[MAX_ROW_LEN];
		// extern void perror(), exit();
		// int i, n, l;
		// int c;
		// int line = 0;

	initscr();
	signal(SIGWINCH, sig_winch);
	curs_set(0);
	start_color();
	refresh();
	init_pair(1, COLOR_YELLOW, COLOR_BLUE);
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
		switch(3)
		{
			case GET_OPEN:
			{
				char input[MAX_ROW_LEN];
				char *estr;
				int i = 1;

				file = fopen("./newfile.txt", "r");
			 	if (file == NULL) wprintw(wnd, "error\n");
			 	
			 	while(1) 
			 	{
			 		wmove(wnd, i, 1);
			 		estr = fgets(input, sizeof(input), file);
			 		nodelay(wnd, TRUE);
					if (estr == NULL)
					{
						if (feof(file) != 0)
						{  
							//wprintw(wnd, "\nЧтение файла закончено\n");
							break;
						}
						else
						{
							//wprintw(wnd, "\nОшибка чтения из файла\n");
							break;
						}
					}
			 		waddstr(wnd, estr);
			 		wgetnstr(wnd, estr, sizeof(estr));
			 		++i;
				 }

				if (fclose(file) == EOF) wprintw(wnd, "error\n");
				//else wprintw(wnd, "close\n");
			}

			case 2:
			{

			}

			case GET_WRITE:
			{
				file = fopen("./newfile1.txt", "w");
				char input[MAX_ROW_LEN];
				curs_set(TRUE);
				int y = 1;
				for (int i = 1; i < MAX_COL_LEN-1; ++i)
				{
					
					wmove(wnd, i, y);
					wgetnstr(wnd, input, MAX_ROW_LEN-2);
					if (y>=2) y=1;
					fputs (input, file);
					fputc('\n', file);
					wmove(wnd, i+1, 1);
					if (wgetch(wnd) == KEY_F(1)) 
					{
						if (fclose(file) == EOF) wprintw(wnd, "error\n");
						//nodelay(wnd, TRUE); 
						break;
					} else 
					{
						y=y+2;
						fputc(wgetch(wnd), file);
					}
					
		     	}
			}

		}
     	break;
	}

 	delwin(wnd);
	curs_set(FALSE);
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS); 
} 


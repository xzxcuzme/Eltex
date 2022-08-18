#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


#define MAX_COL_LEN 35
#define MAX_ROW_LEN 100
#define ESC 27

int get_open(WINDOW *wnd, FILE *file)
{
	curs_set(TRUE);
	char input[MAX_ROW_LEN];
	char *estr;
	int i = 1;

	file = fopen("./file_input.txt", "r");
 	if (file == NULL) wprintw(wnd, "error\n");
 	
 	while(1) 
 	{
 		wmove(wnd, i, 1);
 		estr = fgets(input, sizeof(input), file);
 		nodelay(wnd, TRUE);
		if (estr == NULL) break;
 		waddstr(wnd, estr);
 		wgetnstr(wnd, estr, sizeof(estr));
 		++i;
	 }

	if (fclose(file) == EOF) wprintw(wnd, "error\n");
	//else wprintw(wnd, "close\n");

}

int save_file(WINDOW *wnd, FILE *file)
{
	if(1) rename("file_output.txt_tmp", "file_output.txt");
		else remove("file_output.txt_tmp");		
	if (fclose(file) == EOF) wprintw(wnd, "error\n");
	return 1;
}

int dectobit(WINDOW *wnd, int flags) {
	for (int i = 0; i < 16; i++) 
		{
			wprintw(wnd, "%c", (flags & 0x80) ? '1' : '0');
			flags <<= 1;
		}
	return 1;
}

int editor(WINDOW *wnd, FILE *file) {
	file = fopen("./file_output.txt_tmp", "w");
	curs_set(TRUE);
	int ch;
	uint8_t flags;
	for (int i = 1; i < MAX_COL_LEN-1; ++i)
	{
		for (int j = 1; j < MAX_ROW_LEN-1; ++j)
		{
			flags = 0;
			wmove(wnd, i, j);
			//dectobit(wnd, flags);
			ch = wgetch(wnd);
			fputc(ch, file);
			switch(ch)
			{
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
				save_file(wnd, file);
				break;
			}
		}
		if (flags & (1 << 1)) break;
	}
}

int menu() {
	const char items[3][10] = {
	    "New file", 
	    "Open file",
	    "Exit"
	};
    initscr();

    unsigned choice = 0;

    curs_set(0); 
    keypad(stdscr, true); 
}
//     while (1)
//     {
//         clear();
//         for (unsigned i = 0; i < sizeof(items)/sizeof(items[i]); i++) 
//         {
//             if (i == choice) addch('>'); 
//             	else addch(' '); 
//             printw("%s\n", items[i]);
//         }
//         switch (getch())
//         {
//             case KEY_UP:
//             {
//                 if (choice) choice--; 
//                 break;
//             }
//             case KEY_DOWN:
//                 if (choice != sizeof(items)/sizeof(items[3])-1) choice++;
//                 break;
//         }
//     }
//     endwin();
//     return 1;
// }
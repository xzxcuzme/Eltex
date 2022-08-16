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
	return 1;
}

int save_file(WINDOW *wnd, FILE *file)
{
	file = fopen("./file_output.txt_tmp", "w");
	char input[MAX_ROW_LEN];
	curs_set(TRUE);
	int y = 1;
	int ch;
	
	for (int i = 1; i < MAX_COL_LEN-1; ++i)
	{
		for (int j = 1; j < MAX_ROW_LEN-1; ++j)
		{
			wmove(wnd, i, j);
			ch = wgetch(wnd);
			fputc(ch, file);
			if (ch == KEY_F(1)) 
			{
				if(1) rename("file_output.txt_tmp", "file_output.txt");
					else remove("file_output.txt_tmp");
				
				return 0; 
			} 
			if (ch == '\n') 
			{
				break;
			}
		}
	}
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
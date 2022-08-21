#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_COL_LEN 35
#define MAX_ROW_LEN 100
#define LINE_FEED '\n'

#define HERE_I_AM() wprintw(wnd, "LINE %d\n", __LINE__) //строчка для отладки

FILE *create_f()
{
    WINDOW *w_name;
    FILE *inputfile=NULL;
    int x,y;
    x=getmaxx(stdscr);
    y=getmaxy(stdscr);
    char name[x];
    w_name=newwin(5,60,(y/2-2),(x/2-30));//создаём новое окно по середине активного окна
    curs_set(TRUE);//включаем курсор
    echo();//выводить набираемые символы
    box(w_name,0,0);//создаём рамку по границе окна
    wmove(w_name,1,1);
    wattron(w_name,A_BOLD);
    wprintw(w_name, "Enter path end name:");//приглашение к вводу данных
    wmove(w_name,2,1);
    wgetnstr(w_name, name, y);//получение строки с путём к файлу и его именем.Максимальная длина-размер окна
    wrefresh(w_name);//обновляем для вывода на экран
    //file = fopen(name, "w");
    inputfile=fopen(name, "w+");//создаём файл
    /*В случае ошибке при создании файла выводим на экран сообщении и возвращаемся в главное меню*/
    if(inputfile==NULL) {
        wmove(w_name,2,1);
        wprintw(w_name,"Problem with file creating. Press any key");
        wrefresh(w_name);
        wgetch(w_name);
        wattroff(w_name,A_BOLD);
        delwin(w_name);
    }
    return inputfile;
}

FILE *open_f()
{
    WINDOW *w_name;
    FILE *inputfile=NULL;
    int x,y;
    x=getmaxx(stdscr);
    y=getmaxy(stdscr);
    char name[x];
    w_name=newwin(5,60,(y/2-2),(x/2-30));//создаём новое окно по середине активного окна
    curs_set(TRUE);//включаем курсор
    echo();//выводить набираемые символы
    box(w_name,0,0);//создаём рамку по границе окна
    wmove(w_name,1,1);
    wattron(w_name,A_BOLD);
    wprintw(w_name, "Enter path end name:");//приглашение к вводу данных
    wmove(w_name,2,1);
    wgetnstr(w_name, name, y);//получение строки с путём к файлу и его именем.Максимальная длина-размер окна
    wrefresh(w_name);//обновляем для вывода на экран
    //file = fopen(name, "w");
    inputfile=fopen(name, "r+");//создаём файл
    /*В случае ошибке при создании файла выводим на экран сообщении и возвращаемся в главное меню*/
    if(inputfile == NULL) {
        wmove(w_name,2,1);
        wprintw(w_name,"Problem with file opening. Press any key");
        wrefresh(w_name);
        wgetch(w_name);
        wattroff(w_name,A_BOLD);
        delwin(w_name);
    }
    return inputfile;
}

int editor(WINDOW *wnd, FILE *file) {
	//mousemask(BUTTON1_CLICKED, NULL);
	curs_set(TRUE);
	uint8_t flags;
	int x;
	char name[x];
	char estr[MAX_COL_LEN];
	char input[MAX_ROW_LEN];
	//file = fopen("./file_input.txt", "r+");
	if(!file)
	{
		wprintw(wnd, "FILE OPEN ERROR %p\n", file);
	}
	int read_string = 1;
	int read = 0;
	size_t len = 0;
	char *line = NULL;
	while ((read = getline(&line, &len, file)) != -1) //читаем файл по строчно
 	{
 		wmove(wnd, read_string, 1);
 		nodelay(wnd, TRUE);
 		waddstr(wnd, line);
		wgetnstr(wnd, line, len);
 		if(!read)
 		{	
 			wprintw(wnd, "END OF FILE\n");
			waddstr(wnd, "END OF FILE\n");
			wgetnstr(wnd, "END OF FILE\n", MAX_COL_LEN);
 			break;
 		}
		read_string++;
	} 

	for (int i = 1; i < MAX_COL_LEN-1; ++i) //обрабатываем нажатия пользователя, ограничиваясь размерами окна
	{
		for (int j = 1; j < MAX_ROW_LEN-1; ++j)
		{
	
			flags = 0;
			wmove(wnd, i, j);
			// while (wgetch(wnd) == KEY_MOUSE) 
			// {
			// 	MEVENT event;
			// 	getmouse(&event);
			// 	i=event.y-2;
			// 	j=event.x-2;
			// 	//wmove(wnd, event.y-2, event.x-2);
			// }
			
			nodelay(wnd, FALSE);
			int ch = 0;
			ch = wgetch(wnd);
			switch(ch)
			{
				case LINE_FEED:
				{
					flags |= (1 << 0); //флаг для обработки конца строки
					break;
				}
				
				case KEY_F(1):
				{
					nodelay(wnd, TRUE);
					flags |= (1 << 1); //
					break;
				}

				case KEY_LEFT:
				{	
					getyx(wnd, i, j);
					if(j > 0) 
					{
						wrefresh(wnd);
						wmove(wnd, i, j--);
						if(j == 0); //что бы не зайти за границу рамки
						else j--;
						continue;
					} 
					else 
					{
						flash();
					} 
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
					} 
					else
					{
						flash ();
					} 
				}

				case KEY_UP:
				{	
					getyx(wnd, i, j);
					if(i > 0) 
					{
						wrefresh(wnd);
						wmove(wnd, i, j--);
						if(i == 1); //что бы не зайти за границу рамки
						else i--;
						continue;
					} 
					else
					{
						flash ();
					} 
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
					} 
					else
					{
						flash ();
					} 
				}

				case KEY_DL:
				{	
					delch();
					break;
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
				case -1:
				{	
					break;
				}
				default:
				{
					fputc(ch, file); //wechochar()
					continue;
				}
			}
			if(flags & (1 << 0))
			{
				fputc(ch, file);
				break;
			} 
			if(flags & (1 << 1))
			{	
				//if(1) rename("file_output.txt_tmp", "file_output.txt"); 
					//else remove("file_output.txt_tmp");
				/*
				Хотел сделать временный файл, если пользователь сохраняет файл, 
				переименовываем в его имя. Если	не сохранять, то делитем tmp.
				Не могу получить имя из file.
				*/
				if(fclose(file) == EOF) wprintw(wnd, "error\n");
				break;
			}
		}
		if(flags & (1 << 1)) break;
	}
}
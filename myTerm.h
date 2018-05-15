#ifndef _GUARD_TERM_
#define _GUARD_TERM_

#define BGCOLOR "\E[4%dm"
#define FGCOLOR "\E[3%dm"
#define CLS "\E[H\E[J"
#define POS "\E[%d;%dH"
#define TERM "/dev/tty"

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

enum colors {
    DEFAULT = 9, BLACK = 0, WHITE = 7, GREEN = 2, RED = 1
    /*black,
	red,
	green,
	yellow,
	blue,
	pink,
	white,
    standart*/

};


int mt_clrscr();
int mt_gotoXY(int x,int y);
int mt_getscreensize(int *rows,int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);



#endif

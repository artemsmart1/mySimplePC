#include <fcntl.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "myBigChars.h"
#include "myTerm.h"
#include "my_sc.h"

int main()
{


	bc_printA("\E[H\E[J");
	sc_memoryInit();
	sc_regInit();
	printf("\n");
	sc_memoryPrint();
	sc_memoryPrint();
	mt_setfgcolor(BLUE);
	mt_setbgcolor(DEFAULT);
	bc_box(1, 1, 12, 78);
	mt_gotoXY(1, 35);
	mt_setfgcolor(DEFAULT);
	mt_setbgcolor(BLUE);
	printf(" Memory ");
	mt_gotoXY(13, 1);

	int big[2];
	bc_setBig(big, 'A');
	bc_printBigChar(big, 10, 10, GREEN, DEFAULT);
	bc_setBig(big, '1');
	bc_printBigChar(big, 10, 18, BLACK, DEFAULT);

	mt_setfgcolor(DEFAULT);
	mt_setbgcolor(DEFAULT);


	return 0;
}

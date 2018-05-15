#ifndef _BIG_CHARS_
#define _BIG_CHARS_

#define ENTER_MODE "\E(0"
#define EXIT_MODE "\E(B"

int bc_printA (char *);
int bc_box(int, int, int, int);
int bc_printBigChar(int *, int, int, enum colors, enum colors);
int bc_setBigCharPos(int *, int, int, int);
int bc_getBigCharPos(int *, int, int, int *);
int bc_bigCharWrite(int, int *, int);
int bc_bigCharRead(int, int *, int, int *);
void bc_setBig(int*, int);
#endif

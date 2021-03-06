#include <stdio.h>
#include <stdlib.h>

#include "my_sc.h"
#include "myTerm.h"
#include "myBigChars.h"

int bc_printA (char *str)
{
	printf(ENTER_MODE);
	printf(str);
	printf(EXIT_MODE);

	return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
	int i;
	mt_gotoXY(x1, y1);
	bc_printA("l");

	for (i = 0; i < y2 - 2; i++)
	{
		bc_printA("q");
	}

	bc_printA("k");

	for (i = 1; i <= x2 - 2; i++)
	{
		mt_gotoXY(x1 + i, y1);
		bc_printA("x");
		mt_gotoXY(x1 + i, y1 + y2 - 1);
		bc_printA("x");
	}

	mt_gotoXY(x1 + x2 - 1, y1);
	bc_printA("m");

	for (i = 0; i < y2 - 2; i++)
	{
		bc_printA("q");
	}

	bc_printA("j");

	return 0;
}

int bc_printBigChar(int big[2], int x, int y, enum colors fgColor, enum colors bgColor)
{
	int buffer;
	int bitBuffer;
	int BigBuffer;
	char str[8] = {0};
	//mt_gotoXY(x, y);
	mt_setfgcolor(fgColor);
	mt_setbgcolor(bgColor);

	int i, j, k;

	for (i = 0; i < 2; i++)
	{
		BigBuffer = big[i];
		for (j = 0; j < 4; j++)
		{
			BigBuffer = big[i] >> (j * 8);
			buffer = BigBuffer & 255;

			for (k = 0; k < 8; k++)
			{
				bitBuffer = (buffer & (1 << k)) >> k;
				if (bitBuffer == 1)
				{
					str[k] = 'a';
				}
				else
				{
					str[k] = ' ';
				}
				mt_gotoXY(x + (i * 4) + j, y);
				bc_printA(str);
			}
		}
	}

	mt_gotoXY(25, 1);

	return 0;
}

int bc_setBigCharPos(int *big, int x, int y, int value)
{

	if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0)
	{
		return -1;
	}

	int index = 0;

	if (x > 3)
	{
		index = 1;
	}

	if (value == 1)
	{
		big[index] |= 1 << (x * 8 + y);
	}
	else
	{
		if (value == 0)
		{
			big[index] &= ~(1 << (x * 8 + y));
		}
	}

	return 0;
}

int bc_getBigCharPos(int *big, int x, int y, int *value)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
	{
		return -1;
	}

	int index = 0;

	if (x > 3)
	{
		index = 1;
	}

	*value = ((big[index] >> (x * 8)) >> y) & 1;

	return 0;
}

int bc_bigCharWrite(int fd, int *big, int count)
{
	int result;

	while (count > 0)
	{
		if ((result = write(fd, big, sizeof(int) * 2)) == -1)
		{
			return -1;
		}
		count--;
	}

	return 0;
}

int bc_bigCharRead(int fd, int *big, int need_count, int *count)
{
	while (need_count > 0)
	{
		int result;
		if ((result = read(fd, big, sizeof(int) * 2)) == -1)
		{
			return -1;
		}
		need_count--;
		*count = *count + 1;
	}

	return 0;
}

void bc_setBig(int *big, int value)
{
	switch (value) {
				case '-':
						big[0] = 4278190080;
						big[1] = 0;
						break;
        case '+':
            big[0] = 4279769088;
            big[1] = 6168;
            break;
        case '0':
						big[0] = 2172748287;
						big[1] = 4286677377;
            break;
        case '1':
						big[0] = 3235442912;
            big[1] = 3233857728;
            break;
        case '2':
            big[0] = 4290822399;
            big[1] = 4278387459;
            break;
        case '3':
            big[0] = 4290822399;
            big[1] = 4290822336;
            break;
        case '4':
            big[0] = 4291019715;
            big[1] = 3233857728;
            break;
        case '5':
            big[0] = 4278387711;
            big[1] = 4290822336;
            break;
        case '6':
            big[0] = 4278387711;
            big[1] = 4291019715;
            break;
        case '7':
            big[0] = 3233857791;
            big[1] = 3233857728;
            break;
        case '8':
            big[0] = 4291019775;
            big[1] = 4291019715;
            break;
        case '9':
            big[0] = 4291019775;
            big[1] = 4290822336;
            break;
        case 'A':
            big[0] = -8289793;
            big[1] = -2122219135;
            break;
        case 'B':
            big[0] = -14606017;
            big[1] = -8286847;
            break;
        case 'C':
            big[0] = 16843516;
            big[1] = -66977535;
            break;
        case 'D':
            big[0] = -1925111521;
            big[1] = 522273153;
            break;
        case 'E':
            big[0] = 1057030655;
            big[1] = -16711423;
            break;
        case 'F':
            big[0] = 1057030655;
            big[1] = 16843009;
            break;
        default:
            big[0] = 0;
            big[1] = 0;
            break;
    }
}

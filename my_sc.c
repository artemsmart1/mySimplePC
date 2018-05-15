#include "my_sc.h"
#include "myTerm.h"

int sc_memoryInit()
{
	for (int i=0;i<SIZE;i++)
		Memory[i]=0;

	int cache[] = {10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 59, 60,
		61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76};
	memcpy(cmd_arr, cache, sizeof(cache));

	memoryPointer = 0;

	return 0;
}

int sc_memorySet(int address,int value)
{
	if ((address>=0) && (address<SIZE))
	{
		Memory[address]=value;
		return 0;
	}
	else
	{
		mt_gotoXY(24, 1);
		flag = EXITOFMEM;
		printf("Выход за границы памяти\nError: %8.0i", flag);
		return 0;
	}

}

int sc_memoryGet(int address,int *value)
{
	if ((address>=0) && (address<SIZE))
	{
		*value=Memory[address];
		return 0;
	}
	else
	{
		mt_gotoXY(24, 1);
		flag = EXITOFMEM;
		printf("Выход за границы памяти\nError: %8.0i\n\n", flag);
		return 0;
	}
}

int sc_memoryPrint()
{
	for (int i = 0; i < 10; i++)
	{
		printf(" ");
		for (int j = 0; j < 10; j++){
			printf("+%.4d\t",Memory[(10 * i) + j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int sc_memorySave(char *filename)
{
	FILE *f;
	f=fopen(filename, "wb");

	int temp;

	if (f==NULL)
		return -1;

	temp=fwrite(Memory,sizeof(*Memory)*SIZE,1,f);
	fclose(f);

	if (temp!=1)
		return -1;
	else
		return 0;
}

int sc_memoryLoad(char *filename)
{
	FILE *f;

	int k;

	f=fopen(filename,"rb");
	if (f == NULL)
		return -1;

	k=fread(Memory,sizeof(*Memory)*SIZE,1,f);

	fclose(f);
	if (k!=1)
		return -1;
	else
		return 0;
}

int sc_regInit()
{
	reg_flags=0;
	return 0;
}

int sc_regSet(int reg,int value)
{
	if (reg>0)
	{
		if (value==1)
		{
			reg_flags = reg;
		}
		else if (value==0)
		{
			reg_flags = reg;
		}
		else
		{
			mt_gotoXY(24, 1);
			flag = ERRREGVALUE;
			printf("Недопустимое значение регистра\nError: %8.0i\n", flag);
			return 0;
		}
	}
	else
	{
		mt_gotoXY(24, 1);
		flag = ERRREGNUM;
		printf("Недопустимый номер регистра\nError: %8.0i\n", flag);
	}
	return 0;
}

int sc_regGet(int reg,int *value)
{
	if (reg>0)
	{
		*value = reg_flags;
		return 0;
	}
	else
	{
		mt_gotoXY(24, 1);
		flag = ERRREGNUM;
		printf("Недопустимый номер регистра\nError: %8.0i\n", flag);
		return 0;
	}
}

int compare(const void *a,const void *b)
{
	if (*(int*)a < *(int*)b)
		return -1;
	else if (*(int*)a > *(int*)b)
		return 1;
	else
		return 0;
}

int sc_commandEncode(int command,int operand,int *value)
{
	printf("\nEncode\n");
	int trig = 0;
	for (int i = 0; i < cmd_num; i++)
	{
		if (command == cmd_arr[i])
		{
			trig = 1;
			break;
		}
	}

	if (trig == 1)
	{
		*value=(command<<7)|operand;
		return 0;
	}
	else
	{
		mt_gotoXY(24, 1);
		flag = ERRCOMMAND;
		printf("Ошибочная команда\nError: %8.0i\n", flag);
		return 0;
	}

}

int sc_commandDecode(int value,int *command,int *operand)
{
	printf("\nDecode\n");
	int temp, temp_cmd, temp_oper, trig = 0;
	//&a = command;

	temp=(value>>14)&1;
	if (temp==0)
	{
		temp_cmd=(value>>7) & 0x7F;
		temp_oper=value & 0x7F;

		for (int i = 0; i < cmd_num; i++)
		{
			if (*command == cmd_arr[i])
			{
				trig = 1;
				break;
			}
		}

		if (trig == 1)
		{
			*command=temp_cmd;
			*operand=temp_oper;
		}
		else
		{
			mt_gotoXY(24, 1);
			flag = ERRCOMMAND;
			printf("Ошибочная команда\nError: %8.0i\n", flag);
			return 0;
		}
	}
		return 0;
}

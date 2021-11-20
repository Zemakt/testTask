#include "Header.h"
using namespace std;

int LFSR_Fibonacci1(unsigned short*);
int LFSR_Fibonacci2(unsigned int*);
int LFSR_Fibonacci3(unsigned int*);
int LFSR_Fibonacci4(unsigned char*);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char msg[0xff] = { '\0' };
	printf("Введите строку для шифрования: \n");
	gets_s(msg);

	printf("Введите начальное значение регистров:\n");
	static unsigned short r1;
	scanf("%hx", &r1);
	printf("Регистр 1 = %u бит\n", r1);

	static unsigned int r2;
	scanf("%x", &r2);
	printf("Регистр 2 = %u бит\n", r2);

	static unsigned int r3;
	scanf("%x", &r3);
	printf("Регистр 3 = %u бит\n", r3);

	static unsigned char r4;
	scanf("%hhx", &r4);
	printf("Регистр 4 = %u бит\n", r4);
	unsigned int key = LFSR_Fibonacci1(&r1) ^ LFSR_Fibonacci2(&r2) ^ LFSR_Fibonacci3(&r3) ^ LFSR_Fibonacci4(&r4) ^ 1;
	printf("\nKEY = %x\n", key);
	int N = strlen(msg);
	printf("\nТекст который необходимо зашифровать\n");
	printf("%s",msg);

	for (int i = 0; i < N; i++)
	{
		msg[i] ^= key;

	}
	printf("\nЗашифрованный текст\n");

	for (int i = 0; i < N; i++)
	{
		printf("0x%x ",msg[i]);
		
	}

	for (int i = 0; i < N; i++)
	{
		msg[i] ^= key;
	}

	printf("\nРасшифрованный текст\n");

	for (int i = 0; i < N; i++)
	{
		 cout << msg[i];
	}

	return 0;
}

int LFSR_Fibonacci1(unsigned short* r1)
{

	*r1 = ((((*r1 >> 11) ^ (*r1 >> 10) ^ (*r1 >> 9) ^ (*r1 >> 3) ^ *r1) & 0x1) << 11) | (*r1 >> 1);
	return *r1 & 0x1;
}
int LFSR_Fibonacci2(unsigned int* r2)
{

	*r2 = ((((*r2 >> 18) ^ (*r2 >> 17) ^ (*r2 >> 16) ^ (*r2 >> 13) ^ *r2) & 0x1) << 18) | (*r2 >> 1);
	return *r2 & 0x1;
}
int LFSR_Fibonacci3(unsigned int* r3)
{

	*r3 = ((((*r3 >> 16) ^ (*r3 >> 13) ^ *r3) & 0x1) << 16) | (*r3 >> 1);
	return *r3 & 0x1;
}
int LFSR_Fibonacci4(unsigned char* r4)
{

	*r4 = ((((*r4 >> 7) ^ (*r4 >> 5) ^ (*r4 >> 4) ^ *r4) & 0x1) << 7) | (*r4 >> 1);
	return *r4 & 0x1;
}


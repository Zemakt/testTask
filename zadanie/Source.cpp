#include "Header.h"
using namespace std;
int LFSR_Fibonacci1(unsigned short*);
int LFSR_Fibonacci2(unsigned int*);
int LFSR_Fibonacci3(unsigned int*);
int LFSR_Fibonacci4(unsigned char*);
int GetKey(unsigned short* r1, unsigned int* r2, unsigned int* r3, unsigned char* r4);
int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("Введите строку для шифрования: \n");
	char* msg = new char[256];
	char* msg_secret = new char[256]{ '\0' };
	char* shifr = new char[256]{ '\0' };
	char* unshifr = new char[256];
	char* ms = new char[256];
	gets_s(msg, 256);
	unsigned short r1 = atoi(argv[1]);
	printf("\n%hd\n", r1);
	unsigned int r2 = atoi(argv[2]);
	printf("%d\n", r2);
	unsigned int r3 = atoi(argv[3]);
	printf("%d\n", r3);
	unsigned char r4 = atoi(argv[4]);
	printf("%hhd\n", r4);

	printf("\nKEY = %x\n", GetKey(&r1, &r2, &r3, &r4));
	printf("\nТекст который необходимо зашифровать\n");
	printf("%s", msg);
	printf("\nЗашифрованный текст\n");
	for (unsigned int i = 0; i < strlen(msg); i++)
	{
		// std::cout << std::bitset<sizeof(msg[i])* CHAR_BIT>(msg[i]) << "\n";
		char mask1 = (GetKey(&r1, &r2, &r3, &r4));
		char mask2 = (GetKey(&r1, &r2, &r3, &r4) << 1);
		char mask3 = (GetKey(&r1, &r2, &r3, &r4) << 2);
		char mask4 = (GetKey(&r1, &r2, &r3, &r4) << 3);
		char mask5 = (GetKey(&r1, &r2, &r3, &r4) << 4);
		char mask6 = (GetKey(&r1, &r2, &r3, &r4) << 5);
		char mask7 = (GetKey(&r1, &r2, &r3, &r4) << 6);
		char mask8 = (GetKey(&r1, &r2, &r3, &r4) << 7);
		msg_secret[i] = ((msg[i] ^ mask1) & 0x1) +
			((msg[i] ^ mask2) & 0x2) +
			((msg[i] ^ mask3) & 0x4) +
			((msg[i] ^ mask4) & 0x8) +
			((msg[i] ^ mask5) & 0x10) +
			((msg[i] ^ mask6) & 0x20) +
			((msg[i] ^ mask7) & 0x40) +
			((msg[i] ^ mask8) & 0x80);
		shifr[i] = msg_secret[i] ^ msg[i];
		cout << shifr[i];

		// std::cout << std::bitset<sizeof(shifr[i])* CHAR_BIT>(shifr[i]) << "\n";
	}
	printf("\nРасшифрованный текст\n");
	for (unsigned int j = 0; j < strlen(shifr); j++)
	{
		char mask1 = (GetKey(&r1, &r2, &r3, &r4));
		char mask2 = (GetKey(&r1, &r2, &r3, &r4) << 1);
		char mask3 = (GetKey(&r1, &r2, &r3, &r4) << 2);
		char mask4 = (GetKey(&r1, &r2, &r3, &r4) << 3);
		char mask5 = (GetKey(&r1, &r2, &r3, &r4) << 4);
		char mask6 = (GetKey(&r1, &r2, &r3, &r4) << 5);
		char mask7 = (GetKey(&r1, &r2, &r3, &r4) << 6);
		char mask8 = (GetKey(&r1, &r2, &r3, &r4) << 7);
		unshifr[j] = ((shifr[j] ^ mask1) & 0x80) +
			((shifr[j] ^ mask2) & 0x40) +
			((shifr[j] ^ mask3) & 0x20) +
			((shifr[j] ^ mask4) & 0x10) +
			((shifr[j] ^ mask5) & 0x8) +
			((shifr[j] ^ mask6) & 0x4) +
			((shifr[j] ^ mask7) & 0x2) +
			((shifr[j] ^ mask8) & 0x1);
		ms[j] = msg_secret[j] ^ unshifr[j];

		cout << ms[j];
		// std::cout << std::bitset<sizeof(ms[j])* CHAR_BIT>(ms[j]) << "\n";
	}
	delete[] msg;
	delete[] msg_secret;
	delete[] shifr;
	delete[] unshifr;
	delete[] ms;
	return 0;
}
int GetKey(unsigned short* r1, unsigned int* r2, unsigned int* r3, unsigned char* r4)
{
	unsigned int key = LFSR_Fibonacci1(r1) ^ LFSR_Fibonacci2(r2) ^ LFSR_Fibonacci3(r3) ^ LFSR_Fibonacci4(r4) ^ 1;
	return key;
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


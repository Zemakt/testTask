#include "Header.h"
using namespace std;
int LFSR1(unsigned short*);
int LFSR2(unsigned int*);
int LFSR3(unsigned int*);
int LFSR4(unsigned char*);
void Encrypt(char* msg, char* msg_secret, char* shifr, unsigned short r1, unsigned int r2, unsigned int r3, unsigned char r4);
void Decrypt(char* shifr, char* msg_secret, char* ms, char* unshifr, unsigned short reg1, unsigned int reg2, unsigned int reg3, unsigned char reg4);
int Key(unsigned short* reg1, unsigned int* reg2, unsigned int* reg3, unsigned char* reg4);
void msgsize(char size, char* msg);
void secretsize(char size, char* msg_secret);
void unshifrsize(char size, char* unshifr);
void shifrsize(char size, char* shifr);
void mssize(char size, char* ms);
int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    int size = 255;
	char* msg = new char[size];
	printf("Введите строку для шифрования: \n");
	char* msg_secret = new char[size];
	char* shifr = new char[size];
	char* unshifr = new char[size];
	char* ms = new char[size];
	cin >> msg;
	unsigned short reg1 = atoi(argv[1]);
	unsigned int reg2 = atoi(argv[2]);
	unsigned int reg3 = atoi(argv[3]);
	unsigned char reg4 = atoi(argv[4]);
	printf("\nСообщение которое необходимо зашифровать\n");
	cout << msg;
	Encrypt(msg, msg_secret, shifr, reg1, reg2, reg3, reg4);
	Decrypt(shifr, msg_secret, ms, unshifr, reg1, reg2, reg3, reg4);

	return 0;
}


void msgsize(char size,char *msg) 
{
	char newSize = size * 2;
	char* newmsg = new char[newSize];

	memcpy(newmsg, msg, size * sizeof(char));

	size = newSize;
	delete[] msg;
	msg = newmsg;
}
void shifrsize(char size, char* shifr)
{
	char newSize = size * 2;
	char* newshifr = new char[newSize];

	memcpy(newshifr, shifr, size * sizeof(char));

	size = newSize;
	delete[] shifr;
	shifr = newshifr;
}
void unshifrsize(char size, char* unshifr)
{
	char newSize = size * 2;
	char* newunshifr = new char[newSize];

	memcpy(newunshifr, unshifr, size * sizeof(char));

	size = newSize;
	delete[] unshifr;
	unshifr = newunshifr;
}
void secretsize(char size, char* msg_secret)
{
	char newSize = size * 2;
	char* newsecret = new char[newSize];

	memcpy(newsecret, msg_secret, size * sizeof(char));

	size = newSize;
	delete[] msg_secret;
	msg_secret = newsecret;
}
void mssize(char size, char* ms)
{
	char newSize = size * 2;
	char* newms = new char[newSize];

	memcpy(newms, ms, size * sizeof(char));

	size = newSize;
	delete[] ms;
	ms = newms;
}
void Encrypt(char* msg, char* msg_secret, char* shifr, unsigned short reg1, unsigned int reg2, unsigned int reg3, unsigned char reg4)
{
	printf("\nЗашифрованное сообщение\n");
	for (size_t i = 0; i < strlen(msg); i++)
	{
		char mask1 = (Key(&reg1, &reg2, &reg3, &reg4));
		char mask2 = (Key(&reg1, &reg2, &reg3, &reg4) << 1);
		char mask3 = (Key(&reg1, &reg2, &reg3, &reg4) << 2);
		char mask4 = (Key(&reg1, &reg2, &reg3, &reg4) << 3);
		char mask5 = (Key(&reg1, &reg2, &reg3, &reg4) << 4);
		char mask6 = (Key(&reg1, &reg2, &reg3, &reg4) << 5);
		char mask7 = (Key(&reg1, &reg2, &reg3, &reg4) << 6);
		char mask8 = (Key(&reg1, &reg2, &reg3, &reg4) << 7);
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
	}
}
void Decrypt(char* shifr, char* msg_secret, char* ms, char* unshifr, unsigned short reg1, unsigned int reg2, unsigned int reg3, unsigned char reg4)
{
	printf("\nРасшифрованное сообщение\n");
	for (size_t j = 0; j < strlen(shifr); j++)
	{
		char mask1 = (Key(&reg1, &reg2, &reg3, &reg4));
		char mask2 = (Key(&reg1, &reg2, &reg3, &reg4) << 1);
		char mask3 = (Key(&reg1, &reg2, &reg3, &reg4) << 2);
		char mask4 = (Key(&reg1, &reg2, &reg3, &reg4) << 3);
		char mask5 = (Key(&reg1, &reg2, &reg3, &reg4) << 4);
		char mask6 = (Key(&reg1, &reg2, &reg3, &reg4) << 5);
		char mask7 = (Key(&reg1, &reg2, &reg3, &reg4) << 6);
		char mask8 = (Key(&reg1, &reg2, &reg3, &reg4) << 7);
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
	}
}
int Key(unsigned short* reg1, unsigned int* reg2, unsigned int* reg3, unsigned char* reg4)
{
	unsigned int key = LFSR1(reg1) ^ LFSR2(reg2) ^ LFSR3(reg3) ^ LFSR4(reg4) ^ 1;
	return key;
}
int LFSR1(unsigned short* reg1)
{
	*reg1 = ((((*reg1 >> 11) ^ (*reg1 >> 10) ^ (*reg1 >> 9) ^ (*reg1 >> 3) ^ *reg1) & 0x1) << 11) | (*reg1 >> 1);
	return *reg1 & 0x1;
}
int LFSR2(unsigned int* reg2)
{
	*reg2 = ((((*reg2 >> 18) ^ (*reg2 >> 17) ^ (*reg2 >> 16) ^ (*reg2 >> 13) ^ *reg2) & 0x1) << 18) | (*reg2 >> 1);
	return *reg2 & 0x1;
}
int LFSR3(unsigned int* reg3)
{
	*reg3 = ((((*reg3 >> 16) ^ (*reg3 >> 13) ^ *reg3) & 0x1) << 16) | (*reg3 >> 1);
	return *reg3 & 0x1;
}
int LFSR4(unsigned char* reg4)
{
	*reg4 = ((((*reg4 >> 7) ^ (*reg4 >> 5) ^ (*reg4 >> 4) ^ *reg4) & 0x1) << 7) | (*reg4 >> 1);
	return *reg4 & 0x1;
}


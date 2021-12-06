#include "Header.h"
void bufresize(int& size, char** msg)
{
	char* newmass = new char[size]{};
	memcpy(newmass, *msg,size);
	size = size * 8;
	delete[] * msg;
	*msg = newmass;
	
}
void Encrypt(char *msg,char* msg_secret,char* shifr, unsigned short reg1, unsigned int reg2, unsigned int reg3, unsigned char reg4,int curr_size)
{	printf("\nЗашифрованное сообщение\n");
	for (int i = 0; i < curr_size; i++)
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
void Decrypt(char *shifr,char *msg_secret, char* ms, char* unshifr, unsigned short reg1, unsigned int reg2, unsigned int reg3, unsigned char reg4,int curr_size)
{
	printf("\nРасшифрованное сообщение\n");
	for (int i = 0; i < curr_size; i++)
	{
		char mask1 = (Key(&reg1, &reg2, &reg3, &reg4));
		char mask2 = (Key(&reg1, &reg2, &reg3, &reg4) << 1);
		char mask3 = (Key(&reg1, &reg2, &reg3, &reg4) << 2);
		char mask4 = (Key(&reg1, &reg2, &reg3, &reg4) << 3);
		char mask5 = (Key(&reg1, &reg2, &reg3, &reg4) << 4);
		char mask6 = (Key(&reg1, &reg2, &reg3, &reg4) << 5);
		char mask7 = (Key(&reg1, &reg2, &reg3, &reg4) << 6);
		char mask8 = (Key(&reg1, &reg2, &reg3, &reg4) << 7);
		unshifr[i] = ((shifr[i] ^ mask1) & 0x80) +
			((shifr[i] ^ mask2) & 0x40) +
			((shifr[i] ^ mask3) & 0x20) +
			((shifr[i] ^ mask4) & 0x10) +
			((shifr[i] ^ mask5) & 0x8) +
			((shifr[i] ^ mask6) & 0x4) +
			((shifr[i] ^ mask7) & 0x2) +
			((shifr[i] ^ mask8) & 0x1);
		ms[i] = msg_secret[i] ^ unshifr[i];
			cout << ms[i];
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


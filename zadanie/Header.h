#include <iostream>
#include <Windows.h>
using namespace std;
int LFSR1(unsigned short*);
int LFSR2(unsigned int*);
int LFSR3(unsigned int*);
int LFSR4(unsigned char*);
void bufresize(int& size, char** msg);
void Encrypt(char* msg, char* msg_secret, char* shifr, unsigned short r1, unsigned int r2, unsigned int r3, unsigned char r4,int curr_size);
void Decrypt(char* shifr, char* msg_secret, char* ms, char* unshifr, unsigned short reg1, unsigned int reg2, unsigned int reg3, unsigned char reg4,int curr_size);
int Key(unsigned short* reg1, unsigned int* reg2, unsigned int* reg3, unsigned char* reg4);
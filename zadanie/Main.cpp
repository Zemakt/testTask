#include "Header.h"
int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int size = 200, curr_size = 0;
	char* msg = new char[size] {};
	char* msg_secret = new char[size] {};
	char* shifr = new char[curr_size] {};
	char* unshifr = new char[curr_size] {};
	char* ms = new char[curr_size] {};
	printf("Введите строку для шифрования: \n");
	char c = cin.get();
	while (c != '\n')
	{
		msg[curr_size++] = c;
		if (curr_size >= size)
		{
			bufresize(size, &msg);
		}
		msg[curr_size] = c;
		c = cin.get();
	}

	printf("\nСообщение которое необходимо зашифровать\n");
	for (int i = 0; i < curr_size; i++)
	{
		cout << msg[i];
	}
	unsigned short reg1 = atoi(argv[1]);
	unsigned int reg2 = atoi(argv[2]);
	unsigned int reg3 = atoi(argv[3]);
	unsigned char reg4 = atoi(argv[4]);

	Encrypt(msg, msg_secret, shifr, reg1, reg2, reg3, reg4, curr_size);
	Decrypt(shifr, msg_secret, ms, unshifr, reg1, reg2, reg3, reg4, curr_size);

	delete[] msg;
	delete[] ms;
	delete[] msg_secret;
	delete[] shifr;
	delete[] unshifr;
	return 0;
}
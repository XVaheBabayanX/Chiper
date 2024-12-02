#include "Cipher.h"

int main()
{
	std::string  Original, Encrypted;
	size_t Shift;
	std::cout << "Input Text : ";
	std::cin >> Original;
	std::cout << "Input Shift : ";
	std::cin >> Shift;

	Cipher cipher;
	CaesarCipher* caesarCipher = cipher.caesar();
	caesarCipher->setShift(Shift);
	caesarCipher->Encrypt(Original, Encrypted);

	std::cout << "Encrypted Text : " << Encrypted << "\n";

	return 0;
}
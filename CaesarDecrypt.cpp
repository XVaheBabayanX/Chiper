#include "Cipher.h"

int main()
{
	std::string Encrypted, Decrypted;
	size_t Shift;
	std::cout << "Input Encrypted Text : ";
	std::cin >> Encrypted;
	std::cout << "Input Shift : ";
	std::cin >> Shift;

	Cipher cipher;
	CaesarCipher* caesarCipher = cipher.caesar();
	caesarCipher->setShift(Shift);
	caesarCipher->Decrypt(Encrypted, Decrypted);

	std::cout << "Decrypted Text : " << Decrypted << "\n";

	return 0;
}
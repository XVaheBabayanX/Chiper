#include "Transposition.h"

TranspositionCipher::TranspositionCipher() : TranspositionCipher(GenerateRandomKey(MIN_KEY_SIZE)) {}

TranspositionCipher::TranspositionCipher(size_t key)
{
	setKey(key);
}

void TranspositionCipher::setKey(size_t key)
{
	Key = (key > 0) ? key : GenerateRandomKey(MIN_KEY_SIZE);
}

void TranspositionCipher::setTableSize(const std::string& input)
{
	Columns = Key;
	Rows = (input.size() + Columns - 1) / Columns;
	Table.resize(Rows, std::string(Columns, Space));
}

void TranspositionCipher::setKeyRandomSize(size_t Size)
{
	KeyRandomSize = (Size > 0) ? Size : MIN_KEY_SIZE;
}

size_t TranspositionCipher::GenerateRandomKey(size_t Size)
{
	size_t key;
	setKeyRandomSize(Size);
	srand(static_cast<unsigned int>(time(0)));
	key = MIN_KEY_SIZE + std::rand() % (KeyRandomSize - MIN_KEY_SIZE + 1);
	return key;
}

void TranspositionCipher::CreateEncryptTable(const std::string& input)
{
	setTableSize(input);
	for (size_t i = 0; i < input.size(); ++i) {
		Table[i / Columns][i % Columns] = input[i];
	}
}

void TranspositionCipher::CreateDecryptTable(const std::string& input)
{
	setTableSize(input);
	for (size_t i = 0; i < input.size(); ++i) {
		Table[i % Rows][i / Rows] = input[i];
	}
}

void TranspositionCipher::DeleteTable()
{
	Table.clear();
}

std::string TranspositionCipher::CreateEncryptString(std::string& output)
{
	for (size_t col = 0; col < Columns; col++)
	{
		for (size_t row = 0; row < Rows; row++)
		{
			output.push_back(Table[row][col]);
		}
	}
	return output;
}

std::string TranspositionCipher::CreateDecryptString(std::string& output)
{
	for (size_t row = 0; row < Rows; row++)
	{
		for (size_t col = 0; col < Columns; col++)
		{
			output.push_back(Table[row][col]);
		}
	}
	return output;
}

void TranspositionCipher::Encrypt(const std::string& input, std::string& output)
{
	CreateEncryptTable(input);
	PrintTable();
	output = CreateEncryptString(output);
	DeleteTable();
}

void TranspositionCipher::Decrypt(const std::string& input, std::string& output)
{
	CreateDecryptTable(input);
	PrintTable();
	output = CreateDecryptString(output);
	DeleteTable();
}

void TranspositionCipher::PrintTable()
{
	if (Table.size() == 0) std::cout << "\nTable is empty";
	else {
		std::cout << std::endl;
		for (const auto& row : Table) {
			for (char ch : row) {
				std::cout << ch << ' ';
			}
			std::cout << std::endl;
		}
	}
}
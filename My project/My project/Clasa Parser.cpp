#include<iostream>
#include<string.h>

#include "Clasa Ecuatie.cpp"


using namespace std;

class Parser 
{
	char* RetinereVector = nullptr;

public:

	Parser()
	{
		this->RetinereVector = nullptr;
	}

	Parser(char* ecuatie)
	{
		if (ecuatie != nullptr)
		{
			if (this->RetinereVector != nullptr)
			{
				delete[] this->RetinereVector;
			}
			this->RetinereVector = new char[strlen(ecuatie) + 1];
			strcpy_s(this->RetinereVector, strlen(ecuatie) + 1, ecuatie);

		}
		else
		{
			this->RetinereVector = nullptr;
		}

	}


	~Parser()
	{
		if (this->RetinereVector != nullptr)
			delete[] this->RetinereVector;

	}

	void setVector(char* vector)
	{
		if (vector != nullptr)
		{
			delete[] this->RetinereVector;
			this->RetinereVector = new char[strlen(vector) + 1];
			strcpy_s(this->RetinereVector, strlen(vector) + 1, vector);
		}
		else
		{
			this->RetinereVector = nullptr;
		}

	}

	char* getVector()
	{
		if (this->RetinereVector != nullptr)
		{
			char* copie = new char[strlen(this->RetinereVector) + 1];
			strcpy_s(copie, strlen(this->RetinereVector) + 1, this->RetinereVector);
			return copie;
		}
		else
		{
			return nullptr;
		}
	}


	Parser(Parser& p)
	{
		if (p.RetinereVector != nullptr)
		{
			if (this->RetinereVector != nullptr)
			{
				delete[] this->RetinereVector;
			}
			this->RetinereVector = new char[strlen(p.RetinereVector) + 1];
			strcpy_s(this->RetinereVector, strlen(p.RetinereVector) + 1, p.RetinereVector);
		}
		else
		{
			this->RetinereVector = nullptr;
		}

	}

	static bool isDigit(char ch) {
		return ch >= '0' && ch <= '9';
	}

	operator float() const
	{
		float numar = 0.0f;
		float factor = 1.0f;
		bool decimalPointEncountered = false;
		const char* str = RetinereVector;

		if (!str) {
			return 0.0f;
		}

		for (int i = 0; str[i] != '\0'; i++) {
			char ch = str[i];
			if (ch >= '0' && ch <= '9') {
				if (decimalPointEncountered) {
					factor /= 10.0f;
					numar += (ch - '0') * factor;
				}
				else {
					numar = numar * 10.0f + (ch - '0');
				}
			}
			else if (ch == '.' && !decimalPointEncountered) {
				decimalPointEncountered = true;
			}
			else {
				break;
			}
		}
		return numar;
	}


	static Ecuatie parseEcuatie(const string& input)
	{
		Ecuatie ecuatie;

		string operand = "";
		char ultimulOperator = '\0';

		for (int i = 0; input[i] != '\0'; i++)
		{
			char ch = input[i];
			if (isDigit(ch))
			{
				operand += ch;
			}
			else
			{
				if (!operand.empty()) {
					Parser parser(operand);
					float valoare = parser; // Utilizează operatorul de cast pentru conversie
					ecuatie.adaugaOperand(valoare);
					operand = "";
				}

				if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
					ecuatie.adaugaOperator(ch);
					ultimulOperator = ch;
				}
			}
		}

		// Procesează ultimul operand, dacă există
		if (!operand.empty()) {
			Parser parser(operand);
			float valoare = parser; // Utilizează operatorul de cast pentru conversie
			ecuatie.adaugaOperand(valoare);
		}

		return ecuatie;
	}



};

ostream& operator<<(ostream& out, Parser& p)
{
	if (p.getVector() != nullptr)
	{
		out << "Ecuatia acre trebuie calculata este: ";
		out << p.getVector();
	}
	else
		out << "Nu exista ecuatia care sa fie calculata: ";

	return out;
}

istream& operator>>(istream& in, Parser& p)
{
	cout << "Dati ecuatia care urmeaza sa fie calculata: ";
	char* copie;
	in >> copie;
	p.setVector(copie);

	return in;
}


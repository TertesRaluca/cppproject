#pragma once
#include<iostream>
#include<stdio.h>
#include<string>

using namespace std;

class Ecuatie
{
	char* expresie;
	float* operanzi;
	char* operatori;
	int nrOperanzi;
	int nrOperatori;
public:

	Ecuatie()
	{
		this->expresie = nullptr;
		this->operanzi = nullptr;
		this->operatori = nullptr;
		this->nrOperanzi = 0;
		this->nrOperatori = 0;
	}

	Ecuatie(const char* expresie)
	{
		setExpresie(expresie);
	}


	char* getExpresie()
	{
		if (this->expresie != nullptr)
		{
			char* copie = new char[strlen(this->expresie) + 1];
			strcpy_s(copie, strlen(this->expresie) + 1, this->expresie);
			return copie;
		}
		else
			return nullptr;
	}

	float* getOperanzi()
	{
		if (this->operanzi != nullptr)
		{
			float* copie = new float[nrOperanzi];
			for (int i = 0; i < nrOperanzi; i++) {
				copie[i] = this->operanzi[i];
			}
			return copie;
		}
		return nullptr;

	}

	char* getOperatori()
	{
		if (this->operatori != nullptr)
		{
			char* copie = new char[strlen(this->operatori) + 1];
			strcpy_s(copie, strlen(this->operatori) + 1, this->operatori);
			return copie;
		}
		else
			return nullptr;
	}

	int getnrOperatori()
	{
		return this->nrOperatori;
	}

	int getnrOperanzi()
	{
		return this->nrOperanzi;
	}

	void setExpresie(const char* vector)
	{
		if (vector != nullptr)
		{
			if (this->expresie != nullptr)
			{
				delete[] this->expresie;
			}
			this->expresie = new char[strlen(vector) + 1];
			strcpy_s(this->expresie, strlen(vector) + 1, vector);
		}
		else
			this->expresie = nullptr;

	}

	void setOperatori(char* operatori)
	{

		if (operatori != nullptr)
		{
			if (this->operatori != nullptr)
			{
				delete[] this->operatori;
			}
			this->operatori = new char[strlen(operatori) + 1];
			strcpy_s(this->operatori, strlen(operatori) + 1, operatori);
		}
		else
			this->operatori = nullptr;;
	}

	void setOperanzi(float* vector, int nrOperanzi)
	{
		this->nrOperanzi = nrOperanzi;
		if (vector != nullptr && nrOperanzi != 0)
		{
			if (this->operanzi != nullptr)
			{
				delete[] this->operanzi;
			}
			this->operanzi = new float[nrOperanzi];
			for (int i = 0; i < nrOperanzi; i++)
			{
				this->operanzi[i] = vector[i];
			}
		}
		else
			this->operanzi = nullptr;
	}

	void setnrOperatori(int nrOperatori)
	{
		this->nrOperatori = nrOperatori;
	}

	void setnrOperanzi(int nrOPeranzi)
	{
		this->nrOperanzi = nrOPeranzi;
	}

	void adaugaOperand(float operand) {
		float* temp = new float[nrOperanzi + 1];
		for (int i = 0; i < nrOperanzi; i++) {
			temp[i] = this->operanzi[i];
		}
		temp[nrOperanzi] = operand;
		delete[] this->operanzi;
		this->operanzi = temp;
		nrOperanzi++;
	}

	void adaugaOperator(char op)
	{
		char* temp = new char[nrOperatori + 1];
		for (int i = 0; i < nrOperatori; i++) {
			temp[i] = this->operatori[i];
		}
		temp[nrOperatori] = op;
		delete[] this->operatori;
		this->operatori = temp;
		nrOperatori++;
	}

	static float stringToFloat(const char* str) {
		float rezultat = 0.0;
		float divizor = 1.0;
		bool isNegative = false;
		bool inFraction = false;

		if (*str == '-') {
			isNegative = true;
			++str;
		}

		while (*str != '\0') {
			if (*str == '.') {
				inFraction = true;
				++str;
				continue;
			}

			int cifra = *str - '0';
			if (cifra >= 0 && cifra <= 9) {
				rezultat = rezultat * 10 + cifra;
				if (inFraction) {
					divizor *= 10.0;
				}
			}
			else {
				break;
			}

			++str;
		}

		if (isNegative) {
			rezultat = -rezultat;
		}

		return rezultat / divizor;
	}

	Ecuatie(Ecuatie& e)
	{
		this->nrOperanzi = e.nrOperanzi;
		this->nrOperatori = e.nrOperatori;
		if (e.nrOperanzi != 0 && e.operanzi != nullptr)
		{
			if (this->operanzi != nullptr)
			{
				delete[] this->operanzi;
			}
			this->operanzi = new float[e.nrOperanzi];
			for (int i = 0; i < e.nrOperanzi; i++)
			{
				this->operanzi[i] = e.operanzi[i];
			}
		}
		else
			this->operanzi = nullptr;
		if (e.nrOperatori != 0 && e.operatori != nullptr)
		{
			if (this->operatori != nullptr)
			{
				delete[] this->operatori;
			}
			this->operatori = new char[strlen(e.operatori) + 1];
			strcpy_s(this->operatori, strlen(e.operatori) + 1, e.operatori);
		}
		else
		{
			this->operatori = nullptr;
		}

		if (e.expresie != nullptr)
		{
			if (this->expresie != nullptr)
			{
				delete[] this->expresie;
			}
			this->expresie = new char[strlen(e.expresie) + 1];
			strcpy_s(this->expresie, strlen(e.expresie) + 1, e.expresie);
		}
		else
		{
			this->expresie = nullptr;
		}
	}

	Ecuatie& operator=(const Ecuatie& e)
	{
		if(this!=&e)
			{
			this->nrOperanzi = e.nrOperanzi;
			this->nrOperatori = e.nrOperatori;
			if (e.nrOperanzi != 0 && e.operanzi != nullptr)
			{
				if (this->operanzi != nullptr)
				{
					delete[] this->operanzi;
				}
				this->operanzi = new float[e.nrOperanzi];
				for (int i = 0; i < e.nrOperanzi; i++)
				{
					this->operanzi[i] = e.operanzi[i];
				}
			}
			else
				this->operanzi = nullptr;
			if (e.nrOperatori != 0 && e.operatori != nullptr)
			{
				if (this->operatori != nullptr)
				{
					delete[] this->operatori;
				}
				this->operatori = new char[strlen(e.operatori) + 1];
				strcpy_s(this->operatori, strlen(e.operatori) + 1, e.operatori);
			}
			else
			{
				this->operatori = nullptr;
			}

			if (e.expresie != nullptr)
			{
				if (this->expresie != nullptr)
				{
					delete[] this->expresie;
				}
				this->expresie = new char[strlen(e.expresie) + 1];
				strcpy_s(this->expresie, strlen(e.expresie) + 1, e.expresie);
			}
			else
			{
				this->expresie = nullptr;
			}


		}

	}

	static void extractOperandsAndOperators(const char* str, float* operands, char* operators, int* n_operands, int* n_operators) {
		int operandsIdx = -1; 
		int operatorsIdx = -1;

		char* currentOperand = new char[strlen(str)];
		int currentOperandIndex = 0;
		bool operandIsNegative = false;
		for (int i = 0; i < strlen(str); i++) {

			
			if (str[i] == ' ') {
				continue;
			}

			
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
				currentOperand[currentOperandIndex++] = str[i];
			}

			
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '#' || str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']') {
				char currentFoundOperator = str[i];

				
				if (currentOperandIndex != 0) {
					float operand = stringToFloat(currentOperand);

					if (operandIsNegative)
						operands[++operandsIdx] = 0 - operand; 
					else
						operands[++operandsIdx] = operand;

					
					memset(currentOperand, 0, strlen(str));
					currentOperandIndex = 0;
				}
				else {
					if (currentFoundOperator == '-') {
						operandIsNegative = true;
						continue;
					}
					else if (currentFoundOperator == '[' || currentFoundOperator == '(') {
						
						if (operandIsNegative)
							operators[operatorsIdx] = '-';
					}
				}

				
				if (currentFoundOperator == '-') {
					operandIsNegative = true;

					
					operators[++operatorsIdx] = '+';
				}
				else {
					operandIsNegative = false;

					
					operators[++operatorsIdx] = currentFoundOperator;
				}

			}
		}

		
		if (currentOperandIndex != 0) {
			float operand = stringToFloat(currentOperand);

			if (operandIsNegative)
				operands[++operandsIdx] = 0 - operand; 
			else
				operands[++operandsIdx] = operand;

			delete[] currentOperand;
		}

		*n_operands = operandsIdx;
		*n_operators = operatorsIdx;
	}

	~Ecuatie()
	{
		if (this->expresie != nullptr)
			delete[] this->expresie;
		if (this->operanzi != nullptr)
			delete[] this->operanzi;
		if (this->operatori != nullptr)
			delete[] this->operatori;
	}

	float& operator[](int index)
	{
		if (index >= 0 && index < nrOperanzi)
		{
			return this->operanzi[index];
		}
		else
		{
			throw exception();
		}
	}


	Ecuatie& operator++() {
		if (nrOperanzi > 0 && operanzi != nullptr) {
			++operanzi[0]; 
		}
		return *this;
	}

};

ostream& operator<<(ostream& out, Ecuatie& e)
{
	out << "Expresia de calculat: "<<e.getExpresie()<<endl;
	out << "Numarul de operanzi este: " << e.getOperanzi() << endl;
	out << "Numarul de operatori este: " << e.getnrOperatori() << endl;
	if (e.getnrOperatori() != 0 && e.getOperatori() != nullptr)
	{
		out << "Operanzii ecuatiei sunt: " << e.getOperatori() << endl;
	}
	else
	{
		out << "Functia nu are operatori" << endl;
	}
	if (e.getnrOperanzi() != 0 && e.getOperanzi() != nullptr)
	{
		for (int i = 0; i < e.getnrOperatori(); i++)
			out << e.getOperatori()[i] << " " << endl;
	}
	return out;
}

istream& operator>>(istream& in, Ecuatie& e)
{
	cout << "Numarul de operanzi este: "<<endl;
	int nrOperatori;
	int nrOperanzi;
	in >> nrOperanzi;
	e.setnrOperanzi(nrOperanzi);
	cout << "Numarul de operatori: " << endl;;
	in >> nrOperatori;
	e.setnrOperatori(nrOperatori);
	cout << "Ecuatia care trebuie evaluata: ";
	string copie;
	getline(in, copie);
	e.setExpresie(copie.c_str());
	cout << endl << "Operatorii expresiei sunt: "<<endl;
	cout << endl << "Operanzii expresiei sunt: " << endl;
	float* vector = new float[nrOperanzi];
	for (int i = 0; i < nrOperanzi; i++)
	{
		cout << "Citeste elementul " << i + 1<<" ";
		in >> vector[i];
	}
	e.setOperanzi(vector, nrOperanzi);

	return in;

}


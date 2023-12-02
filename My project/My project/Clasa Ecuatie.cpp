#include<iostream>
#include<string.h>



using namespace std;


class Ecuatie
{
	float* operanzi=nullptr;   // Array pentru stocarea operandilor
	char* operatori=nullptr;   // Array pentru stocarea operatorilor
	int nrOperanzi;   // Dimensiunea array-ului de operanzi
	int nrOperatori;

public:

	Ecuatie()
	{
		this->nrOperanzi = 0;
		this->nrOperatori = 0;
		this->operanzi = nullptr;
		this->operatori = nullptr;
	}

	Ecuatie(float* operanzi, char* operatori, int nrOperanzi, int nrOperatori)
	{
		this->nrOperanzi = nrOperanzi;
		this->nrOperatori = nrOperatori;
		setOperanzi(operanzi, nrOperanzi);
		setOperatori(operatori, nrOperatori);
	}

	~Ecuatie() 
	{
		if(this->operanzi!=nullptr)
			delete[] this->operanzi;
		if (this->operatori != nullptr)
			delete[] this->operatori;
	}

	float* getOperanzi()
	{
		if (operanzi != nullptr)
		{
			float* copie = new float[nrOperanzi];
			for (int i = 0; i < nrOperanzi; i++)
			{
				copie[i] = operanzi[i];
			}
			return copie;
		}
		return nullptr;
	}

	char* getOperatori()
	{
		if (operatori != nullptr)
		{
			char* copie = new char[strlen(operatori) + 1];
			strcpy_s(copie, strlen(operatori) + 1, operatori);
			return copie;
		}
		else
			return nullptr;
	}

	int getnrOperanzi()
	{
		return this->nrOperanzi;
	}

	int getnrOperatori()
	{
		return this->nrOperatori;
	}

	void setnrOperanzi(int nrOperanzi)
	{
		this->nrOperanzi = nrOperanzi;
	}

	void setnrOperatori(int nrOperatori)
	{
		this->nrOperatori = nrOperatori;
	}

	void setOperanzi(float* operanzi, int nrOperanzi)
	{
		if (operanzi != nullptr && nrOperanzi != 0)
		{
			if (this->operanzi != nullptr)
			{
				delete[] this->operanzi;
				this->operanzi = nullptr;
			}
			this->nrOperanzi = nrOperanzi;
			this->operanzi = new float[nrOperanzi];
			for (int i = 0; i < nrOperanzi; i++)
			{
				this->operanzi[i] = operanzi[i];
			}
		}
		else
			this->operanzi = nullptr;
	}

	void setOperatori(char* operatori, int nrOperatori)
	{
		if (operatori != nullptr && nrOperatori != 0)
		{
			if (this->operatori != nullptr)
			{
				delete[] this->operatori;
				this->operatori = nullptr;
			}
			this->nrOperatori = nrOperatori;
			this->operatori=new char[nrOperatori];
			strcpy_s(this->operatori, nrOperatori, operatori);
		}
		else
		{
			this->operatori = nullptr;
		}

	}


	void adaugaOperand(float operand) {
		// Logica pentru adăugarea unui operand la array
		// Acest lucru va implica realocarea array-ului și adăugarea noului operand
	}

	void adaugaOperator(char op) {
		// Logica similară pentru adăugarea unui operator
	}

	float evaluate() {
		// Logica pentru evaluarea ecuației
		// Aceasta va implica parcurgerea array-urilor de operanzi și operatori și efectuarea calculelor
		// Trebuie să ții cont de ordinea operațiilor matematice și de paranteze, dacă sunt prezente
		return 0; // Rezultatul ipotetic al ecuației
	}

	




	

};




int main()
{
	


}
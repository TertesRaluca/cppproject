#include<iostream>
#include<stdio.h>

using namespace std;

class Util {
public:
	static double* copiereVector(double* rezultate, int capacitate)
	{
		if (capacitate == 0 || rezultate == nullptr)
			return nullptr;
		double* vectorNou = new double[capacitate];
		for (int i = 0; i < capacitate; i++)
		{
			vectorNou[i] = rezultate[i];
		}
		return vectorNou;
	}

	static void AfisareVector(double* rezultate, int cap)
	{
		if (cap == 0 || rezultate == nullptr)
			cout << "Vectorul este null"<<endl;
		else
		{
			cout << "Vectorul este: " << endl;
			for (int i = 0; i < cap; i++)
				cout << rezultate[i];
		}

	}





};

class CalculatorSimplu
{
	double* vectorRezultate;
	int capacitateVector;

	const float precizie = 0.00001;
	static int nrMaxCalcule;

public:
	//constructor implicit

	CalculatorSimplu() {
		this->vectorRezultate = nullptr;
		this->capacitateVector = 0;
	}

	//constructor de copiere

	CalculatorSimplu(double* rezultate, int capacitate)
	{
		if (this->vectorRezultate != nullptr)
			delete[] vectorRezultate;
		this->vectorRezultate = new double[capacitate];
		this->capacitateVector = capacitate;
		for (int i = 0; i < capacitate; i++)
			this->vectorRezultate[i] = rezultate[i];
	}

	//destructor

	~CalculatorSimplu()
	{
		if (this->vectorRezultate != nullptr)
			delete[] this->vectorRezultate;
	}

	//getteri si setteri

	 int getcapacitateVector()
	{
		 return this->capacitateVector;
	}

	 double* getvectorRezultate()
	 {
		 return Util::copiereVector(this->vectorRezultate, this->capacitateVector);
	 }

	 void setcapacitateVector(int capacitate)
	 {
		 if (capacitate < 0)
			 throw exception("Capacitatea vectorului nu poate fi negativa");
		 else
			 this->capacitateVector = capacitate;
	 }

	 void setvectorRezultate(double* rezultate, int capacitate) 
	 {
		 if (capacitate == 0 || rezultate==nullptr)
			 this->vectorRezultate = nullptr;
		 else
		 {
			 delete[] this->vectorRezultate;
			 this-> vectorRezultate = new double[capacitate];
			 for (int i = 0; i < this->capacitateVector; i++)
			 {
				 this->vectorRezultate[i] = rezultate[i];
			 }
		 }
	 }
};

int CalculatorSimplu::nrMaxCalcule;

int main()
{
	CalculatorSimplu Calc;
	Calc.setcapacitateVector(4);
	double rezultate[] = { 0.3, 10.89, 78.67, 0.17 };
	int capacitate = 4;
	Calc.setvectorRezultate (rezultate, capacitate);
	double* vectorRez = Calc.getvectorRezultate();
	cout << "Numar maxim al capacitatii vectorului de rezultate: " << Calc.getcapacitateVector() << endl;
	Util::AfisareVector(vectorRez, Calc.getcapacitateVector());
	return 0;
}
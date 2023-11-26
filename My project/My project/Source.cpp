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

	static float* copiereVector_float(float* rezultate, int capacitate)
	{
		if (capacitate == 0 || rezultate == nullptr)
			return nullptr;
		float* vectorulNou = new float[capacitate];
		for (int i = 0; i < capacitate; i++)
		{
			vectorulNou[i] = rezultate[i];
		}
		return vectorulNou;
	}

	static void AfisareVector(double* rezultate, int cap)
	{
		if (cap == 0 || rezultate == nullptr)
			cout << "Vectorul este null"<<endl;
		else
		{
			cout << "Vectorul este: " << endl;
			for (int i = 0; i < cap; i++)
				cout << rezultate[i]<<" ";
		}

	}

	static void AfisareVector_float(float* rezultate, int cap)
	{
		if (cap == 0 || rezultate == nullptr)
			cout << "Vectorul este null" << endl;
		else
		{
			cout << "Vectorul este: " << endl;
			for (int i = 0; i < cap; i++)
				cout << rezultate[i]<<" ";
		}

	}
};

class CalculatorSimplu
{
	double* vectorRezultate;
	int capacitateVector;
	float* VectorVariabile;
	int nrVariabile;

	const float precizie = 0.00001;
	static int nrMaxCalcule;

public:
	//constructor implicit

	CalculatorSimplu() {
		this->vectorRezultate = nullptr;
		this->capacitateVector = 0;
		this->VectorVariabile = nullptr;
		this->nrVariabile = 0;
	}

	//constructor de copiere

	CalculatorSimplu(double* rezultate, int capacitate, float* variabile, int nrVariabile)
	{
		if (this->vectorRezultate != nullptr)
			delete[] vectorRezultate;
		this->vectorRezultate = new double[capacitate];
		this->capacitateVector = capacitate;
		for (int i = 0; i < capacitate; i++)
			this->vectorRezultate[i] = rezultate[i];

		if (this->VectorVariabile != 0)
			delete[] this->VectorVariabile;
		this->nrVariabile = nrVariabile;
		this->VectorVariabile = new float[nrVariabile];
		for (int i; i < nrVariabile; i++)
			this->VectorVariabile[i] = variabile[i];
	}

	//destructor

	~CalculatorSimplu()
	{
		if (this->vectorRezultate != nullptr)
			delete[] this->vectorRezultate;

		if (this->VectorVariabile != nullptr)
			delete[]  this->VectorVariabile;
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

	 int getnrVariabile() {
		 return this->nrVariabile;
	 }

	 float* getVectorVariabile()
	 {
		 return Util::copiereVector_float(this->VectorVariabile, this->nrVariabile);
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

	 void setnrVariabile(int nrVariabile)
	 {
		 if (nrVariabile < 0)
			 cout << "Lungimea unui vector nu poate sa fie negativa";
		 else
			 this->nrVariabile = nrVariabile;
	 }

	 void setVectorVariabile(float* VecVariabile, int nrVar)
	 {
		 if (nrVar == 0 || VecVariabile == nullptr)
			 this->VectorVariabile = nullptr;
		 else
		 {
			 delete[] this->VectorVariabile;
			 this->VectorVariabile = new float[nrVar];
			 for (int i = 0; i < nrVar; i++)
			 {
				 this->VectorVariabile[i] = VecVariabile[i];
			 }
		 }

	 }
};

int CalculatorSimplu::nrMaxCalcule;

int main()
{
	CalculatorSimplu Calc;
	Calc.setcapacitateVector(4);
	Calc.setnrVariabile(3);
	double rezultate[] = { 0.3, 10.89, 78.67, 0.17 };
	float variabile[] = { 12, 13.9, 14.50 };
	int capacitate = 4;
	int nrvar = 3;
	Calc.setvectorRezultate (rezultate, capacitate);
	Calc.setVectorVariabile(variabile, nrvar);
	double* vectorRez = Calc.getvectorRezultate();
	float* vectorVar = Calc.getVectorVariabile();
	cout << "Numar maxim al capacitatii vectorului rez de rezultate: " << Calc.getcapacitateVector() << endl;
	Util::AfisareVector(vectorRez, Calc.getcapacitateVector());
	cout << endl;
	cout << "Numar maxim al capacitatii vectorului variabile de rezultate: " << Calc.getnrVariabile() << endl;
	Util::AfisareVector_float(vectorVar, Calc.getnrVariabile());
	return 0;
}
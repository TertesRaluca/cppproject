#include "Ecuatie.h"
#include"Prelucrare.h"
#include"Calculator.h"

#include<iostream>
#include<stdio.h>
#include<string>
#include<cmath>

using namespace std;



int main()
{
	Eliminare expresie("Expresie nedefinita");
	const char* expresieComparare=expresie.getExpresie();
	const char* oprire = "Exit";

	while ( strcmp(expresieComparare,oprire)) 
	{
		cin >> expresie;
		cout << expresie;
		const char* expresie2 = expresie.getExpresie();
		Eliminare rezultat = Eliminare::parse(expresie2);
		cout << endl << rezultat << endl;
		const char* expresie3 = rezultat.getExpresie();
		float* operands = new float[strlen(expresie3)];
		char* operators = new char[strlen(expresie3)];
		int n_operands = 0;
		int n_operators = 0;
		Ecuatie::extractOperandsAndOperators(expresie3, operands, operators, &n_operands, &n_operators);
		cout << "Operanzi: ";
		for (int i = 0; i <= n_operands; i++) {
			cout << operands[i] << " ";
		}
		cout << endl;
		cout << "Operatori: ";
		for (int i = 0; i <= n_operators; i++) {
			cout << operators[i] << " ";
		}

		cout << expresie3 << endl;
		cout << Calculator::Compute(expresie3)<<endl;
		expresieComparare = expresie.getExpresie();
		
	}
 
	return 0;
}
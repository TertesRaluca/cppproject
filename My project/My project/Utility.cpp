#include "Ecuatie.h"
#include"Prelucrare.h"
#include"Calculator.h"

#include<iostream>
#include<stdio.h>
#include<string>
#include<cmath>

using namespace std;

/// <summary>
/// Eu, initial am facut supraincarcarile pt clasele eliminare si ecutie, dar imi dadea o erare care zicea ca sunt deja definite in alta clasa
/// si pentru a nu avea erori le-am sters.
/// </summary>


int main()
{
	const char* expresie = "-2.546 - 2.55345 * [2 ^ (3 + 27#3)] + 1 + 5 * 2\0";
	Eliminare objEliminare(expresie);
    const char* rezultat = Eliminare::parse(expresie);
	const char* expresie2 = "-2+3*8";
	Calculator objCalculator(expresie2);
	cout << Calculator::parseAndCompute(expresie2) << endl;

	float* operands = new float[strlen(rezultat)];
	char* operators = new char[strlen(rezultat)];
	int n_operands = 0;
	int n_operators = 0;

    Ecuatie objEcuatie(rezultat);
   Ecuatie::extractOperandsAndOperators(rezultat, operands,operators, &n_operands, &n_operators);

   cout << "Operanzi: ";
   for (int i = 0; i <= n_operands; i++) {
	   cout << operands[i] << " ";
   }

   cout << endl;

   cout << "Operatori: ";
   for (int i = 0; i <= n_operators; i++) {
	   cout << operators[i] << " ";
   }
   
 
	return 0;
}
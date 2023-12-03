#pragma once
#include<iostream>
#include<stdio.h>
#include "Prelucrare.h"
#include"Ecuatie.h"

using namespace std;

class Calculator
{
    char* expresie;

public:

    Calculator()
    {
        this->expresie = nullptr;
    }

    Calculator(const char* vector)
    {
        setExpresie(vector);
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
    bool isDigit(char ch) {
        return ch >= '0' && ch <= '9';
    }

    static  float stringToFloat(const char* str) {
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

    static  bool solve(float operand1, float operand2, char op, float* result) {
        cout << "Solving: " << operand1 << " " << op << " " << operand2 << endl;

        switch (op) {
        case '+':
            *result = operand1 + operand2;
            break;
        case '-':
            *result = operand1 - operand2;
            break;
        case '*':
            *result = operand1 * operand2;
            break;
        case '/':
            if (operand2 == 0) {
                return false;
            }
            *result = operand1 / operand2;
            break;
        case '^':
            *result = pow(operand1, operand2);
            break;
        case '#':
            if (operand2 == 0) {
                return false;
            }
            *result = pow(operand1, 1.0 / operand2);
            break;
        }

        return true;
    }

  static  bool calculate(const float* operands, const char* operators, float* result) {
        float operand1 = operands[0];
        float operand2 = operands[1];
        char _operator = operators[0];

        switch (_operator) {
        case '+':
            *result = operand1 + operand2;
            break;
        case '-':
            *result = operand1 - operand2;
            break;
        }

        return true;
    }

    static  float parseAndCompute(const char* str) {
        float* operands = new float[strlen(str)]();
        char* operators = new char[strlen(str)];

        int operandsIdx = -1; // -1 desemneaza un array gol
        int operatorsIdx = -1;

        // Numarul curent care trebuie parsat
        char* currentOperand = new char[strlen(str)];
        int currentOperandIndex = 0;

        /*
            Retinem parantezele deschise pentru a verifica
            daca sunt corect pozitionate in cadrul expresiei
        */
        char* openParantheses = new char[strlen(str)];
        int paranthesesIdx = -1;
        for (int i = 0; i < strlen(str); i++) {

            // Daca e spatiu, continuam cu urmatorul caracter
            if (str[i] == ' ') {
                continue;
            }

            if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
                currentOperand[currentOperandIndex++] = str[i];
            }

            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '#' || str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']') {
                char currentFoundOperator = str[i];

                // Parsam ultimul operand gasit
                if (currentOperandIndex != 0) {
                    float operand = stringToFloat(currentOperand);
                    operands[++operandsIdx] = operand; // Il adaugam

                    // clear pentru urmatorul operand
                    memset(currentOperand, 0, strlen(str));
                    currentOperandIndex = 0;
                }
                else {
                    /*
                        Daca nu am gasit niciun operand pana acum,
                        verificam daca nu cumva operatorul desemneaza semnul operandului urmator
                    */
                    if (currentFoundOperator == '-') {
                        /*
                            Minus desemneaza un numar negativ,
                            prin urmare putem salva expresia "0 - numar"
                        */
                        operands[++operandsIdx] = 0;
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }
                }

                /*
                    Daca am gasit un operator, exista 3 cazuri:
                    1. operand1 op_gasit operand2 => il retinem pana gasim operand2
                    2. operand1 op_anterior operand2 op_gasit => intai rezolvam expresia (operand1 op_anterior operand2) daca respecta regulile de precedenta
                    3. op_gasit este o paranteza
                */
                if (currentFoundOperator == '(' || currentFoundOperator == ')' || currentFoundOperator == '[' || currentFoundOperator == ']') {
                    /*
                        Daca este o paranteza deschisa, doar o retinem
                        si mergem mai departe
                    */
                    if (currentFoundOperator == '(' || currentFoundOperator == '[') {
                        openParantheses[++paranthesesIdx] = currentFoundOperator;

                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                    /*
                        Altfel, daca este inchisa, trebuie sa rezolvam
                        toate operatiile din interiorul parantezei.

                        Verificam intai daca inchiderea se face corect
                    */
                    if (paranthesesIdx == -1) {
                        /*
                            Daca am gasit o paranteza inchisa fara pereche,
                            returnam eroare
                        */
                        cout << "Wrong parantheses alignment!" << endl;
                        return -1; // sau false, ca nu s-a putut rezolva
                    }
                    else {
                        char lastOpenParanthesis = openParantheses[paranthesesIdx--];

                        /*
                            Daca nu e inchisa corect, returnam eroare
                        */
                        if ((lastOpenParanthesis == '(' && currentFoundOperator == ']')
                            || (lastOpenParanthesis == '[' && currentFoundOperator == ')')) {
                            cout << "Wrong parantheses alignment!" << endl;
                            return -1; // sau false, ca nu s-a putut rezolva
                        }
                    }

                    char lastFoundOperator = operators[operatorsIdx--];
                    while (lastFoundOperator != '(' && lastFoundOperator != '[') {
                        float lastFoundOperand2 = operands[operandsIdx--];
                        float lastFoundOperand1 = operands[operandsIdx--];

                        float result = 0;
                        bool done = solve(lastFoundOperand1, lastFoundOperand2, lastFoundOperator, &result);

                        if (!done) {
                            cout << "Operation: " << lastFoundOperand1 << " " << lastFoundOperator << " " << lastFoundOperand2 << " not allowed!" << endl;
                            return -1; // sau false, ca nu s-a putut rezolva
                        }

                        /*
                            Adaugam rezultatul in array-ul de operanzi,
                            intrucat acesta va constitui primul operand al
                            operatorului curent gasit
                        */
                        operands[++operandsIdx] = result;

                        lastFoundOperator = operators[operatorsIdx--];
                    }
                }
                else {
                    /*
                        Daca nu mai avem alti operatori gasiti
                        il retinem pe acesta, si trecem mai departe
                    */
                    if (operatorsIdx == -1) {
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                    char lastFoundOperator = operators[operatorsIdx];

                    /*
                        Daca ultimul operator gasit a fost o paranteza,
                        doar retinem si operatorul curent gasit
                        si trecem mai departe
                    */
                    if (lastFoundOperator == '(' || lastFoundOperator == '[') {
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                    /*
                        Verificam regula de precedenta
                        Daca operatorul curent gasit are prioritate in
                        evaluarea expresiei, il retinem si trecem mai departe
                    */
                    if (((lastFoundOperator == '+' || lastFoundOperator == '-') && (currentFoundOperator == '*' || currentFoundOperator == '/'))
                        || ((lastFoundOperator == '+' || lastFoundOperator == '-') && (currentFoundOperator == '#' || currentFoundOperator == '^'))
                        || ((lastFoundOperator == '*' || lastFoundOperator == '/') && (currentFoundOperator == '#' || currentFoundOperator == '^'))) {
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                    /*
                        Altfel, ultimul operator gasit nu a fost o paranteza,
                        prin urmare trebuie sa rezolvam expresia ce contine operatorul
                        gasit anterior (daca se respecta ordinea de precendenta, altfel il retinem)
                    */
                    float lastFoundOperand2 = operands[operandsIdx--];
                    float lastFoundOperand1 = operands[operandsIdx--];

                    /*
                        Decrementam indexul operatorilor
                        pentru a desmna folosirea ultimului operator
                    */
                    operatorsIdx--;

                    float result = 0;
                    bool done = solve(lastFoundOperand1, lastFoundOperand2, lastFoundOperator, &result);

                    if (!done) {
                        cout << "Operation: " << lastFoundOperand1 << " " << lastFoundOperator << " " << lastFoundOperand2 << " not allowed!" << endl;
                        return -1; // sau false, ca nu s-a putut rezolva
                    }

                    /*
                        Adaugam rezultatul in array-ul de operanzi,
                        intrucat acesta va constitui primul operand al
                        operatorului curent gasit
                    */
                    operands[++operandsIdx] = result;

                    // Adaugam si operatorul curent gasit
                    operators[++operatorsIdx] = currentFoundOperator;
                }
            }

        }

        /*
            Daca mai avem paranteze deschise
            care nu au fost inchise,
            returnam eroare
        */
        if (paranthesesIdx != -1) {
            cout << "Unclosed parantheses!" << endl;
            return -1;
        }

        // Parsam si ultimul operand din ecuatie (daca ecuatia se termina intr-unul)
        if (currentOperandIndex != 0) {
            float operand = stringToFloat(currentOperand);
            operands[++operandsIdx] = operand; // Il adaugam

            delete[] currentOperand;
        }

        // Cat timp mai avem operatori de rezolvat
        // calculam ecuatiile
        while (operatorsIdx != -1) {

            // Scoatem ultimul operator gasit impreuna cu ultimii 2 operanzi
            float lastFoundOperand2 = operands[operandsIdx--];
            float lastFoundOperand1 = operands[operandsIdx--];
            char lastOperatorFound = operators[operatorsIdx--];

            float result = 0;
            bool done = solve(lastFoundOperand1, lastFoundOperand2, lastOperatorFound, &result);
            if (!done) {
                cout << "Operation: " << lastFoundOperand1 << " " << lastOperatorFound << " " << lastFoundOperand2 << " not allowed!" << endl;
                return -1; // sau false, ca nu s-a putut rezolva
            }

            operands[++operandsIdx] = result;
        }

        return operands[operandsIdx];
    }

    explicit operator int() const 
    {
        float rezultat = parseAndCompute(expresie);
        return static_cast<int>(rezultat);
    }


};



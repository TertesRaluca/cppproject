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

    Calculator(const Calculator& c)
    {
        if (c.expresie != nullptr)
        {
            if (this->expresie != nullptr)
            {
                delete[] this->expresie;
            }
            this->expresie = new char[strlen(c.expresie) + 1];
            strcpy_s(this->expresie, strlen(c.expresie) + 1, c.expresie);
        }
        else
            this->expresie = nullptr;
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

    Calculator& operator=(const Calculator& other) {
        if (this != &other) { 
           
            if (expresie != nullptr) {
                delete[] expresie;
            }

            
            if (other.expresie != nullptr) {
                expresie = new char[strlen(other.expresie) + 1];
                strcpy_s(expresie, strlen(other.expresie) + 1, other.expresie);
            }
            else {
                expresie = nullptr;
            }
        }
        return *this; 
    }

    ~Calculator()
    {
        if (this->expresie != nullptr)
            delete[] this->expresie;
    }

    explicit operator int() const 
    {
       float rezultat = Compute(expresie);
        return static_cast<int>(rezultat);
    }

    Calculator operator+(const Calculator& other) const {
       
        float rezultat1 = Compute(this->expresie);
        float rezultat2 = Compute(other.expresie);
        float suma = rezultat1 + rezultat2;
        string nouaExpresie = to_string(suma);
        return Calculator(nouaExpresie.c_str());
    }

    static bool solve(float operand1, float operand2, char op, float* result) {
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

   bool calculate(const float* operands, const char* operators, int n_operands, int n_operators, float* res) {
       float* operandsToProcess = new float[n_operands];
       char* operatorsToProcess = new char[n_operators];

       int operandsToProcessIdx = -1; 
       int operatorsToProcessIdx = -1;

       int operatorsIdx = 0;
       int operandsIdx = 0;

       
       operandsToProcess[++operandsToProcessIdx] = operands[operandsIdx++];
       operatorsToProcess[++operatorsToProcessIdx] = operators[operatorsIdx++];
       while (operatorsIdx <= n_operators && operandsIdx <= n_operands) {
           char currentOperator = operatorsToProcess[operatorsToProcessIdx];
           char nextOperator = operators[operatorsIdx];

           if (currentOperator == '[' || currentOperator == '(') {
               if (nextOperator == '[' || nextOperator == '(') {
                   operatorsToProcess[++operatorsToProcessIdx] = nextOperator;
                   operatorsIdx++;
               }
               else {
                   operandsToProcess[++operandsToProcessIdx] = operands[operandsIdx++];
                   operatorsToProcess[++operatorsToProcessIdx] = nextOperator;
                   operatorsIdx++;
               }
           }
           else if (!(currentOperator == ']' || currentOperator == ')')) {
               if (!(nextOperator == '[' || nextOperator == '(' || nextOperator == ']' || nextOperator == ')')) {
                  
                   if (((currentOperator == '+' || currentOperator == '-') && (nextOperator == '*' || nextOperator == '/'))
                       || ((currentOperator == '+' || currentOperator == '-') && (nextOperator == '#' || nextOperator == '^'))
                       || ((currentOperator == '*' || currentOperator == '/') && (nextOperator == '#' || nextOperator == '^'))) {
                       operandsToProcess[++operandsToProcessIdx] = operands[operandsIdx++];
                       operatorsToProcess[++operatorsToProcessIdx] = nextOperator;
                       operatorsIdx++;
                       continue;
                   }
                   else {
                       float operand2 = operands[operandsIdx++];
                       float operand1 = operandsToProcess[operandsToProcessIdx--];
                       operatorsToProcessIdx--; 
                       float result = 0;
                       bool done = solve(operand1, operand2, currentOperator, &result);

                       if (!done) {
                           cout << "Operation: " << operand1 << " " << currentOperator << " " << operand2 << " not allowed!" << endl;
                           return false;
                       }

                      
                       operandsToProcess[++operandsToProcessIdx] = result;

                       operatorsToProcess[++operatorsToProcessIdx] = nextOperator;
                       operatorsIdx++;
                   }
               }
               else if (nextOperator == '[' || nextOperator == '(') {
                   operatorsToProcess[++operatorsToProcessIdx] = nextOperator;
                   operatorsIdx++;
               }
               else {
                   operandsToProcess[++operandsToProcessIdx] = operands[operandsIdx++];
                   operatorsToProcess[++operatorsToProcessIdx] = nextOperator;

                   operatorsIdx++;
               }
           }
           else {
               
               char lastFoundOperator = operatorsToProcess[--operatorsToProcessIdx];
               while (lastFoundOperator != '(' && lastFoundOperator != '[') {
                   float lastFoundOperand2 = operandsToProcess[operandsToProcessIdx--];
                   float lastFoundOperand1 = operandsToProcess[operandsToProcessIdx--];

                   float result = 0;
                   bool done = solve(lastFoundOperand1, lastFoundOperand2, lastFoundOperator, &result);

                   if (!done) {
                       cout << "Operation: " << lastFoundOperand1 << " " << lastFoundOperator << " " << lastFoundOperand2 << " not allowed!" << endl;
                       return false;
                   }

                   
                   operandsToProcess[++operandsToProcessIdx] = result;
                   lastFoundOperator = operatorsToProcess[--operatorsToProcessIdx];
               }
               operatorsToProcessIdx--;

               char operationBeforeParanthesis = operatorsToProcess[operatorsToProcessIdx];

              
               if (operationBeforeParanthesis == '-') {
                   operatorsToProcess[operatorsToProcessIdx] = '+';
                   operandsToProcess[operandsToProcessIdx] = 0 - operandsToProcess[operandsToProcessIdx];
               }

               char operationAfterParanthesis = nextOperator;

               if (((operationAfterParanthesis == '+' || operationAfterParanthesis == '-') && (operationBeforeParanthesis == '*' || operationBeforeParanthesis == '/'))
                   || ((operationAfterParanthesis == '+' || operationAfterParanthesis == '-') && (operationBeforeParanthesis == '#' || operationBeforeParanthesis == '^'))
                   || ((operationAfterParanthesis == '*' || operationAfterParanthesis == '/') && (operationBeforeParanthesis == '#' || operationBeforeParanthesis == '^'))
                   || ((operationAfterParanthesis == '+' || operationAfterParanthesis == '-') && (operationBeforeParanthesis == '+' || operationBeforeParanthesis == '-'))
                   || ((operationAfterParanthesis == '*' || operationAfterParanthesis == '/') && (operationBeforeParanthesis == '*' || operationBeforeParanthesis == '/'))
                   || ((operationAfterParanthesis == '^' || operationAfterParanthesis == '#') && (operationBeforeParanthesis == '^' || operationBeforeParanthesis == '#'))) {
                   operatorsToProcessIdx--;
                   float lastFoundOperand2 = operandsToProcess[operandsToProcessIdx--];
                   float lastFoundOperand1 = operandsToProcess[operandsToProcessIdx--];

                   float result = 0;
                   bool done = solve(lastFoundOperand1, lastFoundOperand2, operationBeforeParanthesis, &result);

                   if (!done) {
                       cout << "Operation: " << lastFoundOperand1 << " " << operationBeforeParanthesis << " " << lastFoundOperand2 << " not allowed!" << endl;
                       return false;
                   }

                   
                   operandsToProcess[++operandsToProcessIdx] = result;
               }

               operatorsToProcess[++operatorsToProcessIdx] = nextOperator;
               operatorsIdx++;
           }
       }

       while (operatorsIdx <= n_operators) {
           operatorsToProcess[++operatorsToProcessIdx] = operators[operatorsIdx++];
       }

       while (operandsIdx <= n_operands) {
           operandsToProcess[++operandsToProcessIdx] = operands[operandsIdx++];
       }

       while (operatorsToProcessIdx > -1) {
           char _operator = operatorsToProcess[operatorsToProcessIdx--];
           float _operand2 = operandsToProcess[operandsToProcessIdx--];
           float _operand1 = operandsToProcess[operandsToProcessIdx--];

           float result = 0;
           bool done = solve(_operand1, _operand2, _operator, &result);

           if (!done) {
               cout << "Operation: " << _operand1 << " " << _operator << " " << _operand2 << " not allowed!" << endl;
               return false;
           }
           operandsToProcess[++operandsToProcessIdx] = result;
       }

       *res = operandsToProcess[operandsToProcessIdx];

       return true;
   }


    static  float Compute(const char* str) {
        float* operands = new float[strlen(str)]();
        char* operators = new char[strlen(str)];

        int operandsIdx = -1; 
        int operatorsIdx = -1;

        
        char* currentOperand = new char[strlen(str)];
        int currentOperandIndex = 0;

       
        char* openParantheses = new char[strlen(str)];
        int paranthesesIdx = -1;
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
                    operands[++operandsIdx] = operand; 

                    
                    memset(currentOperand, 0, strlen(str));
                    currentOperandIndex = 0;
                }
                else {
                    
                    if (currentFoundOperator == '-') {
                       
                        operands[++operandsIdx] = 0;
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }
                }

                
                if (currentFoundOperator == '(' || currentFoundOperator == ')' || currentFoundOperator == '[' || currentFoundOperator == ']') {
                    
                    if (currentFoundOperator == '(' || currentFoundOperator == '[') {
                        openParantheses[++paranthesesIdx] = currentFoundOperator;

                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                   
                    if (paranthesesIdx == -1) {
                        
                        cout << "Wrong parantheses alignment!" << endl;
                        return -1; 
                    }
                    else {
                        char lastOpenParanthesis = openParantheses[paranthesesIdx--];

                        
                        if ((lastOpenParanthesis == '(' && currentFoundOperator == ']')
                            || (lastOpenParanthesis == '[' && currentFoundOperator == ')')) {
                            cout << "Wrong parantheses alignment!" << endl;
                            return -1; 
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
                            return -1; 
                        }

                        operands[++operandsIdx] = result;

                        lastFoundOperator = operators[operatorsIdx--];
                    }
                }
                else {
                    
                    if (operatorsIdx == -1) {
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                    char lastFoundOperator = operators[operatorsIdx];

                   
                    if (lastFoundOperator == '(' || lastFoundOperator == '[') {
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                   
                    if (((lastFoundOperator == '+' || lastFoundOperator == '-') && (currentFoundOperator == '*' || currentFoundOperator == '/'))
                        || ((lastFoundOperator == '+' || lastFoundOperator == '-') && (currentFoundOperator == '#' || currentFoundOperator == '^'))
                        || ((lastFoundOperator == '*' || lastFoundOperator == '/') && (currentFoundOperator == '#' || currentFoundOperator == '^'))) {
                        operators[++operatorsIdx] = currentFoundOperator;
                        continue;
                    }

                  
                    float lastFoundOperand2 = operands[operandsIdx--];
                    float lastFoundOperand1 = operands[operandsIdx--];

                    
                    operatorsIdx--;

                    float result = 0;
                    bool done = solve(lastFoundOperand1, lastFoundOperand2, lastFoundOperator, &result);

                    if (!done) {
                        cout << "Operation: " << lastFoundOperand1 << " " << lastFoundOperator << " " << lastFoundOperand2 << " not allowed!" << endl;
                        return -1; 
                    }

                    
                    operands[++operandsIdx] = result;

                    
                    operators[++operatorsIdx] = currentFoundOperator;
                }
            }

        }

        
        if (paranthesesIdx != -1) {
            cout << "Unclosed parantheses!" << endl;
            return -1;
        }

        
        if (currentOperandIndex != 0) {
            float operand = stringToFloat(currentOperand);
            operands[++operandsIdx] = operand; 

            delete[] currentOperand;
        }

        
        while (operatorsIdx != -1) {

            
            float lastFoundOperand2 = operands[operandsIdx--];
            float lastFoundOperand1 = operands[operandsIdx--];
            char lastOperatorFound = operators[operatorsIdx--];

            float result = 0;
            bool done = solve(lastFoundOperand1, lastFoundOperand2, lastOperatorFound, &result);
            if (!done) {
                cout << "Operation: " << lastFoundOperand1 << " " << lastOperatorFound << " " << lastFoundOperand2 << " not allowed!" << endl;
                return -1; 
            }

            operands[++operandsIdx] = result;
        }

        return operands[operandsIdx];
    }

};

istream& operator>>(istream& in, Calculator& c)
{
    cout << "Introduceti expresia: ";
    string copie;
    getline(in, copie);

    c.setExpresie(copie.c_str());

    return in;

}

ostream& operator<<(ostream& out, Calculator& c)
{
    out << "Expresie care trebuie evaluata: ";
    out << c.getExpresie();
    return out;
}




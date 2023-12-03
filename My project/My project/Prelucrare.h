#pragma once
#include<iostream>
#include<stdio.h>
#include<string>

using namespace std;

class Eliminare
{
    char* expresie;

    const static int maxExpresie;

public:
    Eliminare()
    {
        this->expresie = nullptr;
    }

    Eliminare(const char* vector)
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

    static char* parse(const char* str)
    {
        char* parsed_exp = new char[strlen(str)+1];
        int parsedExpIdx = -1;

        // Pentru verificarea parantezelor
        char* openParantheses = new char[strlen(str)];
        int paranthesesIdx = -1;
        for (int i = 0; i < strlen(str); i++) {
            // Daca e spatiu, continuam cu urmatorul caracter
            if (str[i] == ' ') {
                continue;
            }

            // Retinem in noua expresie
            parsed_exp[++parsedExpIdx] = str[i];

            // Retinem parantezele deschise pe masura ce le intalnim
            if (str[i] == '(' || str[i] == '[') {
                openParantheses[++paranthesesIdx] = str[i];
                continue;
            }

            /*
                Altfel, daca este inchisa,
                verificam intai daca inchiderea se face corect
            */
            if (str[i] == ')' || str[i] == ']') {
                if (paranthesesIdx == -1) {
                    /*
                        Daca am gasit o paranteza inchisa fara pereche,
                        returnam eroare
                    */
                    cout << "Wrong parantheses alignment - closed paranthesis without opening one" << endl;
                    return nullptr;
                }
                else {
                    char lastOpenParanthesis = openParantheses[paranthesesIdx--];

                    /*
                        Daca nu e inchisa corect, returnam eroare
                    */
                    if ((lastOpenParanthesis == '(' && str[i] == ']')
                        || (lastOpenParanthesis == '[' && str[i] == ')')) {
                        cout << "Wrong parantheses alignment - open and close paranthesis don't match" << endl;
                        return nullptr;
                    }
                }
            }
        }

        /*
            Daca mai avem paranteze deschise
            care nu au fost inchise,
            returnam eroare
        */
        if (paranthesesIdx != -1) {
            cout << "Unclosed parantheses" << endl;
            return nullptr;
        }

        parsed_exp[++parsedExpIdx] = '\0';
        return parsed_exp;
    }


    ~Eliminare()
    {
        if (this->expresie != nullptr)
            delete[] this->expresie;
    }

    bool operator!() const {
        if (expresie == nullptr) {
            return true; 
        }

        for (int i = 0; expresie[i] != '\0'; i++) {
            if (expresie[i] == '(' || expresie[i] == ')' ||
                expresie[i] == '[' || expresie[i] == ']') {
                return false; 
            }
        }
        return true; 
    }

};

const int Eliminare::maxExpresie = 35;

istream& operator>>(istream& in, Ecuatie& e)
{
        cout << "Introduceti expresia: ";
        string copie;
        getline(in, copie);

        e.setExpresie(copie.c_str());

        return in;
    
}

ostream& operator<<(ostream& out, Ecuatie& e)
{
    out << "Expresie care trebuie evaluata: ";
    out << e.getExpresie();
    return out;
}




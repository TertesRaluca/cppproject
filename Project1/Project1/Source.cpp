
Conversa?ie deschis?. 4 mesaje.Toate mesajele au fost citite.

Treci la con?inut
Se folose?te E - mail Academia de Studii Economice din Bucure?ti cu cititoare de ecran
in : sent

7 din 43
seminar 5 PO
Mesaje primite

Cristina - Raluca TERTES < tertescristina22@stud.ase.ro>
31 oct. 2023, 11:57
c?tre Ioana - Ruxandra, tertesraluca1, Diana

#include<iostream>
#include<string>

using namespace std;


enum TipAuto { SCUTER, DUBA, AUTO }; ///ENUM CLASS=ENUM

class Util {
public:
	static string* copiereVector(string* vector, int nrElemente) {
		if (vector == nullptr) {
			return nullptr;
		}

		string* vectorNou = new string[nrElemente];
		for (int i = 0; i < nrElemente; i++) {
			vectorNou[i] = vector[i];
		}
		return vectorNou;
	}

	static void printVectorString(string* vector, int n) {
		if (vector == nullptr)
		{
			cout << endl << "Vectorul nu are valori";
		}
		else {

			cout << endl << "vector: ";
			for (int i = 0; i < n; i++)
				cout << " " << vector[i];
		}
	}

};

class Curier {
	string nume = ""; ///trebuie sa punem valori by default
	string* traseulLivrari = nullptr;  ///string*=char**
	int nrLocatii = 0;
	int nrPachete = 0;
	TipAuto autoLivrare = TipAuto::AUTO;


public:
	string getNume() {
		return this->nume;
	}

	string* getTraseu() {
		//nu aasa
		//return this-> traseullivrari
		return Util::copiereVector(
			this->traseulLivrari, this->nrLocatii);
	}



	int getNrLocatii() {
		return this->nrPachete;
	}

	TipAuto getTipAuto() {
		return this->autoLivrare;
	}

	void setNume(string nume) {
		//shadowing  nume=nume
		this->nume = nume;
	}

	void setNrPachete(int nrPachete) {
		if (nrPachete < 0) {
			throw exception("numar negativ");
		}
		this->nrPachete = nrPachete;
	}


	void setTraseu(string* traseu, int nrLocatii) {
		delete[] this->traseulLivrari;
		this->traseulLivrari = Util::copiereVector(traseu, nrLocatii);
		this->nrLocatii = nrLocatii;
	}

	void setTipAuto(TipAuto tip) {
		this->autoLivrare = tip;
	}

	//constructori- acestia construiesc obiectul
	/*Curier() {

	this->setNume("Anonim");
	}*/
	//evitam constructorii default

	Curier(string nume, TipAuto tip = TipAuto::AUTO) {
		this->setNume(nume);
		this->setTipAuto(tip);
	}

	Curier(string nume, TipAuto tip, int nrPachete, string* locatii, int nrLocatii) :nume(nume), autoLivrare(tip) {
		this->setTraseu(locatii, nrLocatii);
		this->setNrPachete(nrPachete);

	}

	//destructori
	Curier() {

		delete[] this->traseulLivrari;

	}

};


int main() {

	Curier curier;

	curier.setNume("Gigek");
	string locatii[] = { "Piata Victorie", "Piata Unrii", "Universitate", "Unirea" };
	int nrlocatii = 4;
	curier.setTraseu(locatii, nrlocatii);
	curier.setNrPachete(16);
	curier.setTipAuto(TipAuto::DUBA);

	cout << endl << "nume curier " << curier.getNume();
	string* traseu = curier.getTraseu();
	Util::printVectorString(traseu, curier.getNrLocatii());
	delete[] traseu;

	{
		Curier c2("Nu stiu");
	}
	//aici testam destructorii
	Curier* pCurier = new Curier("BOB");
	delete pCurier;

}






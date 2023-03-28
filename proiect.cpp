//Aplicatie pentru gestiunea vânzărilor unui magazin ca mulțime de vânzări individuale(cod produs, denumire, preț unitar, cantitate), pe zile calendaristice.
//Aplicația permite calculul totalului valoric al vânzărilor magazinului pe o perioada, zilele cu incasarile cele mai mari, respectiv cele mai mici.





#include<iostream>
#include<vector>
#include<fstream>
#include <utility>
using namespace std;

#define MAX_TIME_UNIT 365


class Exceptie
{
	string mesajExceptie;

public:
	Exceptie(string mesajExceptie)
	{
		this->mesajExceptie = mesajExceptie;
	}

	string getMesajExceptie()
	{
		return mesajExceptie;
	}
};

class ScriereCitire
{
public:
	virtual void scrieInFisierBinar(fstream& fisier) = 0;
	virtual void citesteDinFisierBinar(fstream& fisier) = 0;
};


class Produs 
{
private:
	const int cod_produs;
	char* denumire;
	int pret_unitar;
	int cantitate;
	static int nrProduse;

public:

	Produs():cod_produs(nrProduse++) 
	{
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->pret_unitar = 0;
		this->cantitate = 0;
	}

	Produs(const char* denumire, int pret_unitar, int cantitate) :cod_produs(nrProduse++)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret_unitar = pret_unitar;
		this->cantitate = cantitate;
	}

	Produs(const Produs& p):cod_produs(nrProduse++)
	{
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret_unitar = p.pret_unitar;
		this->cantitate = p.cantitate;
	}

	Produs operator=(const Produs& p)
	{
		if (p.denumire != NULL)
		{
			if (this->denumire != NULL)
			{
				delete[] this->denumire;
			}
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		this->pret_unitar = p.pret_unitar;
		this->cantitate = p.cantitate;
		
		return *this;
	}

	Produs operator++()
	{
		this->pret_unitar++;
		return *this;
	}

	Produs operator++(int)
	{
		Produs aux = *this;
		this->pret_unitar++;
		return aux;
	}

	operator int()
	{
		return cantitate*pret_unitar;
	}

	Produs operator+(Produs p)
	{
		Produs result = *this;
		result.cantitate= this->cantitate + p.cantitate;
		return result;
	}

	Produs operator-(Produs p)
	{
		Produs result = *this;
		result.cantitate = this->cantitate - p.cantitate;
		return result;
	}

	Produs operator+=(Produs p)
	{
		this->cantitate += p.cantitate;
		return *this;
	}

	bool operator!=(Produs p)
	{
		if (strcmp(this->denumire, p.denumire) == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator<(Produs p)
	{
		if (this->cantitate < p.cantitate)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*char* getDenumire()
	{
		return this->denumire;
	}*/

	int getPret()
	{
		return pret_unitar;
	}

	int getCantitate()
	{
		return cantitate;
	}

	virtual char* getDenumire()
	{
		return denumire;
	}

	void setDenumire(const char* denumireNoua) 
	{
		if (strlen(denumireNoua) > 2) 
		{
			delete[] this->denumire;
		}
		this->denumire = new char[strlen(denumireNoua) + 1]; 
		strcpy(this->denumire, denumireNoua); 
	}

	void setPret(int pretNou)
	{
		this->pret_unitar = pretNou;
	}

	void setCantitate(int cantitateNoua)
	{
		this->cantitate = cantitateNoua;
	}


	friend istream& operator>>(istream& in, Produs& p)
	{
		cout << "Denumire produs: ";
		in >> p.denumire;
		cout << "Pret produs: ";
		in >> p.pret_unitar;
		cout << "Cantitate produs: ";
		in >> p.cantitate;

		return in;
	}
	
	
	friend ifstream& operator>>(ifstream& ifs, Produs& p)
	{

		ifs >> p.denumire;
		ifs >> p.pret_unitar;
		ifs >> p.cantitate;
		
		return ifs;
	}


	friend ofstream& operator<<(ofstream& ofs, Produs& p)
	{

		ofs << p.denumire<<endl;
		ofs << p.pret_unitar<<endl;
		ofs << p.cantitate<<endl;

		return ofs;
	}


	friend ostream& operator<<(ostream& out, Produs& p)
	{
		out << "Cod produs: " << p.cod_produs << endl;
		out << "Denumire produs: " << p.denumire << endl;
		out << "Pret produs: " << p.pret_unitar << endl;
		out << "Cantitate produs: " << p.cantitate << endl;

		return out;
	}


	~Produs()
	{

		delete[]this->denumire;
		
	}

};

int Produs::nrProduse = 1;


class Produs1 : public Produs
{
private:
	
	char* denumire;
	;
public:
	Produs1()
	{
		this->denumire = new char[strlen("Alin") + 1];
		strcpy(this->denumire, "Alin");
	}

	char* getDenumire() override
	{
		return denumire;
	}
};

void afiseaza(Produs* a)
{
	cout << "Produsul: " << a->getDenumire() << endl;
}




class ProdusPremium : public Produs
{
private:
	string tipProdus;
	string culoare;


public:
	ProdusPremium() :Produs()
	{
		tipProdus = "Anonim";
		culoare = "Anonima";
		
	}

	ProdusPremium(const char* denumire, int pret_unitar, int cantitate,
		string tipProdus, string culoare) :Produs(denumire, pret_unitar, cantitate)
	{
		this->tipProdus = tipProdus;
		this->culoare = culoare;
		
	}

	ProdusPremium(const ProdusPremium& pr) :Produs(pr)
	{
		this->tipProdus = pr.tipProdus;
		this->culoare = pr.culoare;
	
	}

	ProdusPremium operator=(const ProdusPremium& pr)
	{
		Produs::operator=(pr);
		this->tipProdus = pr.tipProdus;
		this->culoare = pr.culoare;
		return *this;
	}

	friend ostream& operator<<(ostream& out, ProdusPremium& pr)
	{
		out << (Produs&)pr;
		out << endl << "Tip produs: " << pr.tipProdus;
		out << endl << "Culoare produs: " << pr.culoare;
		
		return out;
	}

	friend istream& operator>>(istream& in, ProdusPremium& pr)
	{
		in >> (Produs&)pr;
		cout << "Tip produs: ";
		in >> pr.tipProdus;
		cout << "Culoare produs: ";
		in >> pr.culoare;
		
		return in;
	}

	
};




class Magazin {
	
private:

	vector<vector<Produs>> cantitate_vanduta;
	
public:

	

	Magazin() {
		this->cantitate_vanduta = vector<vector<Produs>>(MAX_TIME_UNIT);
	}

	void add(Produs p, int zi) {
		if (zi < 1 || zi > MAX_TIME_UNIT) {
			throw Exceptie("Nu ati introdus o zi calendaristica");
		}

		this->cantitate_vanduta[zi - 1].push_back(p);
	}


	int valoare_zi(int zi) {

		int sum = 0;

		for (auto& produs : cantitate_vanduta[zi]) {
			sum = sum + produs.getPret() * produs.getCantitate();
		}

		return sum;
	}



	void total_vanzari() {
		for (int i = 0; i < MAX_TIME_UNIT; i++) {
			cout << "Ziua " << i + 1 << ", total: " << valoare_zi(i) << endl;
		}
	}

	void total_vanzari(int ziua1, int ziua365) {
		if (ziua1 <= 0 || ziua365 > MAX_TIME_UNIT) {
			throw Exceptie("Nu ati introdus o zi calendaristica");
		}

		int total = 0;

		for (int i = ziua1 - 1; i < ziua365; i++) {
			cout << "Ziua " << i + 1 << ", total: " << valoare_zi(i) << endl;
			total = total + valoare_zi(i);
		}
		cout << "Total vanzari: " << total << endl;
	}

	void maxim() {
		int z = -1;
		int max = 0;

		for (int i = 0; i < MAX_TIME_UNIT; i++) {
			int s = valoare_zi(i);

			if (s > max) {
				max = s;
				z = i;
			}
		}

		cout << "Cea mai buna zi a fost ziua " << z + 1 << " cu total: " << max << endl;
	}

	void maxim(int ziua1, int ziua365) {
		int z = -1;
		int max = 0;

		for (int i = ziua1 - 1; i < ziua365; i++) {
			int s = valoare_zi(i);

			if (s > z) {
				max = s;
				 z = i;
			}
		}

		cout << "Cea mai buna zi a fost ziua " << z + 1 << " cu total: " << max << endl;
	}

	void minim() {
		int z = -1;
		int min = valoare_zi(0);

		for (int i = 1; i < MAX_TIME_UNIT; i++) {
			int s = valoare_zi(i);

			if (s < min) {
				min = s;
				z = i;
			}
		}

		cout << "Cea mai slaba zi a fost ziua " << z + 1 << " cu total: " << min << endl;
	}

	void minim(int ziua1, int ziua365) {
		int z = ziua1 - 1;
		int min = valoare_zi(ziua1 - 1);

		for (int i = ziua1; i < ziua365; i++) {
			 int s = valoare_zi(i);

			if (s < min) {
				min = s;
				z = i;
			}
		}

		cout << "Cea mai slaba zi a fost ziua " << z + 1 << " cu total: " << min << endl;
	}


};
 
void meniu()
{
	
	cout << "\n Menu Aplicatie ";
	cout << "\n========";
	cout << "\n 1 - Total_Vanzari";
	cout << "\n 2 - Zi_Productiva";
	cout << "\n 3 - Zi_Slaba";
	cout << "\n X - Exit";
	cout << "\n Inntroduceti cifra/text: ";


	char selection;
	int zistart;
	int zifinal;
	cin >> selection;

	Produs p1;
	Produs p2;
	Produs p3;
	Produs p4;
	Produs p5;
	Produs p6;
	ifstream fileIn("produse.txt", ios::in);
	fileIn >> p1;
	fileIn >> p2;
	fileIn >> p3;
	fileIn >> p4;
	fileIn >> p5;
	fileIn >> p6;
	fileIn.close();

	ofstream fileOut("produse1.txt", ios::out);
	fileOut << p1;
	fileOut << p2;
	fileOut << p3;
	fileOut << p4;
	fileOut << p5;
	fileOut << p6;
	fileOut.close();

	p1++;
	p2 += p3;


	Magazin cantitate_vanduta;

	cantitate_vanduta.add(p1, 1);
	cantitate_vanduta.add(p2, 2);
	cantitate_vanduta.add(p4, 3);
	cantitate_vanduta.add(p5, 4);
	cantitate_vanduta.add(p2, 4);
	cantitate_vanduta.add(p4, 4);
	cantitate_vanduta.add(p1, 5);
	cantitate_vanduta.add(p3, 5);
	cantitate_vanduta.add(p4, 6);
	cantitate_vanduta.add(p2, 6);
	cantitate_vanduta.add(p3, 6);
	cantitate_vanduta.add(p5, 7);
	cantitate_vanduta.add(p2, 8);
	cantitate_vanduta.add(p1, 8);
	cantitate_vanduta.add(p2, 8);
	cantitate_vanduta.add(p3, 8);
	cantitate_vanduta.add(p1, 8);
	cantitate_vanduta.add(p5, 9);
	cantitate_vanduta.add(p1, 10);
	cantitate_vanduta.add(p2, 10);
	cantitate_vanduta.add(p3, 10);
	cantitate_vanduta.add(p6, 8);
	cantitate_vanduta.add(p6, 8);

	


	switch (selection)
	{


	case '1':

	case 't': 
	{
		
		cout << "Dati zilele pentru care sa se calculeze suma tuturor vanzarilor in fiecare zi, facandu-se suma tuturor vanzarilor in acea perioada " << endl;
		cin >> zistart >> zifinal;
		cantitate_vanduta.total_vanzari(zistart, zifinal); 
	}
	break;


	case '2':

	case 'm': 
	{
		
		cout << "Dati zilele pentru care sa se calculeze suma tuturor vanzarilor in fiecare zi si sa se determine ziua cea mai productiva" << endl;
		cin >> zistart >> zifinal;
		cantitate_vanduta.maxim(zistart, zifinal); 
	}
	break;



	case '3':

	case 'i': 
	{
		cout << "Dati zilele pentru care sa se calculeze suma tuturor vanzarilor in fiecare zi si sa se determine ziua cea mai neproductiva " << endl;
		cin >> zistart >> zifinal;
		cantitate_vanduta.minim(zistart, zifinal); 
	}
	break;



	case 'X':

	case 'x': {cout << "\n Exit"; }

			break;
	
	default: cout << "\n Sectiune Invalida";


	}

	cout << "\n";


}
void main()
{

	meniu();
	/*ProdusPremium p6("Produs6",80,1,"Elux","Verde");
	cout << p6;*/

}

#ifndef FUNKCJE_H
#define FUNKCJE_H
class Statystyki {
public:
	double robotnicy;
	double zasoby;
	double urzadzenia;
	int tura;
};
class Pieniadze
{
public:
	double budzet;
};
class Zyski {
public:
	double output;
};
class Wydatki{
public:
	double utrzymanie_robotnicy;
	double utrzymanie_prad;
};
class Ulepszenia{
public:
	double ulepszenie_prad = 1;
	double ulepszenie_kawa = 1;
	double ulepszenie_sprzet = 1;
};
class Wynik{
public:
	double wynik;
};
class WynikGry : public Wynik{
public:
	std::pair<int, double> para;
};
bool WczytajPlik(std::string statystyki_poczatkowe, Statystyki& StatFab, Pieniadze& Pln);
void obliczWynik(Wynik& End, Statystyki& StatFab, Pieniadze& Pln);
void wpiszPara(WynikGry& EndGame, Statystyki& StatFab);
void wypiszKoncowyWynik(WynikGry EndGame);
void calculateStats(Statystyki& StatFab, Pieniadze& Pln, Zyski& Stonks, Wydatki& Loss, Ulepszenia& Upgrade);
void showStats(Statystyki& StatFab, Pieniadze& Pln);
void losoweWydarzenie(Statystyki& StatFab, Pieniadze& Pln);
void sklep(Statystyki& StatFab, Pieniadze& Pln, Ulepszenia& Upgrade);
#endif
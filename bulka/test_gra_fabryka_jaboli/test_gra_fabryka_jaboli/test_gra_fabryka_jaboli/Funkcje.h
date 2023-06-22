#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "komorka.h"
#include "wektor.h"

class Statystyki {
public:
	double robotnicy;
	double zasoby;
	double urzadzenia;
	int tura;
	Statystyki(double worker, double supply, double machine, double turn);
	Statystyki() = default;
};
class Pieniadze
{
public:
	double budzet;
	Pieniadze(double money);
	Pieniadze() = default;
};
class Zyski {
public:
	double output;
	Zyski(double zarobki);
	Zyski() = default;
};
class Wydatki{
public:
	double utrzymanie_robotnicy;
	double utrzymanie_prad;
	Wydatki(double loss_work, double loss_power);
	Wydatki() = default;
};
class Ulepszenia{
public:
	double ulepszenie_prad = 1;
	double ulepszenie_kawa = 1;
	double ulepszenie_sprzet = 1;
	Ulepszenia(double upg_power, double upg_coffe, double upg_mach);
	Ulepszenia() = default;
};
class Wynik{
public:
	double score;
	double endscore;
	Wynik(double wynik, double wynikKoncowy);
	Wynik() = default;
};
class WynikGry : public Wynik{
public:
	Wektor<double> zapiszScore;
	WynikGry(Wektor<double> saveScore);
	WynikGry() = default;
};
bool WczytajPlik(std::string statystyki_poczatkowe, Statystyki& StatFab, Pieniadze& Pln, Ulepszenia Upgrade, WynikGry End);
void calculateStats(Statystyki& StatFab, Pieniadze& Pln, Zyski& Stonks, Wydatki& Loss, Ulepszenia& Upgrade);
void showStats(Statystyki& StatFab, Pieniadze& Pln);
void losoweWydarzenie(Statystyki& StatFab, Pieniadze& Pln);
void sklep(Statystyki& StatFab, Pieniadze& Pln, Ulepszenia& Upgrade);
void obliczWynik(WynikGry& End, Statystyki& StatFab, Pieniadze& Pln);
void wpiszTablica(WynikGry& End);
void wypiszKoncowyWynik(WynikGry& EndGame);
void zapiszGre(Statystyki& StatFab, Pieniadze& Pln, Ulepszenia& Upgrade, WynikGry& End);
#endif
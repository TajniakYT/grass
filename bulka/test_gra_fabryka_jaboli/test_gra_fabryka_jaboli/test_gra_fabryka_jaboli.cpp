#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <list>
#include "Funkcje.h"

int main()
{
	Pieniadze Pln;
	Statystyki StatFab;
	Zyski Stonks;
	Wydatki Loss;
	Ulepszenia Upgrade;
	WynikGry EndGame;
	StatFab.tura=0;

	WczytajPlik("statystyki_poczatkowe.txt", StatFab, Pln);

	for (StatFab.tura = 0; StatFab.tura < 50; StatFab.tura++)
	{
		calculateStats(StatFab, Pln, Stonks, Loss, Upgrade);

		std::cout << "Tura: " << StatFab.tura + 1 << " obecne wydarzenia:" << std::endl;
		showStats(StatFab, Pln);
		if (Pln.budzet < 0)
		{
			std::cout << "Bankrupcja, przegrales gre" << std::endl;
			break;
		}
		losoweWydarzenie(StatFab, Pln);
		showStats(StatFab, Pln);
		if (Pln.budzet < 0)
		{
			std::cout << "Bankrupcja, przegrales gre" << std::endl;
			break;
		}
		sklep(StatFab, Pln, Upgrade);
	}
	if (StatFab.tura == 50) {
		std::cout << "Gratulacje, ukonczylej gre i udalo ci sie przezyc kryzys ekonomiczny i nawet cos zarobiles" << std::endl;
	}

	obliczWynik(EndGame, StatFab, Pln);
	wpiszPara(EndGame, StatFab);
	wypiszKoncowyWynik(EndGame);
}
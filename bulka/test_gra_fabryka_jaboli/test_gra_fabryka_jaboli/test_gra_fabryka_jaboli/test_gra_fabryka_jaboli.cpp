#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "komorka.h"
#include "wektor.h"
#include "Funkcje.h"

Statystyki StatFab;
Pieniadze Pln;
Zyski Stonks;
Wydatki Loss;
Ulepszenia Upgrade;
WynikGry End;

int main()
{
	int odczyt;

	std::cout << "Witaj w grze symulator fabryki, nacisnij 1 jezeli chcesz zaczac nowa gre, nacisnij 2 jezeli chcesz wczytac zapis" << std::endl;
	for (int i = 0; i < 5000; i++)
	{
		std::cin >> odczyt;
		if (odczyt != 1 && odczyt != 2)
			std::cout << "Podano nie porawna wartosc, spobuj ponownie" << std::endl;
		else
			break;
	}
	if (odczyt == 1)
	{
		WczytajPlik("statystyki_poczatkowe.txt", StatFab, Pln, Upgrade, End);
		std::ofstream plik;
		plik.open("zapis.txt", std::ofstream::out | std::ofstream::trunc);
		plik.close();
	}
	else if (odczyt == 2)
	{
		WczytajPlik("zapis.txt", StatFab, Pln, Upgrade, End);
	}

	for (StatFab.tura; StatFab.tura < 50; StatFab.tura++)
	{
		calculateStats(StatFab, Pln, Stonks, Loss, Upgrade);
		obliczWynik(End, StatFab, Pln);
		wpiszTablica(End);

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
		std::cout << "Czy chcesz zapisac gre i wyjsc? 1-tak, 2-nie" << std::endl;
		for (int i = 0; i < 5000; i++)
		{
			std::cin >> odczyt;
			if (odczyt != 1 && odczyt != 2)
				std::cout << "Podano nie porawna wartosc, spobuj ponownie" << std::endl;
			else
				break;
		}
		if (odczyt == 1)
		{
			zapiszGre(StatFab, Pln, Upgrade, End);
			exit;
		}
		else if (odczyt == 2)
		{

		}
	}
	if (StatFab.tura == 50) {
		std::cout << "Gratulacje, ukonczylej gre i udalo ci sie przezyc kryzys ekonomiczny i nawet cos zarobiles" << std::endl;
	}
	wypiszKoncowyWynik(End);
}
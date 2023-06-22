#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "komorka.h"
#include "wektor.h"
#include "Funkcje.h"

Statystyki::Statystyki(double worker, double supply, double machine, double turn)
{
	robotnicy = worker;
	zasoby = supply;
	urzadzenia = machine;
	tura = turn;
}

Pieniadze::Pieniadze(double money)
{
	budzet = money;
}

Zyski::Zyski(double zarobki)
{
	output = zarobki;
}

Wydatki::Wydatki(double loss_work, double loss_power)
{
	utrzymanie_robotnicy = loss_work;
	utrzymanie_prad = loss_power;
}

Ulepszenia::Ulepszenia(double upg_power, double upg_coffe, double upg_mach)
{
	ulepszenie_prad = upg_power;
	ulepszenie_kawa = upg_coffe;
	ulepszenie_sprzet = upg_mach;
}

Wynik::Wynik(double wynik, double wynikKoncowy) {
	score = wynik;
	endscore = wynikKoncowy;
}

WynikGry::WynikGry(Wektor<double> saveScore) : Wynik(0.0, 0.0)
{
	zapiszScore = saveScore;
}

bool WczytajPlik(std::string statystyki_poczatkowe, Statystyki& StatFab, Pieniadze& Pln, Ulepszenia Upgrade, WynikGry End)
{
	std::ifstream plik;
	plik.open(statystyki_poczatkowe.c_str());
	if (!plik.good())
		return false;
	while (true)
	{
		double O_pln;
		double O_rob;
		double O_zas;
		double O_urz;
		double O_tur;
		double O_up1;
		double O_up2;
		double O_up3;
		double O_wyn;
		plik >> O_pln >> O_rob >> O_zas >> O_urz >> O_tur >> O_up1 >> O_up2 >> O_up3 >> O_wyn;
		if (!plik.fail())
		{
			Pln.budzet = O_pln;
			StatFab.robotnicy = O_rob;
			StatFab.zasoby = O_zas;
			StatFab.urzadzenia = O_urz;
			StatFab.tura = O_tur;
			Upgrade.ulepszenie_prad = O_up1;
			Upgrade.ulepszenie_kawa = O_up2;
			Upgrade.ulepszenie_sprzet = O_up3;
			End.endscore = O_wyn;
		}
		else
			break;
	}
	return true;

}

void calculateStats(Statystyki& StatFab, Pieniadze& Pln, Zyski& Stonks, Wydatki& Loss, Ulepszenia& Upgrade)
{
	if ((StatFab.robotnicy / StatFab.urzadzenia >= 4) && StatFab.zasoby >= (StatFab.urzadzenia * 5))
		Stonks.output = StatFab.robotnicy * StatFab.urzadzenia * 300 * Upgrade.ulepszenie_kawa * Upgrade.ulepszenie_sprzet;
	else if ((StatFab.robotnicy / StatFab.urzadzenia < 4) && StatFab.zasoby >= (StatFab.urzadzenia * 5))
		Stonks.output = ((StatFab.robotnicy / StatFab.urzadzenia) / 4) * StatFab.robotnicy * StatFab.urzadzenia * 300 * Upgrade.ulepszenie_kawa * Upgrade.ulepszenie_sprzet;
	else if ((StatFab.robotnicy / StatFab.urzadzenia < 4) && (StatFab.zasoby < (StatFab.urzadzenia * 5) && StatFab.zasoby>0))
		Stonks.output = StatFab.robotnicy * ((StatFab.zasoby / StatFab.urzadzenia) / 5) * StatFab.urzadzenia * 300 * Upgrade.ulepszenie_kawa * Upgrade.ulepszenie_sprzet;
	else if ((StatFab.robotnicy / StatFab.urzadzenia < 4) && (StatFab.zasoby < (StatFab.urzadzenia * 5) && StatFab.zasoby>0))
		Stonks.output = ((StatFab.robotnicy / StatFab.urzadzenia) / 4) * ((StatFab.zasoby / StatFab.urzadzenia) / 5) * StatFab.robotnicy * StatFab.urzadzenia * 300 * Upgrade.ulepszenie_kawa * Upgrade.ulepszenie_sprzet;
	else
		Stonks.output = 0;
	StatFab.zasoby = StatFab.zasoby - (StatFab.urzadzenia * 5);
	Loss.utrzymanie_prad = (10 + StatFab.urzadzenia * 5) * 150 * Upgrade.ulepszenie_prad;
	Loss.utrzymanie_robotnicy = StatFab.robotnicy * 300;
	Pln.budzet = Pln.budzet + Stonks.output - Loss.utrzymanie_prad - Loss.utrzymanie_robotnicy;
}

void showStats(Statystyki& StatFab, Pieniadze& Pln)
{
	if (StatFab.robotnicy < 0)
		StatFab.robotnicy = 0;
	if (StatFab.zasoby < 0)
		StatFab.zasoby = 0;
	if (StatFab.urzadzenia < 0)
		StatFab.urzadzenia = 0;

	std::cout << "Balans budzetu: " << Pln.budzet << " Robotnicy: " << StatFab.robotnicy << " Zasoby: " << StatFab.zasoby << " Urzadzenia: " << StatFab.urzadzenia << std::endl;
}

void losoweWydarzenie(Statystyki& StatFab, Pieniadze& Pln)
{
	int liczba = rand() % 100;
	int choice;

	if (liczba <= 14)
	{
		StatFab.urzadzenia = StatFab.urzadzenia - 1;
		std::cout << "awaria sprzetu, tracisz 1 urzadzenie" << std::endl;
	}
	else if (liczba >= 15 && liczba <= 29)
	{
		Pln.budzet = Pln.budzet + 1000;
		std::cout << "Inwestorzy ciebie wspieraja, +1000 pieniedzy" << std::endl;
	}
	else if (liczba >= 30 && liczba <= 44)
	{
		Pln.budzet = Pln.budzet - 1000;
		std::cout << "inwesstorzy wycofuja sie, -1000 pieniedzy" << std::endl;
	}
	else if (liczba >= 45 && liczba <= 59)
	{
		StatFab.zasoby = StatFab.zasoby - 10;
		std::cout << "Nasze zasoby produkcyjne zostaly ukradzione, -10 zasobow" << std::endl;
	}
	else if (liczba >= 60 && liczba <= 69)
	{
		std::cout << "Robotnicy strajkuja, domagaja sie lepszych warunkow pracy i lepszej placy. Co robimy?" << std::endl;
		std::cout << "Opcja 1: Dajmy im pieniadze aby byli cicho (utracimy czesc pieniedzy od ilosci robotnikow)" << std::endl;
		std::cout << "Opcja 2: Negocjacje, moze sie powioda albo beda porazka (20% szans na nic, 40% utrata pieniedzy, 40% utrata pracownikow)" << std::endl;
		std::cout << "Opcja 3: Nie ma zadnych strakow (utrata duzej ilosci pracownikow)" << std::endl;
		std::cout << "Wpisz liczbe 1, 2 lub 3 aby wybrac jedno z wydarzen" << std::endl;
		for (int i = 0; i < 5000; i++)
		{
			std::cin >> choice;
			if (choice >= 1 && choice <= 3)
				break;

			std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
		}
		switch (choice) {
		case(1):
		{
			Pln.budzet = Pln.budzet - (StatFab.robotnicy * 15);
			std::cout << "Po wyplacie pieniedzy robotnicy przestali marudzic i wrocili do pracy" << std::endl;
			break;
		}
		case(2):
		{
			int negocjacje = rand() % 10;
			if (negocjacje <= 2)
			{
				std::cout << "Strajkujacy uznali ze wiecej zarobia pracujac niz strajkujac, nic sie nie dzieje" << std::endl;
			}
			else if (negocjacje >= 3 && negocjacje <= 6)
			{
				Pln.budzet = Pln.budzet - (StatFab.robotnicy * 10);
				std::cout << "Doszilismy do umowy, damy im czesc pieniedzy a beda dalej pracowac" << std::endl;
			}
			else
			{
				StatFab.robotnicy = StatFab.robotnicy - 4;
				std::cout << "Neocjacje sie nie powiodly i czesc pracownikow odeszla" << std::endl;
			}
			break;
		}
		case(3):
		{
			StatFab.robotnicy = StatFab.robotnicy - 8;
			std::cout << "Duza ilosc pracownikow oburzona brakiem reakcji odeszla od fabryki" << std::endl;
			break;
		}
		}
	}
	else if (liczba >= 70 && liczba <= 79)
	{
		std::cout << "Pobliska fabryka bankruptuje i jej posiadlosci zostaja sprzedawane za niska cene" << std::endl;
		std::cout << "Opcja 1: Zarekrutujmy obecnie bezrobotnych pracownikow" << std::endl;
		std::cout << "Opcja 2: Wezmy czesc ich sprzetu" << std::endl;
		std::cout << "Opcja 3: Ich zasoby sie nam bardziej przydadza" << std::endl;
		std::cout << "Opcja 4: Inwestorzy teraz w nas zainwestuja" << std::endl;
		std::cout << "Wpisz liczbe 1, 2 ,3 lub 4 aby wybrac jedno z wydarzen" << std::endl;
		for (int i = 0; i < 5000; i++)
		{
			std::cin >> choice;
			if (choice >= 1 && choice <= 4)
				break;

			std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
		}
		switch (choice) {
		case(1):
		{
			StatFab.robotnicy = StatFab.robotnicy + 6;
			Pln.budzet = Pln.budzet - 2000;
			std::cout << "Zdesperowani pracownicy za nizsza cene akceptuja prace u nas" << std::endl;
			break;
		}
		case(2):
		{
			StatFab.urzadzenia = StatFab.urzadzenia + 2;
			Pln.budzet = Pln.budzet - 1500;
			std::cout << "Za nizsza cene zakupilismy ich sprzet do wytwarzania produktow" << std::endl;
			break;
		}
		case(3):
		{
			StatFab.zasoby = StatFab.zasoby + 40;
			Pln.budzet = Pln.budzet - 1500;
			std::cout << "Za nizsza cene zdobylismy zasoby potrzebne do produkcji" << std::endl;
			break;
		}
		case(4):
		{
			Pln.budzet = Pln.budzet + 4000;
			std::cout << "Inwestorzy teraz w nas inwestuja i mamy poparcie finansowe" << std::endl;
			break;
		}
		}
	}
	else
		std::cout << "Wszystko w normie" << std::endl;
}

void sklep(Statystyki& StatFab, Pieniadze& Pln, Ulepszenia& Upgrade)
{
	int odczyt;
	bool koniec = false;

	for (int i = 0; i < 10000; i++)
	{
		std::cout << "Czy potrzebujesz cos zakupic?" << std::endl;
		std::cout << "Nacisnij 1 aby kupic podstawowe materialy, 2 aby kupic ulepszenia, 3 aby wyjsc ze sklepu i przejsc do nastepnej tury" << std::endl;
		for (int i = 0; i < 5000; i++)
		{
			std::cin >> odczyt;
			if (odczyt >= 1 && odczyt <= 3)
				break;

			std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
		}
		switch (odczyt)
		{
		case(1):
		{
			std::cout << "Cennik kazdego zakupu:" << std::endl;
			std::cout << "1 zasob za 50 pieniedzy" << std::endl;
			std::cout << "1 urzadznie za 1000 pieniedzy" << std::endl;
			std::cout << "1 robotnik za 500 pieniedzy" << std::endl;
			std::cout << "Opcje 1, 2 i 3 prowadza do opcji zakupu podstawowych materialow, opcja 4 to powrot do glownego menu" << std::endl;
			for (int i = 0; i < 5000; i++)
			{
				std::cin >> odczyt;
				if (odczyt >= 1 && odczyt <= 4)
					break;

				std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
			}
			switch (odczyt)
			{
			case(1):
			{
				std::cout << "Ile chcesz kupic zasobow?" << std::endl;
				for (int i = 0; i < 5000; i++)
				{
					std::cin >> odczyt;
					if (odczyt >= 1)
						break;

					std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
				}
				if ((Pln.budzet - (odczyt * 50)) < 0)
				{
					std::cout << "Nie stac ciebie na to" << std::endl;
				}
				else
				{
					StatFab.zasoby = StatFab.zasoby + odczyt;
					std::cout << "Zakupiles " << odczyt << " zasobow" << std::endl;
					showStats(StatFab, Pln);
				}
				break;
			}
			case(2):
			{
				std::cout << "Ile chcesz kupic zasobow?" << std::endl;
				for (int i = 0; i < 5000; i++)
				{
					std::cin >> odczyt;
					if (odczyt >= 1)
						break;

					std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
				}
				if ((Pln.budzet - (odczyt * 1000)) < 0)
				{
					std::cout << "Nie stac ciebie na to" << std::endl;
				}
				else
				{
					StatFab.urzadzenia = StatFab.urzadzenia + odczyt;
					std::cout << "Zakupiles " << odczyt << " urzadzen" << std::endl;
					showStats(StatFab, Pln);
				}
				break;
			}
			case(3):
			{
				std::cout << "Ile chcesz kupic zasobow?" << std::endl;
				for (int i = 0; i < 5000; i++)
				{
					std::cin >> odczyt;
					if (odczyt >= 1)
						break;

					std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
				}
				if ((Pln.budzet - (odczyt * 500)) < 0)
				{
					std::cout << "Nie stac ciebie na to" << std::endl;
				}
				else
				{
					StatFab.robotnicy = StatFab.robotnicy + odczyt;
					std::cout << "Zakupiles " << odczyt << " robotnikow" << std::endl;
					showStats(StatFab, Pln);
				}
				break;
			}
			case(4):
			{
				break;
			}
			}
			break;
		}
		case(2):
		{
			std::cout << "Ka¿de z ulepszen kosztuje 10000" << std::endl;
			std::cout << "Wcisnij 1 aby zakupic ekspres do kawy, pracownicy beda efektywniej pracowac" << std::endl;
			std::cout << "Wcisnij 2 aby zakupic efektywniejsza instalacje elektryczna, zuzycie pradu mniejszone" << std::endl;
			std::cout << "Wcisnij 3 aby zakupic modernizacje maszyn, produkcja jest zwiekszona" << std::endl;
			std::cout << "Wcisnij 4 aby wyjsc z tego dzialu sklepu" << std::endl;
			for (int i = 0; i < 5000; i++)
			{
				std::cin >> odczyt;
				if (odczyt >= 1 && odczyt <= 4)
					break;

				std::cout << "Podano niepoprawna wartosc, sprobuj ponownie" << std::endl;
			}
			switch (odczyt)
			{
			case(1):
			{
				if ((Pln.budzet - 10000) < 0)
					std::cout << "Za malo pieniedzy aby kupic" << std::endl;
				else if (Upgrade.ulepszenie_kawa == 1.2)
					std::cout << "Ju¿ posiadasz to ulepszenie" << std::endl;
				else
				{
					Upgrade.ulepszenie_kawa = 1.2;
					std::cout << "Zakupiono ekspres do kawy" << std::endl;
				}
				break;
			}
			case(2):
			{
				if ((Pln.budzet - 10000) < 0)
					std::cout << "Za malo pieniedzy aby kupic" << std::endl;
				else if (Upgrade.ulepszenie_prad == 1.2)
					std::cout << "Ju¿ posiadasz to ulepszenie" << std::endl;
				else
				{
					Upgrade.ulepszenie_prad = 1.2;
					std::cout << "Zakupiono lepsza instalacje elektryczna" << std::endl;
				}
				break;
			}
			case(3):
			{
				if ((Pln.budzet - 10000) < 0)
					std::cout << "Za malo pieniedzy aby kupic" << std::endl;
				else if (Upgrade.ulepszenie_sprzet == 1.2)
					std::cout << "Ju¿ posiadasz to ulepszenie" << std::endl;
				else
				{
					Upgrade.ulepszenie_sprzet = 1.2;
					std::cout << "Zakupiono modernizacje sprzetu produkcyjnego" << std::endl;
				}
				break;
			}
			case(4):
			{
				break;
			}
			}
			break;
		}
		case(3):
		{
			koniec = true;
			break;
		}
		}
		if (koniec == true)
			break;
	}
}

void obliczWynik(WynikGry& End, Statystyki& StatFab, Pieniadze& Pln)
{
	End.score = StatFab.robotnicy + StatFab.urzadzenia + (Pln.budzet / 1000);
}

void wpiszTablica(WynikGry& End)
{
	End.zapiszScore.dodaj(End.score);
}

void wypiszKoncowyWynik(WynikGry& EndGame)
{
	EndGame.endscore = EndGame.zapiszScore.suma();
	std::cout << "twoj wynik to: " << EndGame.endscore << std::endl;
}

void zapiszGre(Statystyki& StatFab, Pieniadze& Pln, Ulepszenia& Upgrade, WynikGry& End)
{
	wypiszKoncowyWynik(End);
	std::ofstream plik;
	plik.open("zapis.txt");
	if (plik.is_open())
	{
		plik << Pln.budzet << ' ' << StatFab.robotnicy << ' ' << StatFab.zasoby << ' ' << StatFab.urzadzenia << ' ' << StatFab.tura << ' ' << Upgrade.ulepszenie_prad << ' ' << Upgrade.ulepszenie_kawa << ' ' << Upgrade.ulepszenie_sprzet << ' ' << End.endscore;
		return;
	}
	plik.close();
}
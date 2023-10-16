#include <iostream>
#include <fstream>

bool loadFile()
{
    std::ifstream file;
    char symbol;
    file.open("gwiazdy.txt");
    if (!file.good()) {
        std::cout << "Nie odczytano pliku" << std::endl;
        return false;
    }
    while (true) {
        while (file.get(symbol))
        {
            //wpisanie do wprowadzonej przez mnie listy
        }
    }
    file.close();
    return false;
}

bool saveFile()
{
    std::ofstream file;
    file.open("wyniki.txt");
    if (!file.good()) {
        std::cout << "Nie odczytano pliku" << std::endl;
        return false;
    }
    file << "W pliku bylo: " << ' ';//liczba elementow w liscie
    file << " elementow oraz w srod nich bylo: " << ' ';//liczba gwiazdek
    file << " gwiazdek";
    file.close();
}

int main()
{
    loadFile();
    //coś z liczeniem gwiazd
    saveFile();
}
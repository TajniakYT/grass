#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

class Time {
public:
    int year;
    int month;
    int day;
};

class DynamicArray {
    //tutaj struktóra za pomocą można potem wpisać dane z pliku
    //fajna będzie multimapa z iteratorem
};

int localTime()
{
    Time loctime;
    time_t now;
    struct tm timeInfo;
    time(&now);
    if (localtime_s(&timeInfo, &now) == 0)
    {
        loctime.year = 1900 + timeInfo.tm_year;
        loctime.month = 1 + timeInfo.tm_mon;
        loctime.day = timeInfo.tm_mday;
        std::cout << "Year: " << loctime.year << ", Month: " << loctime.month << ", Day: " << loctime.day << std::endl;
        return 0;
    }
}

bool loadFile()
{
    std::ifstream file;
    file.open("wydarzenia.txt");
    if (file.is_open())
    {
        //odczyt każdej lini za pomocą struktury dynamicznej
        return true;
    }
}

int main()
{
    localTime();
    loadFile();
    //pytanie czy chce wszystkie wydarzenia czy tylko ważne oraz po tym
    //ile lat i miesięcy w przód ma sprawdzić
    
    //funkcja, która oddczytuje te informacje które użytkownik chciał
    //wyswietl na ekranie
    //koniec zadania xd
}
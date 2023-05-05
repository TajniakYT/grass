// zdarzenia c++

#include <iostream>
#include <string>
#include <vector>

const char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};

class Walidator {
    public:
        std::vector<std::string> numer_telefonu;
        virtual bool validate(std::string verify){
            return false;
        }
};

class TelefonKom : public Walidator {
    //konkretny validatory w klasach dziedzicz¹cych, przyjmuj¹ce ³añcuchy (string) zwraca true/false
    char numer[numer_telefonu.size() + 1];

    if (char numer[0] = !'+') {
        validate;
    }
    else if (numer.size() = !12) {
        validate;
    }
    else {
        for (int i = 1; i < numer.size(); i++)
        {
            for (int z = 0, z < numbers.size(); z++)
            {
                if(numer[i]==numbers[z])
                    break
            }
            validate;
        }
    }
        
};

class Kwota : public Walidator {
    void kwota(int budzet) {
        if (budzet < 0) {
            validate;
        }
    }
};

class Email : public Walidator {
    void email(std::string mail) {
        if (mail.size() <= 0)
        {
            validate;
        }
    }

};

class TelefonStaat : public Walidator {

};

int main()
{
    
}
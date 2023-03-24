#include <iostream>

class LiczbyZespolone
{
    private:
        double Real, Imaginary;
    public:
        void set(double im, double re)
        {
            Real = re;
            Imaginary = im;
        }
        void get()
        {
            std::cout << "Licza zespolona: Re(" << Real << ") Im(" << Imaginary << ")" << std::endl;
        }
};

int main()
{
    
}
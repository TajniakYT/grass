#include <iostream>

class LiczbaZespolona {
    double real, imaginary;
    public:
        /*
        void set(double real, double imaginary)
        {
            double re = real;
            double im = imaginary;
        }
        */

        LiczbaZespolona(double real, double imaginary)
        {
            double re = real;
            double im = imaginary;
        }

        LiczbaZespolona wypisz(double real, double imaginary)
        {
            std::cout << "Rzeczywista: " << real << " Zmyslona: " << imaginary << std::endl;
        }

        inline LiczbaZespolona& operator = (const LiczbaZespolona& c)
        {
            if (this == &c)
                return *this;

            real = c.real;
            imaginary = c.imaginary;
        }

        inline LiczbaZespolona & operator += (const LiczbaZespolona& c)
        {
            real += c.real;
            imaginary += c.imaginary;

            return *this;
        }
        inline LiczbaZespolona& operator -= (const LiczbaZespolona& c)
        {
            real -= c.real;
            imaginary -= c.imaginary;

            return *this;
        }
};

int main()
{
    LiczbaZespolona a(3.5, 9);
    LiczbaZespolona b(12, 3.5);
    LiczbaZespolona c(6.7, 2.3);
    a += b;
    b -= c;
}
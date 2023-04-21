#include <iostream>

class Plane
{
public:
    double fuel, range, x, y, z, altitude;
    Plane(double fuel, double range, double x, double y, double z, double altitude)
    {
        fuel = fuel;
        range = range;
        x = x;
        y = y;
        z = z;
        altitude = altitude;
    }
    Plane() {
        fuel = 0.0;
        range = 0.0;
        x = 0.0;
        y = 0.0;
        z = 0.0;
        altitude = 0.0;
    }
    ~Plane() {
        std::cout << "Pilot uczyl sie zdalnie" << std::endl;
    }
};

void write(Plane flight)
{
    std::cout << "Fuel: " << flight.fuel << "L, Range: " << flight.range << "km" << std::endl;
    std::cout << "Coordinates: " << flight.x << ',' << flight.y << ',' << flight.z << " Altitude: " << flight.altitude << 'm' << std::endl;
}

Plane correct(Plane flight, double correct_height) {
    return(Plane(flight.fuel, flight. range, flight.x, flight.y, flight.z, flight. altitude+correct_height));
}

int main()
{
    Plane A760 = Plane();
    A760.fuel = 500.0;
    A760.range = 800.0;
    A760.x = 41.75;
    A760.y = -36.31;
    A760.z = 60.2;
    A760.altitude = 8000;
    double change = 500.0;
    correct(A760, change);
    write(A760);
}
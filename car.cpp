#include <iostream>
#include <string>
#include <vector>

// Base class
class Vehicle {
public:
    std::string brand;
    int horsepower;

    Vehicle(std::string b, int hp) : brand(b), horsepower(hp) {}
    virtual ~Vehicle() {}

    virtual void info() const {
        std::cout << brand << " (" << horsepower << " hp)";
    }
};

// Passenger car class
class PassengerCar : public Vehicle {
public:
    std::string bodyType;
    PassengerCar(std::string b, int hp, std::string body) 
        : Vehicle(b, hp), bodyType(body) {}

    void info() const override {
        Vehicle::info();
        std::cout << " [Body: " << bodyType << "]";
    }
};

// Truck class
class Truck : public Vehicle {
public:
    double payload; // in tons
    Truck(std::string b, int hp, double p) 
        : Vehicle(b, hp), payload(p) {}

    void info() const override {
        Vehicle::info();
        std::cout << " [Payload: " << payload << " t]";
    }
};

// Analyzer class to determine the category
class CarInspector {
public:
    static void classify(const Vehicle* v) {
        std::cout << "Classification for ";
        v->info();
        std::cout << " -> ";

        // Logic based on criteria
        if (v->horsepower > 300) {
            std::cout << "CATEGORY: Sport Monster" << std::endl;
        } 
        else if (const Truck* t = dynamic_cast<const Truck*>(v)) {
            if (t->payload > 10.0) {
                std::cout << "CATEGORY: Heavy Hauler" << std::endl;
            } else {
                std::cout << "CATEGORY: Light Commercial" << std::endl;
            }
        } 
        else if (const PassengerCar* p = dynamic_cast<const PassengerCar*>(v)) {
            if (p->horsepower < 150) {
                std::cout << "CATEGORY: Economy City Car" << std::endl;
            } else {
                std::cout << "CATEGORY: Standard Passenger" << std::endl;
            }
        }
    }
};

int main() {
    // No need for setlocale or system("chcp") anymore
    
    std::vector<Vehicle*> fleet;

    fleet.push_back(new PassengerCar("Porsche 911", 450, "Coupe"));
    fleet.push_back(new Truck("Kamaz", 280, 15.0));
    fleet.push_back(new PassengerCar("Renault Logan", 90, "Sedan"));
    fleet.push_back(new Truck("GAZelle", 120, 1.5));

    std::cout << "--- Fleet Analysis ---" << std::endl;
    for (const auto& vehicle : fleet) {
        CarInspector::classify(vehicle);
    }

    // Memory cleanup
    for (auto v : fleet) delete v;

    return 0;
}
 // добавил просто для проверки
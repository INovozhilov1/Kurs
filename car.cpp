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

// Motorcycle class
class Motorcycle : public Vehicle {
public:
    std::string type; // sport, cruiser, touring, etc.
    bool hasSidecar;

    Motorcycle(std::string b, int hp, std::string t, bool sidecar = false)
        : Vehicle(b, hp), type(t), hasSidecar(sidecar) {}

    void info() const override {
        Vehicle::info();
        std::cout << " [Type: " << type;
        if (hasSidecar) {
            std::cout << " + Sidecar";
        }
        std::cout << "]";
    }
};

//Bus
class Bus : public Vehicle {
public:
    int passengerCapacity;
    int numberOfAxles;
    bool hasWifi;

    Bus(std::string b, int hp, int capacity, int axles, bool wifi = false)
        : Vehicle(b, hp), passengerCapacity(capacity), numberOfAxles(axles), hasWifi(wifi) {}

    void info() const override {
        Vehicle::info();
        std::cout << " [Passengers: " << passengerCapacity;
        std::cout << ", Axles: " << numberOfAxles;
        if (hasWifi) {
            std::cout << ", WiFi: Yes";
        }
        std::cout << "]";
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
        else if (const Bus* b = dynamic_cast<const Bus*>(v)) {
            if (b->passengerCapacity > 50) {
                std::cout << "CATEGORY: Mega Bus (High Capacity)" << std::endl;
            } else if (b->hasWifi) {
                std::cout << "CATEGORY: Premium Tourist Bus" << std::endl;
            } else if (b->numberOfAxles > 2) {
                std::cout << "CATEGORY: Heavy-Duty Municipal Bus" << std::endl;
            } else {
                std::cout << "CATEGORY: Standard City Bus" << std::endl;
            }
        }
        else if (const Motorcycle* m = dynamic_cast<const Motorcycle*>(v)) {
            if (m->hasSidecar) {
                std::cout << "CATEGORY: Vintage/Utility Bike" << std::endl;
            } else if (m->horsepower > 150) {
                std::cout << "CATEGORY: Superbike" << std::endl;
            } else if (m->type == "Cruiser") {
                std::cout << "CATEGORY: Comfort Cruiser" << std::endl;
            } else {
                std::cout << "CATEGORY: Standard Commuter" << std::endl;
            }
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
        else {
            std::cout << "CATEGORY: Unknown Vehicle" << std::endl;
        }
    }
};

int main() {
    std::vector<Vehicle*> fleet;

    // Passenger cars
    fleet.push_back(new PassengerCar("Porsche 911", 450, "Coupe"));
    fleet.push_back(new PassengerCar("Renault Logan", 90, "Sedan"));
    
    // Trucks
    fleet.push_back(new Truck("Kamaz", 280, 15.0));
    fleet.push_back(new Truck("GAZelle", 120, 1.5));
    
    // Motorcycles
    fleet.push_back(new Motorcycle("Yamaha R1", 200, "Sport"));
    fleet.push_back(new Motorcycle("Harley Davidson", 85, "Cruiser"));
    fleet.push_back(new Motorcycle("Ural", 65, "Touring", true));
    
    // Buses (new additions)
    fleet.push_back(new Bus("Mercedes-Benz", 180, 35, 2, true));     // Tourist bus with WiFi
    fleet.push_back(new Bus("LIAZ", 250, 65, 3));                    // Large city bus
    fleet.push_back(new Bus("PAZ", 110, 22, 2));                     // Small shuttle bus
    fleet.push_back(new Bus("MAN Lion's Coach", 380, 55, 3, true)); // Long-distance coach

    std::cout << "--- Fleet Analysis ---" << std::endl;
    std::cout << "======================" << std::endl;
    for (const auto& vehicle : fleet) {
        CarInspector::classify(vehicle);
    }
    
    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "Total vehicles: " << fleet.size() << std::endl;

    // Memory cleanup
    for (auto v : fleet) delete v;

    return 0;
}
//все сделали в лучшем виде)
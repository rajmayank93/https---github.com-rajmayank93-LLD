#include <iostream>
#include <stdexcept> // For std::logic_error

using namespace std;
// LISKOV substitution
// If class B is a subclass of A , Then B could be replaced By any similar  object and it should run smoothly


// Bike interface
class Bike {
public:
    virtual void turnOnEngine() = 0;
    virtual void accelerate() = 0;
    virtual ~Bike() {}
};

// Motorcycle class implementing Bike interface
class Motorcycle : public Bike {
    bool isEngineOn;
    int speed;
public:
    Motorcycle() : isEngineOn(false), speed(0) {}

    void turnOnEngine() override {
        // Turn on the engine
        isEngineOn = true;
        cout << "Engine is turned on." << endl;
    }

    void accelerate() override {
        if (isEngineOn) {
            // Increase speed
            speed += 10;
            cout << "Accelerating. Current speed: " << speed << " km/h." << endl;
        } else {
            cout << "Can't accelerate. Engine is off." << endl;
        }
    }
};

// Bicycle class implementing Bike interface
class Bicycle : public Bike {
public:
    void turnOnEngine() override {
        throw logic_error("Bicycle has no engine");
    }

    void accelerate() override {
        // Implement bicycle-specific acceleration logic
        cout << "Pedaling faster. Bicycle is accelerating." << endl;
    }
};

// Example usage
int main() {
    Motorcycle myMotorcycle;
    Bicycle myBicycle;

    cout << "Motorcycle:" << endl;
    myMotorcycle.turnOnEngine(); // Turn on the engine
    myMotorcycle.accelerate();   // Accelerate

    cout << "\nBicycle:" << endl;
    try {
        myBicycle.turnOnEngine(); // Attempt to turn on engine
    } catch (const logic_error& e) {
        cout << e.what() << endl; // Handle exception
    }
    myBicycle.accelerate(); // Accelerate

    return 0;
}

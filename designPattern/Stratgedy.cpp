#include <iostream>
#include <memory>
#include <vector>

// Strategy Interface
class DriveStrategy {
public:
    virtual void drive() = 0;
    virtual ~DriveStrategy() = default;
};

// Sporty Drive Strategy
class SportyDrive : public DriveStrategy {
public:
    void drive() override {
        std::cout << "Driving sporty!" << std::endl;
    }
};

// Normal Drive Strategy
class NormalDrive : public DriveStrategy {
public:
    void drive() override {
        std::cout << "Driving normally." << std::endl;
    }
};

// Vehicle Context
class Vehicle {
private:
    DriveStrategy* driveStrategy;

public:
    Vehicle(DriveStrategy* strategy = nullptr) : driveStrategy(strategy) {}

    void setDriveStrategy(DriveStrategy* strategy) {
        delete driveStrategy;  // Clean up the old strategy
        driveStrategy = strategy;
    }

    void performDrive() {
        if (driveStrategy) {
            driveStrategy->drive();
        } else {
            std::cerr << "Drive strategy not set" << std::endl;
        }
    }

    ~Vehicle() {
        delete driveStrategy;
    }
};

// Sporty Car
class SportyCar : public Vehicle {
public:
    SportyCar() : Vehicle(new SportyDrive()) {}
};

// Normal Car
class NormalCar : public Vehicle {
public:
    NormalCar() : Vehicle(new NormalDrive()) {}
};

int main() {
    // Create a sporty car and perform a drive
    Vehicle* sportyCar = new SportyCar();
    sportyCar->performDrive();

    // Create a normal car and perform a drive
    Vehicle* normalCar = new NormalCar();
    normalCar->performDrive();

    // Change the driving strategy of the normal car to sporty driving
    normalCar->setDriveStrategy(new SportyDrive());
    normalCar->performDrive();

    // Clean up
    delete sportyCar;
    delete normalCar;

    return 0;
}

#include<iostream>

using namespace std;

//Interfaces should be such, that client should implement unnecessary functions they do not need

// WaiterInterface
class WaiterInterface {
public:
    virtual void serveCustomers() = 0;
    virtual void takeOrder() = 0;
    virtual ~WaiterInterface() {}
};

// ChefInterface
class ChefInterface {
public:
    virtual void cookFood() = 0;
    virtual void decideMenu() = 0;
    virtual ~ChefInterface() {}
};

// Waiter class implementing WaiterInterface
class Waiter : public WaiterInterface {
public:
    void serveCustomers() override {
        cout << "Serving the customer" << endl;
    }

    void takeOrder() override {
        cout << "Taking order from the customer" << endl;
    }
};

// Chef class implementing ChefInterface
class Chef : public ChefInterface {
public:
    void cookFood() override {
        cout << "Cooking food" << endl;
    }

    void decideMenu() override {
        cout << "Deciding the menu" << endl;
    }
};

// Example usage
int main() {
    Waiter waiter;
    Chef chef;

    cout << "Waiter:" << endl;
    waiter.serveCustomers(); // Serving the customer
    waiter.takeOrder();      // Taking order from the customer

    cout << "\nChef:" << endl;
    chef.cookFood();  // Cooking food
    chef.decideMenu(); // Deciding the menu

    return 0;
}
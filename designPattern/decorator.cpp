#include <iostream>

using namespace std;

// Base class
class BasePizza {
public:
    virtual int cost() const = 0; // Pure virtual function
    virtual ~BasePizza() = default; // Virtual destructor for proper cleanup
};

// Concrete components
class Margherita : public BasePizza {
public:
    int cost() const override {
        return 100;
    }
};

class VeggieDelight : public BasePizza {
public:
    int cost() const override {
        return 200;
    }
};

// Base Decorator
class Toppings : public BasePizza {
protected:
    BasePizza* basePizza;
public:
    Toppings(BasePizza* base) : basePizza(base) {}
    virtual ~Toppings() {
        delete basePizza; // Ensure the base pizza object is deleted to prevent memory leaks
    }
};

// Concrete Decorators
class ExtraCheese : public Toppings {
public:
    ExtraCheese(BasePizza* base) : Toppings(base) {}

    int cost() const override {
        return basePizza->cost() + 20;
    }
};

class Mushroom : public Toppings {
public:
    Mushroom(BasePizza* base) : Toppings(base) {}

    int cost() const override {
        return basePizza->cost() + 40;
    }
};

int main() {
    // Creating a Margherita pizza with extra cheese
    BasePizza* pizza = new ExtraCheese(new Margherita());
    cout << "Cost of Margherita with Extra Cheese: " << pizza->cost() << " units" << endl;
    delete pizza; // Clean up memory

    // Creating a VeggieDelight pizza with extra cheese and mushrooms
    pizza = new Mushroom(new ExtraCheese(new VeggieDelight()));
    cout << "Cost of Veggie Delight with Extra Cheese and Mushroom: " << pizza->cost() << " units" << endl;
    delete pizza; // Clean up memory

    return 0;
}

#include <iostream>

// Abstract Product A
class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;
    virtual void use() const = 0;
};

// Abstract Product B
class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;
    virtual void use() const = 0;
};

// Concrete Product A1
class ConcreteProductA1 : public AbstractProductA {
public:
    void use() const override {
        std::cout << "Using ConcreteProductA1\n";
    }
};

// Concrete Product A2
class ConcreteProductA2 : public AbstractProductA {
public:
    void use() const override {
        std::cout << "Using ConcreteProductA2\n";
    }
};

// Concrete Product B1
class ConcreteProductB1 : public AbstractProductB {
public:
    void use() const override {
        std::cout << "Using ConcreteProductB1\n";
    }
};

// Concrete Product B2
class ConcreteProductB2 : public AbstractProductB {
public:
    void use() const override {
        std::cout << "Using ConcreteProductB2\n";
    }
};

// Abstract Factory
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual AbstractProductA* createProductA() const = 0;
    virtual AbstractProductB* createProductB() const = 0;
};

// Concrete Factory 1
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* createProductA() const override {
        return new ConcreteProductA1();
    }
    
    AbstractProductB* createProductB() const override {
        return new ConcreteProductB1();
    }
};

// Concrete Factory 2
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* createProductA() const override {
        return new ConcreteProductA2();
    }
    
    AbstractProductB* createProductB() const override {
        return new ConcreteProductB2();
    }
};

// Client code
void clientCode(const AbstractFactory& factory) {
    AbstractProductA* productA = factory.createProductA();
    AbstractProductB* productB = factory.createProductB();
    productA->use();
    productB->use();
    delete productA;
    delete productB;
}

int main() {
    ConcreteFactory1 factory1;
    clientCode(factory1);

    ConcreteFactory2 factory2;
    clientCode(factory2);

    return 0;
}

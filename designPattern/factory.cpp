#include <iostream>

// Abstract Product
class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

// Concrete Product A
class ConcreteProductA : public Product {
public:
    void use() const override {
        std::cout << "Using ConcreteProductA\n";
    }
};

// Concrete Product B
class ConcreteProductB : public Product {
public:
    void use() const override {
        std::cout << "Using ConcreteProductB\n";
    }
};

// Abstract Creator
class Creator {
public:
    virtual ~Creator() = default;
    virtual Product* createProduct() const = 0;

    void someOperation() const {
        // Call the factory method to create a Product object.
        Product* product = this->createProduct();
        // Now, use the product.
        product->use();
        // Don't forget to delete the product to avoid memory leaks.
        delete product;
    }
};

// Concrete Creator A
class ConcreteCreatorA : public Creator {
public:
    Product* createProduct() const override {
        return new ConcreteProductA();
    }
};

// Concrete Creator B
class ConcreteCreatorB : public Creator {
public:
    Product* createProduct() const override {
        return new ConcreteProductB();
    }
};

int main() {
    Creator* creatorA = new ConcreteCreatorA();
    creatorA->someOperation();
    delete creatorA; // Clean up creator

    Creator* creatorB = new ConcreteCreatorB();
    creatorB->someOperation();
    delete creatorB; // Clean up creator

    return 0;
}

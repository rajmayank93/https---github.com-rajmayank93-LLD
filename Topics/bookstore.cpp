#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility> // for std::pair

// Book class
class Book {
public:
    Book(int id, const std::string& title, const std::string& author, double price)
        : id(id), title(title), author(author), price(price) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    double getPrice() const { return price; }

private:
    int id;
    std::string title;
    std::string author;
    double price;
};

// Customer class
class Customer {
public:
    Customer(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

    void addOrder(int orderId) { orders.push_back(orderId); }
    const std::vector<int>& getOrders() const { return orders; }

private:
    int id;
    std::string name;
    std::string email;
    std::vector<int> orders;
};

// Order class
class Order {
public:
    Order(int id, int customerId)
        : id(id), customerId(customerId), total(0.0) {}

    void addBook(const Book& book, int quantity) {
        books.push_back(std::make_pair(book, quantity));
        total += book.getPrice() * quantity;
    }

    int getId() const { return id; }
    int getCustomerId() const { return customerId; }
    double getTotal() const { return total; }
    const std::vector<std::pair<Book, int>>& getBooks() const { return books; }

private:
    int id;
    int customerId;
    std::vector<std::pair<Book, int>> books;
    double total;
};

// Bookstore class
class Bookstore {
public:
    void addBook(const Book& book) {
        books[book.getId()] = book;
    }

    void addCustomer(const Customer& customer) {
        customers[customer.getId()] = customer;
    }

    int createOrder(int customerId) {
        int orderId = nextOrderId++;
        orders[orderId] = Order(orderId, customerId);
        customers[customerId].addOrder(orderId);
        return orderId;
    }

    void addBookToOrder(int orderId, const Book& book, int quantity) {
        orders[orderId].addBook(book, quantity);
    }

    const std::unordered_map<int, Book>& getBooks() const { return books; }
    const std::unordered_map<int, Customer>& getCustomers() const { return customers; }
    const std::unordered_map<int, Order>& getOrders() const { return orders; }

private:
    std::unordered_map<int, Book> books;
    std::unordered_map<int, Customer> customers;
    std::unordered_map<int, Order> orders;
    int nextOrderId = 1;
};

// Client code
void clientCode(Bookstore& bookstore) {
    // Add books
    bookstore.addBook(Book(1, "The Catcher in the Rye", "J.D. Salinger", 10.99));
    bookstore.addBook(Book(2, "To Kill a Mockingbird", "Harper Lee", 12.99));

    // Add customers
    bookstore.addCustomer(Customer(1, "Alice", "alice@example.com"));
    bookstore.addCustomer(Customer(2, "Bob", "bob@example.com"));

    // Create an order for Alice
    int orderId = bookstore.createOrder(1);
    bookstore.addBookToOrder(orderId, bookstore.getBooks().at(1), 2);
    bookstore.addBookToOrder(orderId, bookstore.getBooks().at(2), 1);

    // Print order details
    const Order& order = bookstore.getOrders().at(orderId);
    std::cout << "Order ID: " << order.getId() << "\n";
    std::cout << "Customer ID: " << order.getCustomerId() << "\n";
    std::cout << "Total: $" << order.getTotal() << "\n";
    for (const auto& pair : order.getBooks()) {
        const Book& book = pair.first;
        int quantity = pair.second;
        std::cout << "Book: " << book.getTitle() << ", Quantity: " << quantity << "\n";
    }
}

int main() {
    Bookstore bookstore;
    clientCode(bookstore);
    return 0;
}

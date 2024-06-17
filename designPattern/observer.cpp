#include <bits/stdc++.h>

using namespace std;

// Observer Interface
class NotificationAlertObserver {
public:
    virtual void update() = 0;
    virtual ~NotificationAlertObserver() = default;
};

// Observable Interface
class StocksObservable {
public:
    virtual void add(NotificationAlertObserver* observer) = 0;
    virtual void remove(NotificationAlertObserver* observer) = 0;
    virtual void notifySubscribers() = 0;
    virtual void setStockCount(int newStockAdded) = 0;
    virtual int getStockCount() const = 0;
    virtual ~StocksObservable() = default;
};

// Concrete Observable
class Stock : public StocksObservable {
private:
    int stockCount;
    std::vector<NotificationAlertObserver*> observers;

public:
    Stock() : stockCount(0) {}

    void add(NotificationAlertObserver* observer) override {
        observers.push_back(observer);
    }

    void remove(NotificationAlertObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifySubscribers() override {
        for (NotificationAlertObserver* observer : observers) {
            observer->update();
        }
    }

    void setStockCount(int newStockAdded) override {
        stockCount += newStockAdded;
       notifySubscribers();
        
    }

    int getStockCount() const override {
        return stockCount;
    }
};

// Concrete Observer: EmailAlert
class EmailAlert : public NotificationAlertObserver {
private:
    std::string emailAddress;
    StocksObservable* stock;

public:
    EmailAlert(const std::string& email, StocksObservable* stock) 
        : emailAddress(email), stock(stock) {}

    void update() override {
        std::cout << "Email alert to " << emailAddress << ": Stock count is now " << stock->getStockCount() << std::endl;
    }
};

// Concrete Observer: SMSAlert
class SMSAlert : public NotificationAlertObserver {
private:
    std::string phoneNumber;
    StocksObservable* stock;

public:
    SMSAlert(const std::string& phone, StocksObservable* stock) 
        : phoneNumber(phone), stock(stock) {}

    void update() override {
        std::cout << "SMS alert to " << phoneNumber << ": Stock count is now " << stock->getStockCount() << std::endl;
    }
};

int main() {
    Stock stock;

    EmailAlert emailAlert("example@example.com", &stock);
    SMSAlert smsAlert("123-456-7890", &stock);

    stock.add(&emailAlert);
    stock.add(&smsAlert);

    stock.setStockCount(10);  // Notify all observers about the stock count change
    stock.setStockCount(0);  // Notify all observers about the stock count change

    stock.remove(&smsAlert);  // Remove SMS alert observer

    stock.setStockCount(30);  // Notify remaining observers about the stock count change

    return 0;
}

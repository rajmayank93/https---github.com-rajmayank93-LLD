#include<iostream>

using namespace std;

// open for modification and closed for modification


// Marker class
class Marker {
    string name;
    string color;
    int year;
    int price;
public:
    Marker(string name, string color, int year, int price) {
        this->name = name;
        this->color = color;
        this->year = year;
        this->price = price;
    }

    int getPrice() const {
        return price;
    }
};

// Invoice class
class Invoice {
    Marker marker;
    int qty;
public:
    Invoice(Marker marker, int qty) : marker(marker), qty(qty) {}

    int calculateTotal() const {
        return marker.getPrice() * qty;
    }
};
// interface
class Invoice{
    public:
    virtual ~Invoice(){}
    virtual void save(Invoice &invoice)=0;
};

class printdao : public Invoice{
public:
void save(Invoice &invoice) override{
    // print 
}

};

class savetoDBdao : public Invoice{
public:
void save(Invoice &invoice) override{
    // print 
}

};

int main(){
    
    return 0;
}

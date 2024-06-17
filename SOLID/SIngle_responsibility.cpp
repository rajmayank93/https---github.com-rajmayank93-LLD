#include<iostream>

using namespace std;

// single responsibility

class Marker{
    private:
    string name;
    string color;
    int year;
    int price;
public:
  Marker(string name, string color, int year, int price){
    this->name = name;
    this->color = color;
    this->year = year;
    this->price = price;
  }
  
  int getPrice() {
        return price;
    }
};

// NOT following Single Responsibilty
// class Invoice{
//     Marker marker;
//     int qty;

//     Invoice(Marker marker, int qty){
//         this->marker = marker;
//         this->qty = qty;
//     }

//     int Calculate(Marker marker, int qty){
//         return marker.price * qty;
//     }

//     void printInvoices(){
//         // print
//     }

//     void saveToDB(){
//         // save to DB
//     }
// }

// HOW to fix it 
class Invoice{
    Marker marker;
    int qty;
   public:
    Invoice(Marker marker, int qty){
        this->marker = marker;
        this->qty = qty;
    }
   
    int Calculate(Marker marker, int qty){
        return marker.getPrice() * qty;
    }
};

class Invoicedao{
    Invoice invoice;
    Invoicedao(Invoice invoice){
       this->invoice=invoice;
    }

    void printInvoices(){
        // print
    }

};

class InvoicePrinter{
Invoice invoice;
InvoicePrinter(Invoice invoice){
    this->invoice=invoice;
}

void saveToDB(){
    // save to db
}

};


int main(){
    
    return 0;
}

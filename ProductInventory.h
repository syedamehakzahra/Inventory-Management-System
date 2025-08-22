#pragma once

// ProductInventory.h
#pragma once
#ifndef PRODUCTINVENTORY_H // Changed guard name
#define PRODUCTINVENTORY_H // Changed guard name
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    string category;
    float price;
    int quantity;
    Product* next;
};

class ProductInventory {
    Product* head;
public:
    ProductInventory();
    ~ProductInventory(); // Destructor declaration
    void addProduct();
    void deleteProduct(int id); // Declaration for deleteProduct with parameter
    void updateProduct(int id); // Declaration for updateProduct with parameter
    void displayAll();
    void searchProduct();
    void loadFromFile();
    void saveToFile();
    Product*& getHead(); // getHead now returns a reference to Product*
};

#endif


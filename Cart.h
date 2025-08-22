#pragma once
#ifndef CART_H
#define CART_H

#include <stack>
#include <string>
#include "ProductInventory.h"

using namespace std;

struct CartItem {
    int id;
    string name;
    float price;
    int quantity;
};

class Cart {
private:
    stack<CartItem> cartStack;

public:
    void addToCart(Product* product);
    bool removeFromCart(int productId);
    void viewCart() const;
    void checkout();
    bool isEmpty() const;
    void clear();
    float calculateTotal() const;
};

#endif

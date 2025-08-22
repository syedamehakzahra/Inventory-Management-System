#include "Cart.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void Cart::addToCart(Product* product) {
    if (!product) {
        cout << "Invalid product.\n";
        return;
    }

    int qty;
    cout << "Enter quantity: ";
    cin >> qty;
    cin.ignore(1000, '\n');

    if (qty <= 0) {
        cout << "Quantity must be positive.\n";
        return;
    }

    if (qty > product->quantity) {
        cout << "Only " << product->quantity << " items available.\n";
        return;
    }

    stack<CartItem> tempStack;
    bool foundInCart = false;
    while (!cartStack.empty()) {
        CartItem item = cartStack.top();
        cartStack.pop();
        if (item.id == product->id) {
            item.quantity += qty;
            foundInCart = true;
        }
        tempStack.push(item);
    }
    while (!tempStack.empty()) {
        cartStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!foundInCart) {
        CartItem item = { product->id, product->name, product->price, qty };
        cartStack.push(item);
    }

    product->quantity -= qty;
    cout << "\n===============================================================================\n";
    cout << "--------------------------- ITEM ADDED TO CART -------------------------------\n";
    cout << "===============================================================================\n";
}

bool Cart::removeFromCart(int productId) {
    if (cartStack.empty()) {
        cout << "Cart is empty.\n";
        return false;
    }

    stack<CartItem> tempStack;
    bool found = false;

    while (!cartStack.empty()) {
        CartItem item = cartStack.top();
        cartStack.pop();
        if (item.id == productId) {
            cout << "\n===============================================================================\n";
            cout << "------------------------- PRODUCT REMOVED FROM CART----------------------------\n";
            cout << "===============================================================================\n";
            cout << "Removed: " << item.name << " x" << item.quantity << "\n";
            found = true;
        }
        else {
            tempStack.push(item);
        }
    }

    while (!tempStack.empty()) {
        cartStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found) {
        cout << "\n===============================================================================\n";
        cout << "---------------------- PRODUCT NOT FOUND IN CART -----------------------------\n";
        cout << "===============================================================================\n";
    }

    return found;
}

float Cart::calculateTotal() const {
    float total = 0;
    stack<CartItem> temp = cartStack;
    while (!temp.empty()) {
        CartItem item = temp.top();
        temp.pop();
        total += item.price * item.quantity;
    }
    return total;
}

void Cart::viewCart() const {
    if (cartStack.empty()) {
        cout << "\n===============================================================================\n";
        cout << "---------------------------- CART IS EMPTY -----------------------------------\n";
        cout << "===============================================================================\n";
        return;
    }

    stack<CartItem> temp = cartStack;
    float total = 0;

    cout << "\n===============================================================================\n";
    cout << "--------------------------- YOUR SHOPPING CART -------------------------------\n";
    cout << "===============================================================================\n";
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(10) << "Price"
        << setw(10) << "Qty"
        << setw(10) << "Total" << endl;
    cout << "-------------------------------------------------------------------------------\n";

    while (!temp.empty()) {
        CartItem item = temp.top();
        temp.pop();
        float itemTotal = item.price * item.quantity;
        total += itemTotal;
        cout << left << setw(10) << item.id
            << setw(20) << item.name
            << setw(10) << fixed << setprecision(2) << item.price
            << setw(10) << item.quantity
            << setw(10) << fixed << setprecision(2) << itemTotal << endl;
    }

    cout << "-------------------------------------------------------------------------------\n";
    cout << "Cart Total: Rs. " << fixed << setprecision(2) << total << "\n";
    cout << "===============================================================================\n";
}

void Cart::checkout() {
    if (cartStack.empty()) {
        cout << "\n===============================================================================\n";
        cout << "---------------------------- CART IS EMPTY -----------------------------------\n";
        cout << "===============================================================================\n";
        cout << "Nothing to checkout.\n";
        return;
    }

    ofstream receipt("receipt.txt");
    if (!receipt.is_open()) {
        cout << "Error: Could not create receipt.txt\n";
        return;
    }

    receipt << "================= RECEIPT =================\n";
    receipt << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(10) << "Qty"
        << setw(10) << "Price"
        << setw(10) << "Total" << "\n";
    receipt << "------------------------------------------\n";

    float grandTotal = 0;
    stack<CartItem> tempDisplayStack;
    while (!cartStack.empty()) {
        tempDisplayStack.push(cartStack.top());
        cartStack.pop();
    }

    stack<CartItem> tempProcessStack;
    while (!tempDisplayStack.empty()) {
        tempProcessStack.push(tempDisplayStack.top());
        tempDisplayStack.pop();
    }

    while (!tempProcessStack.empty()) {
        CartItem item = tempProcessStack.top();
        tempProcessStack.pop();
        float itemTotal = item.price * item.quantity;
        receipt << left << setw(10) << item.id
            << setw(20) << item.name
            << setw(10) << fixed << setprecision(2) << item.price
            << setw(10) << item.quantity
            << setw(10) << fixed << setprecision(2) << itemTotal << endl;
        grandTotal += itemTotal;
    }

    receipt << "---------------------------------------------------------\n";
    receipt << "\nGrand Total: Rs. " << fixed << setprecision(2) << grandTotal << endl;
    receipt.close();

    cout << "\n===============================================================================\n";
    cout << "----------------------------- CHECKOUT COMPLETE ------------------------------\n";
    cout << "===============================================================================\n";
    cout << "Receipt saved to 'receipt.txt'\n";
    cout << "Total Amount Paid: Rs. " << fixed << setprecision(2) << grandTotal << "\n";
    cout << "===============================================================================\n";

    clear();
}

bool Cart::isEmpty() const {
    return cartStack.empty();
}

void Cart::clear() {
    while (!cartStack.empty())
        cartStack.pop();
}

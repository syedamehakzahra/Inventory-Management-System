#include "ProductInventory.h" 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string> // Required for std::string and getline
// #include <limits> // Removed numeric_limits as requested
using namespace std;

ProductInventory::ProductInventory() {
    head = nullptr;
}

ProductInventory::~ProductInventory() { // Destructor implementation
    Product* current = head;
    while (current != nullptr) {
        Product* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr; // Ensure head is null after cleanup
}

Product*& ProductInventory::getHead() { // Ye function head ka reference return karta hai, jo linked list ka start hota hai, is liye class ke bahar se bhi head ko modify karna possible hota hai.
    return head;
}

void ProductInventory::addProduct() {
    cout << "\n==================================================================\n";
    cout << "\n----------------------- PRODUCT ADDITION -------------------------\n";
    cout << "====================================================================\n";
    Product* newProd = new Product();
    cout << "  Enter Product ID: ";
    cin >> newProd->id;
    cin.ignore(1000, '\n');   //Yeh line input stream (cin) se extra ya unwanted characters ko ignore karti hai — khas kar newline character ('\n') ko.
    cout << "  Enter Name: ";
    getline(cin, newProd->name);
    cout << "  Enter Category: ";
    getline(cin, newProd->category);
    cout << "  Enter Price: ";
    cin >> newProd->price;
    cout << "  Enter Quantity: ";
    cin >> newProd->quantity;
    newProd->next = nullptr;

    if (head == nullptr) {
        head = newProd;
    }
    else {
        Product* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newProd;
    }
    cout << "\n====================================================================================\n";
    cout << "--------------------------- PRODUCT SUCCESSFULLY ADDED -------------------------------\n";
    cout << "======================================================================================\n";
}


void ProductInventory::displayAll() {
    // Step 1: Remove duplicates based on ID
    Product* current = head;
    while (current != nullptr) {
        Product* runner = current;
        while (runner->next != nullptr) {
            if (runner->next->id == current->id) {
                // Duplicate found, delete it
                Product* duplicate = runner->next;
                runner->next = runner->next->next;
                delete duplicate;
            }
            else {
                runner = runner->next;
            }
        }
        current = current->next;
    }

    // Step 2: Display all remaining products
    if (head == nullptr)
    {
        cout << "\n==================================================================\n";
        cout << "---------------------------CURRENT INVENTORY ---------------------- \n";
        cout << "\n==================================================================\n";
        cout << "\n------------------------ EMPTY INVENTORY -------------------------\n";
        cout << "\n==================================================================\n";
        return;
    }

    Product* temp = head;
    cout << "\n=================================================================================\n";
    cout << "                         ALL PRODUCTS IN INVENTORY                         \n";
    cout << "=================================================================================\n";
    cout << "  ID   | Name                  | Category            | Price     | Quantity\n";
    cout << "-------|-----------------------|---------------------|-----------|---------\n";
    while (temp != nullptr) {
        cout << setw(6) << temp->id << " | "
            << setw(22) << left << temp->name << "| "
            << setw(19) << left << temp->category << "| "
            << setw(9) << right << fixed << setprecision(2) << temp->price << " | "
            << setw(7) << right << temp->quantity << "\n";
        temp = temp->next;
    }
    cout << "=================================================================================\n";
    cout << "\n";
}

void ProductInventory::deleteProduct(int id) {
    cout << "\n===================================================================\n";
    cout << "----------------------------DELETE PRODUCT---------------------------\n";
    cout << "\n===================================================================\n";
    if (head == nullptr)
    {
        cout << "\n==================================================================\n";
        cout << "\n------------------------ EMPTY INVENTORY -------------------------\n";
        cout << "\n==================================================================\n";
        return;
    }
    Product* temp = head;
    Product* prev = nullptr;

    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "===============================================================================\n";
        cout << "--------------------------- PRODUCT NOT FOUND ---------------------------------\n";
        cout << "===============================================================================\n";
        return;
    }
    if (prev == nullptr) {
        head = head->next;
    }
    else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "========================================================================================\n";
    cout << "--------------------------- PRODUCT SUCCESSFULLY DELETED -------------------------------\n";
    cout << "========================================================================================\n";
}

void ProductInventory::updateProduct(int id) { // Definition matching declaration
    cout << "\n==================================================================\n";
    cout << "----------------------------UPDATE PRODUCT--------------------------\n";
    cout << "\n==================================================================\n";
    Product* temp = head;
    while (temp != nullptr && temp->id != id)
    {
        temp = temp->next;
    }
    if (temp == nullptr)
    {
        cout << "==========================================\n";
        cout << "  Product with ID " << id << " not found.\n";
        cout << "==========================================\n";
        return;
    }
    cin.ignore(1000, '\n');
    cout << "  Found Product: " << temp->name << " (ID: " << temp->id << ")\n";
    cout << "--------------------------------\n";
    cout << "  Enter new name (current: " << temp->name << "): ";
    getline(cin, temp->name);
    cout << "  Enter new category (current: " << temp->category << "): ";
    getline(cin, temp->category);
    cout << "  Enter new price (current: " << temp->price << "): ";
    cin >> temp->price;
    cout << "  Enter new quantity (current: " << temp->quantity << "): ";
    cin >> temp->quantity;
    cout << "\n-=====================================================================================\n";
    cout << "--------------------------- PRODUCT SUCCESSFULLY UPDATED -------------------------------\n";
    cout << "========================================================================================\n";
}

// THIS IS THE MERGED/UPDATED searchProduct() FUNCTION
void ProductInventory::searchProduct() {
    cout << "\n==================================================================\n";
    cout << "-----------------------------SEARCH PRODUCT-------------------------\n";
    cout << "\n==================================================================\n";
    int choice;
    cout << "  Search by:\n";
    cout << "  1. ID\n";
    cout << "  2. Name\n";
    cout << "  3. Quantity\n";
    cout << "  Enter your choice: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    Product* temp = head;
    bool found = false;

    if (head == nullptr)
    {
        cout << "======================================================================\n";
        cout << "\n------------------------ EMPTY INVENTORY ---------------------------\n";
        cout << "======================================================================\n";
        return;
    }

    cout << "\n---------------------------------------------------------------------------------\n";
    cout << "                                 SEARCH RESULTS                                 \n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << "  ID   | Name                  | Category            | Price     | Quantity\n";
    cout << "-------|-----------------------|---------------------|-----------|---------\n";

    if (choice == 1) {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore(1000, '\n'); // Use 1000, '\n' for consistency
        while (temp) {
            if (temp->id == id) {
                // Print product details
                cout << temp->id << " " << temp->name << " " << temp->category << " " << temp->price << " " << temp->quantity << "\n";
                found = true;
                break; // Assuming ID is unique, no need to continue searching
            }
            temp = temp->next;
        }
    }
    else if (choice == 2) {
        string name;
        cout << "Enter Name: ";
        getline(cin, name);
        while (temp) {
            if (temp->name == name) {
                // Print product details
                cout << temp->id << " " << temp->name << " " << temp->category << " " << temp->price << " " << temp->quantity << "\n";
                found = true;
            }
            temp = temp->next;
        }
    }
    else if (choice == 3) {
        int qty;
        cout << "Enter Quantity: ";
        cin >> qty;
        cin.ignore(1000, '\n'); // Use 1000, '\n' for consistency
        while (temp) {
            if (temp->quantity == qty) {
                // Print product details
                cout << temp->id << " " << temp->name << " " << temp->category << " " << temp->price << " " << temp->quantity << "\n";
                found = true;
            }
            temp = temp->next;
        }
    }
    else {
        cout << "==========================================================================\n";
        cout << "--------------------------- INVALID OPTION -------------------------------\n";
        cout << "==========================================================================\n";
    } // No return here as it should still print "No matching product found" if nothing else happens

    if (!found) cout << "-------------------------------- NO MATCH FOUND ------------------------------------------\n";
}


void ProductInventory::loadFromFile() {
    ifstream file("inventory.txt");
    if (!file.is_open()) {
        cout << "=============================================================================================\n";
        cout << "-----------------------------ERROR OPENING FILE FOR LOADING-----------------------------------\n";
        cout << "=============================================================================================\n\n";
        return;
    }
    // Clear existing inventory before loading to avoid duplicates
    Product* current = head;
    while (current != nullptr) {
        Product* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    while (true) {
        Product* p = new Product();
        file >> p->id;
        if (file.eof()) {
            delete p;
            break;
        }
        file.ignore(1000, '\n'); // Clear buffer
        getline(file, p->name);
        getline(file, p->category);
        file >> p->price >> p->quantity;
        file.ignore(1000, '\n');

        p->next = nullptr;
        if (head == nullptr) {
            head = p;
        }
        else {
            Product* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = p;
        }
    }
    file.close();
    cout << "=============================================================================================\n";
    cout << "------------------------------- INVENTORY LOADED FROM FILE ----------------------------------\n";
    cout << "=============================================================================================\n";
}

void ProductInventory::saveToFile() {
    ofstream file("inventory.txt");
    if (!file.is_open()) {
        cout << "=============================================================================================\n";
        cout << "-----------------------------ERROR OPENING FILE FOR SAVING-----------------------------------\n";
        cout << "=============================================================================================\n";
        return;
    }
    Product* temp = head;
    while (temp != nullptr) {
        file << temp->id << "\n"
            << temp->name << "\n"
            << temp->category << "\n"
            << temp->price << " " << temp->quantity << "\n";
        temp = temp->next;
    }
    file.close();
    cout << "=============================================================================================\n";
    cout << "------------------------------- INVENTORY SAVED TO FILE -------------------------------------\n";
    cout << "=============================================================================================\n";
}

#include "Search.h"
#include <iostream>
#include <string> // Required for std::string and getline
using namespace std;

void searchProduct(Product* head) {
    int choice;
    cout << "\nSearch by:\n1. ID\n2. Name\n3. Quantity\nChoice: ";
    cin >> choice;
    cin.ignore(1000, '\n'); // Consistent cin.ignore

    Product* temp = head;
    bool found = false;

    if (head == nullptr) {
        cout << "Inventory is empty. Cannot search.\n";
        return;
    }

    if (choice == 1) {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore(1000, '\n');
        while (temp) {
            if (temp->id == id) {
                cout << "ID: " << temp->id << "\tName: " << temp->name << "\tCategory: " << temp->category << "\tPrice: " << temp->price << "\tQuantity: " << temp->quantity << "\n";
                found = true;
                break;
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
                cout << "ID: " << temp->id << "\tName: " << temp->name << "\tCategory: " << temp->category << "\tPrice: " << temp->price << "\tQuantity: " << temp->quantity << "\n";
                found = true;
            }
            temp = temp->next;
        }
    }
    else if (choice == 3) {
        int qty;
        cout << "Enter Quantity: ";
        cin >> qty;
        cin.ignore(1000, '\n');
        while (temp) {
            if (temp->quantity == qty) {
                cout << "ID: " << temp->id << "\tName: " << temp->name << "\tCategory: " << temp->category << "\tPrice: " << temp->price << "\tQuantity: " << temp->quantity << "\n";
                found = true;
            }
            temp = temp->next;
        }
    }
    else {
        cout << "Invalid choice.\n";
    }

    if (!found) cout << "No matching product found.\n";
}

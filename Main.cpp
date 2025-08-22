// main.cpp
#include <iostream>
// Added for std::fixed, std::setprecision, std::setw, std::left, tolower
#include <iomanip>
#include <string>
#include <fstream>

#include "ProductInventory.h"
#include "Cart.h"
#include "Search.h"

using namespace std;

// --- RECENTLY VIEWED PRODUCTS (Linked List) - Re-adding as it was part of the original request ---
// Since the prompt was to "put inventory statistics and recently viewed product functionality from second file to first file"
// and your *first* instruction was "YOU JUST HAVE TO PUT INVENTORY STATISTCS AND RECENTLY VIEWED PRODUCT FUNCTIONALITY FROM SECOND FILE TO FIRST FILE BUT MAKE SURE NO OTHER CHANGING OCCOUR"
// and the last main.cpp you sent *did not* have these, I am re-adding them based on your initial core request.
// If you want a truly barebones main.cpp with *only* the cart loop, please explicitly state "remove all other previously added features".

struct HistoryNode {
    int productId;
    HistoryNode* next;
    HistoryNode(int id) : productId(id), next(nullptr) {}
};

HistoryNode* historyHead = nullptr;
const int MAX_HISTORY = 5;
int historyCount = 0;

void addToHistory(int productId) {
    // Check if the product is already in history to avoid adding it again or moving to front
    HistoryNode* current = historyHead;
    HistoryNode* prev = nullptr;
    while (current != nullptr && current->productId != productId) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) { // Product found, move it to front
        if (prev != nullptr) { // If it's not already the head
            prev->next = current->next;
            current->next = historyHead;
            historyHead = current;
        }
    }
    else { // Product not found, add new node at start
        HistoryNode* newNode = new HistoryNode(productId);
        newNode->next = historyHead;
        historyHead = newNode;
        historyCount++;

        // If more than MAX_HISTORY, delete last node
        if (historyCount > MAX_HISTORY) {
            HistoryNode* temp = historyHead;
            for (int i = 1; i < MAX_HISTORY; i++) {
                if (temp->next == nullptr) break;
                temp = temp->next;
            }
            HistoryNode* toDelete = temp->next;
            temp->next = nullptr;
            delete toDelete;
            historyCount--;
        }
    }
}

void showHistory() {
    cout << "\n----- RECENTLY VIEWED PRODUCTS (latest first) -----\n";
    if (historyHead == nullptr) {
        cout << "No products viewed recently.\n";
        cout << "---------------------------------------------------\n\n";
        return;
    }
    HistoryNode* temp = historyHead;
    while (temp != nullptr) {
        cout << "Product ID: " << temp->productId << endl;
        temp = temp->next;
    }
    cout << "---------------------------------------------------\n\n";
}

void clearHistory() {
    while (historyHead != nullptr) {
        HistoryNode* temp = historyHead;
        historyHead = historyHead->next;
        delete temp;
    }
    historyCount = 0; // Reset count
}

// --- INVENTORY STATISTICS - Re-adding as it was part of the original request ---
void showInventoryStats(ProductInventory& inventory) {
    int totalProducts = 0;
    int totalQuantity = 0;
    double totalValue = 0.0;

    Product* temp = inventory.getHead();
    while (temp != nullptr) {
        totalProducts++;
        totalQuantity += temp->quantity;
        totalValue += (temp->price * temp->quantity);
        temp = temp->next;
    }

    cout << "\n----- INVENTORY STATISTICS -----\n";
    cout << "Total different products: " << totalProducts << endl;
    cout << "Total quantity of all products: " << totalQuantity << endl;
    cout << "Total inventory value: $" << fixed << setprecision(2) << totalValue << endl;
    cout << "--------------------------------\n\n";
}

void showMenu() {

    cout << "--------------------------\n";
    cout << "========== MENU ========== \n";
    cout << "--------------------------\n";
    cout << "1. ADD PRODUCT \n";
    cout << "--------------------------\n";
    cout << "2. DELETE PRODUCT\n";
    cout << "--------------------------\n";
    cout << "3. UPDATE PRODUCT\n";
    cout << "--------------------------\n";
    cout << "4. VIEW ALL PRODUCT\n";
    cout << "--------------------------\n";
    cout << "5. SEARCH PRODUCT\n";
    cout << "--------------------------\n";
    cout << "6. ADD TO CART \n";
    cout << "--------------------------\n";
    cout << "7. REMOVE PRODUCT FROM CART\n";
    cout << "--------------------------\n";
    cout << "8. VIEW CART\n";
    cout << "--------------------------\n";
    cout << "9. CHECKOUT\n";
    cout << "--------------------------\n";
    cout << "10. INVENTORY STATISTICS\n"; // Added
    cout << "--------------------------\n"; // Added
    cout << "11. RECENTLY VIEWED PRODUCTS\n"; // Added
    cout << "--------------------------\n"; // Added
    cout << "0. EXIT\n";
    cout << "--------------------------\n";

    cout << "\n=========================\n";
    cout << " ENTER YOUR CHOICE "; // Corrected typo
}

int main() {
    cout << "                                 |        |  __  __          __ __       ___                                  " << endl;
    cout << "                                 |  /\\    | |  | |  | |  / |  |  |  |    \t|      | |\\  |  | /  " << endl;
    cout << "                                 | /  \\   | |  | || |/  |__ ||  |___  \t|      | | \\  |  |_/  " << endl;
    cout << "                                 | /    \\ | |  | |  \\ |  \\  |  |  \\        | \t|      | |  \\ |  | \\  " << endl;
    cout << "                                 |/      \\| || |  \\|  \\ |__ |  \\  ___ | \t|___   | |  \\|  |  \\ " << endl;
    cout << endl;

    cout << "\n===========================================================================================\n";
    cout << "------------------------------ INVENTORY MANAGMENT SYSTEM ---------------------------------\n";
    cout << "===========================================================================================\n\n";


    ProductInventory inventory;
    Cart cart;
    int choice;

    // Load inventory from file at startup
    inventory.loadFromFile();

    // The logic to add default products if inventory is empty
    // This if statement correctly checks if the head is nullptr *after* loading from file.
    if (inventory.getHead() == nullptr) {

        // Product 1
        Product* p1 = new Product();
        p1->id = 101;
        p1->name = "Laptop";
        p1->category = "Electronics";
        p1->price = 1200;
        p1->quantity = 10;
        p1->next = nullptr;
        // Directly set head if it's null
        inventory.getHead() = p1;

        // Product 2
        Product* p2 = new Product();
        p2->id = 102;
        p2->name = "Mouse";
        p2->category = "Electronics";
        p2->price = 25.00;
        p2->quantity = 50;
        p2->next = nullptr;
        Product* temp_for_p2 = inventory.getHead();
        while (temp_for_p2->next != nullptr) temp_for_p2 = temp_for_p2->next;
        temp_for_p2->next = p2;

        // Product 3
        Product* p3 = new Product();
        p3->id = 201;
        p3->name = "Chair";
        p3->category = "Furniture";
        p3->price = 150.00;
        p3->quantity = 5;
        p3->next = nullptr;
        Product* temp_for_p3 = inventory.getHead();
        while (temp_for_p3->next != nullptr) temp_for_p3 = temp_for_p3->next;
        temp_for_p3->next = p3;

        // --- NEW PRODUCTS START HERE ---

        // Product 4
        Product* p4 = new Product();
        p4->id = 202;
        p4->name = "Desk";
        p4->category = "Furniture";
        p4->price = 300.00;
        p4->quantity = 7;
        p4->next = nullptr;
        Product* temp_for_p4 = inventory.getHead();
        while (temp_for_p4->next != nullptr) temp_for_p4 = temp_for_p4->next;
        temp_for_p4->next = p4;

        // Product 5
        Product* p5 = new Product();
        p5->id = 301;
        p5->name = "Pen";
        p5->category = "Stationery";
        p5->price = 1.50;
        p5->quantity = 100;
        p5->next = nullptr;
        Product* temp_for_p5 = inventory.getHead();
        while (temp_for_p5->next != nullptr) temp_for_p5 = temp_for_p5->next;
        temp_for_p5->next = p5;

        // Product 6
        Product* p6 = new Product();
        p6->id = 302;
        p6->name = "Notebook";
        p6->category = "Stationery";
        p6->price = 3.00;
        p6->quantity = 60;
        p6->next = nullptr;
        Product* temp_for_p6 = inventory.getHead();
        while (temp_for_p6->next != nullptr) temp_for_p6 = temp_for_p6->next;
        temp_for_p6->next = p6;

        // Product 7
        Product* p7 = new Product();
        p7->id = 401;
        p7->name = "Smartphone";
        p7->category = "Electronics";
        p7->price = 800.00;
        p7->quantity = 15;
        p7->next = nullptr;
        Product* temp_for_p7 = inventory.getHead();
        while (temp_for_p7->next != nullptr) temp_for_p7 = temp_for_p7->next;
        temp_for_p7->next = p7;

        // --- NEW PRODUCTS END HERE ---

        cout << "\n===========================================================================================\n";
        cout << "-----------------------------------DEFAULT PRODUCTS ADDED-----------------------------------\n";
        cout << "===========================================================================================\n\n";// Confirmation message
    }

    do {
        showMenu();
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1:
            inventory.addProduct();
            break;
        case 2: {
            int id;
            cout << "\n===========================\n";
            cout << "  ENTER PRODUCT ID TO DELETE: ";
            cout << "\n===========================\n";
            cin >> id;
            cin.ignore(1000, '\n');
            inventory.deleteProduct(id);
            break;
        }
        case 3: {
            int id;
            cout << "\n===========================\n";
            cout << "  ENTER PRODUCT ID TO UPDATE: ";
            cout << "\n===========================\n";
            cin >> id;
            inventory.updateProduct(id);
            break;
        }
        case 4:
            inventory.displayAll();
            break;
        case 5: { // Call the new standalone searchProduct function
            searchProduct(inventory.getHead());
            // Prompt for product ID to add to history after search
            int searchedId;
            cout << "Enter the ID of the product you just viewed (for history tracking): ";
            cin >> searchedId;
            cin.ignore(1000, '\n'); // Clear buffer after reading int
            addToHistory(searchedId);
            break;
        }
        case 6: { // Add Product to Cart - MODIFIED for multiple items
            char addMore = 'y';
            while (tolower(addMore) == 'y') {
                int id;
                cout << "\n===========================\n";
                cout << "  ENTER ID FOR ADD TO CART ";
                cout << "\n===========================\n";
                cin >> id;
                cin.ignore(1000, '\n');
                Product* temp = inventory.getHead();
                while (temp != nullptr && temp->id != id)
                    temp = temp->next;
                if (temp) {
                    cart.addToCart(temp);
                    addToHistory(temp->id); // Track recently viewed products
                }
                else {
                    cout << "Product not found in inventory.\n";
                }

                cout << "\nDo you want to add any other item to the cart? (y/n): ";
                cin >> addMore;
                // Important: Clear the buffer after reading char,
                // otherwise it might interfere with subsequent inputs.
                cin.ignore(1000, '\n');
            }
            break;
        }
        case 7: { // Remove Product from Cart
            int id;
            cout << "\n===========================\n";
            cout << "  ENTER ID FOR REMOVAL FROM CART ";
            cout << "\n===========================\n";
            cin >> id;
            cin.ignore(1000, '\n');
            // The cart.removeFromCart function already prints messages.
            // These additional messages here might be redundant but kept as per original code.
            if (!cart.removeFromCart(id)) {
                cout << "===============================================================================\n";
                cout << "------------------------- PRODUCT NOT FOUND IN CART----------------------------\n";
                cout << "===============================================================================\n";
            }
            else {
                cout << "===============================================================================\n";
                cout << "------------------------- PRODUCT REMOVED FROM CART----------------------------\n";
                cout << "===============================================================================\n";
            }
            break;
        }
        case 8: // View Cart
            cart.viewCart();
            break;
        case 9: // Checkout
            cart.checkout();
            break;
        case 10: // Inventory Statistics
            showInventoryStats(inventory);
            break;
        case 11: // Recently Viewed Products
            showHistory();
            break;
        case 0:
            inventory.saveToFile();
            clearHistory(); // Clear history when exiting to free memory
            cout << "===============================================================================\n";
            cout << "---------------------------------EXITING PROGRAM-------------------------------\n";
            cout << "===============================================================================\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
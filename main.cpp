#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 100;
int cartIDs[MAX], cartQtys[MAX];
int cartCount = 0;
float totalBill = 0, discountAmount = 0;
string adminUsername = "admin";
string adminPassword = "pass123";

// Function Declarations
void mainMenu();
void adminPanel();
void userPanel();

// Admin Functions
void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
void sortByPrice();
void totalInventoryValue();
void clearInventory();

// User Functions
void userSearch();
void userView();
void userSortPrice();
void addToCart();
void removeFromCart();
void viewBill();
void applyDiscount();
void confirmPurchase();
void viewHistory();

// Main function to run the system
int main() {
    mainMenu();
    return 0;
}

// Displays main menu and handles admin/user login
void mainMenu() {
    int choice;
    do {
        cout << "\nSMART INVENTORY SYSTEM\n";
        cout << "1. Admin Login\n2. User Panel\n3. Exit\nEnter: ";
        cin >> choice;

        if (choice == 1) {
            string user, pass;
            cout << "Username: "; cin >> user;
            cout << "Password: "; cin >> pass;
            if (user == adminUsername && pass == adminPassword) adminPanel();
            else cout << "Incorrect credentials\n";
        } else if (choice == 2) {
            userPanel();
        } else if (choice == 3) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice\n";
        }
    } while (choice != 3);
}

// Admin panel menu and function calling
void adminPanel() {
    int ch;
    do {
        cout << "\nADMIN PANEL\n";
        cout << "1.Add\n2.View\n3.Search\n4.Update\n5.Delete\n";
        cout << "6.Sort Price\n7.Total Value\n8.Clear All\n9.Back\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: sortByPrice(); break;
            case 7: totalInventoryValue(); break;
            case 8: clearInventory(); break;
            case 9: return;
            default: cout << "Invalid choice\n";
        }
    } while (ch != 9);
}

// User panel menu and function calling
void userPanel() {
    int choice;
    do {
        cout << "\nUSER PANEL\n";
        cout << "1.Search\n2.View\n3.Sort Price\n4.Add Cart\n";
        cout << "5.Remove Cart\n6.Bill\n7.Discount\n8.Confirm\n9.History\n10.Back\n> ";
        cin >> choice;

        switch (choice) {
            case 1: userSearch(); break;
            case 2: userView(); break;
            case 3: userSortPrice(); break;
            case 4: addToCart(); break;
            case 5: removeFromCart(); break;
            case 6: viewBill(); break;
            case 7: applyDiscount(); break;
            case 8: confirmPurchase(); break;
            case 9: viewHistory(); break;
            case 10: return;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 10);
}

// Adds a product to the inventory file
void addProduct() {
    ofstream file("products.txt", ios::app);
    int id, stock;
    float price;
    string name;
    cout << "ID: "; cin >> id;
    cout << "Name: "; cin >> name;
    cout << "Price: "; cin >> price;
    cout << "Stock: "; cin >> stock;
    file << id << " " << name << " " << price << " " << stock << endl;
    file.close();
    cout << "Product added\n";
}

// Displays all products
void viewProducts() {
    ifstream file("products.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open products.txt file.\n";
        return;
    }

    int id, stock;
    float price;
    string name;
    bool found = false;

    cout << "\nID\tName\tPrice\tStock\n";

    while (file >> id >> name >> price >> stock) {
        cout << id << "\t" << name << "\t" << price << "\t" << stock << endl;
        found = true;
    }

    if (!found) {
        cout << "No products available in inventory.\n";
    }

    file.close();
}



// Searches for a product by ID
void searchProduct() {
    ifstream file("products.txt");
    int id, stock, targetID;
    float price;
    string name;
    cout << "Enter ID: "; cin >> targetID;
    bool found = false;
    while (file >> id >> name >> price >> stock) {
        if (id == targetID) {
            cout << "Found: " << name << ", Price: " << price << ", Stock: " << stock << endl;
            found = true;
        }
    }
    if (!found) cout << "Product not found\n";
    file.close();
}

// Updates a product in the inventory
void updateProduct() {
    ifstream in("products.txt");
    ofstream out("temp.txt");
    int id, stock, targetID;
    float price;
    string name;
    cout << "Enter ID to update: "; cin >> targetID;
    while (in >> id >> name >> price >> stock) {
        if (id == targetID) {
            cout << "New Name: "; cin >> name;
            cout << "New Price: "; cin >> price;
            cout << "New Stock: "; cin >> stock;
        }
        out << id << " " << name << " " << price << " " << stock << endl;
    }
    in.close(); out.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");
    cout << "Product updated\n";
}

// Deletes a product from the inventory
void deleteProduct() {
    ifstream in("products.txt");
    ofstream out("temp.txt");
    int id, stock, delID;
    float price;
    string name;
    cout << "Enter ID to delete: "; cin >> delID;
    while (in >> id >> name >> price >> stock) {
        if (id != delID)
            out << id << " " << name << " " << price << " " << stock << endl;
    }
    in.close(); out.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");
    cout << "Product deleted\n";
}

// Sorts products by price
void sortByPrice() {
    int ids[MAX], stocks[MAX], count = 0;
    float prices[MAX];
    string names[MAX];
    ifstream file("products.txt");
    while (file >> ids[count] >> names[count] >> prices[count] >> stocks[count]) count++;
    file.close();
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (prices[i] > prices[j]) {
                swap(prices[i], prices[j]); swap(ids[i], ids[j]);
                swap(names[i], names[j]); swap(stocks[i], stocks[j]);
            }
    cout << "ID\tName\tPrice\tStock\n";
    for (int i = 0; i < count; i++)
        cout << ids[i] << "\t" << names[i] << "\t" << prices[i] << "\t" << stocks[i] << endl;
}

// Calculates and displays total inventory value
void totalInventoryValue() {
    ifstream file("products.txt");
    float price, total = 0;
    int stock, id;
    string name;
    while (file >> id >> name >> price >> stock)
        total += price * stock;
    file.close();
    cout << "Total Inventory Value: Rs. " << total << endl;
}

// Clears all inventory data
void clearInventory() {
    ofstream file("products.txt", ios::trunc); // ensures file is fully cleared
    if (file) {
        cout << "Inventory cleared successfully.\n";
    } else {
        cout << "Error clearing inventory!\n";
    }
    file.close();
}


// User searches for a product
void userSearch() { searchProduct(); }

// User views all products
void userView() { viewProducts(); }

// User sorts products by price
void userSortPrice() { sortByPrice(); }

// Adds product to cart
void addToCart() {
    int id, qty;
    cout << "ID: "; cin >> id;
    cout << "Quantity: "; cin >> qty;
    cartIDs[cartCount] = id;
    cartQtys[cartCount] = qty;
    cartCount++;
    cout << "Added to cart\n";
}

// Removes product from cart
void removeFromCart() {
    int id;
    cout << "ID to remove: "; cin >> id;
    for (int i = 0; i < cartCount; i++) {
        if (cartIDs[i] == id) {
            for (int j = i; j < cartCount - 1; j++) {
                cartIDs[j] = cartIDs[j + 1];
                cartQtys[j] = cartQtys[j + 1];
            }
            cartCount--;
            cout << "Removed from cart\n";
            return;
        }
    }
    cout << "Item not in cart\n";
}

// Displays the total bill
void viewBill() {
    totalBill = 0;
    ifstream file("products.txt");
    int id, stock;
    float price;
    string name;
    while (file >> id >> name >> price >> stock) {
        for (int i = 0; i < cartCount; i++) {
            if (cartIDs[i] == id) {
                float sub = price * cartQtys[i];
                totalBill += sub;
                cout << name << " x" << cartQtys[i] << " = Rs. " << sub << endl;
            }
        }
    }
    file.close();
    cout << "Subtotal: Rs. " << totalBill << endl;
    if (discountAmount > 0)
        cout << "After Discount: Rs. " << totalBill - discountAmount << endl;
}

// Applies discount code
void applyDiscount() {
    string code;
    cout << "Enter Discount Code: ";
    cin >> code;
    if (code == "SAVE10") {
        discountAmount = totalBill * 0.1;
        cout << "10% Discount Applied\n";
    } else {
        cout << "Invalid Code\n";
    }
}

// Confirms and logs the purchase
void confirmPurchase() {
    ofstream sale("sales.txt", ios::app);
    ifstream file("products.txt");
    int id, stock;
    float price;
    string name;
    while (file >> id >> name >> price >> stock) {
        for (int i = 0; i < cartCount; i++) {
            if (cartIDs[i] == id) {
                float sub = price * cartQtys[i];
                sale << name << " x" << cartQtys[i] << " = Rs. " << sub << endl;
            }
        }
    }
    sale.close(); file.close();
    cartCount = 0; totalBill = 0; discountAmount = 0;
    cout << "Purchase Confirmed\n";
}

// Displays purchase history
void viewHistory() {
    ifstream file("sales.txt");
    string line;
    cout << "Purchase History:\n";
    while (getline(file, line))
        cout << line << endl;
    file.close();
}


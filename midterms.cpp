#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>


using namespace std;


const int MAX_ITEMS = 100;


class Item {
private:
   string itemID;
   string name;
   int quantity;
   double price;
   string category;


public:
   // Constructor
   Item(string id = "", string nm = "", int qty = 0, double prc = 0.0, string cat = "")
       : itemID(id), name(nm), quantity(qty), price(prc), category(cat) {}


   // Getter and Setter methods
   string getItemID() const { return itemID; }
   string getName() const { return name; }
   int getQuantity() const { return quantity; }
   double getPrice() const { return price; }
   string getCategory() const { return category; }
  
   void setItemID(const string& id) { itemID = id; }
   void setQuantity(int qty) { quantity = qty; }
   void setPrice(double prc) { price = prc; }


   // Method to display item info
   virtual void displayItem() const {
       cout << itemID << " | " << name << " | " << quantity << " | "
            << fixed << setprecision(2) << price << " | " << category << endl;
   }
};


class Inventory {
private:
   Item* items[MAX_ITEMS];
   int itemCount;
   string categories[3];


   // Helper method to check if a category is valid
   bool isValidCategory(const string& category) {
       for (int i = 0; i < 3; i++) {
           if (categories[i] == category)
               return true;
       }
       return false;
   }


   // Helper method for validating numeric input
   template <typename T>
   bool validateInput(T& input) {
       if (cin.fail()) {
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           return false;
       }
       return true;
   }


   // Helper to find an item by ID
   int findItemByID(const string& id) {
       for (int i = 0; i < itemCount; i++) {
           if (items[i]->getItemID() == id) {
               return i;
           }
       }
       return -1;
   }


public:
   // Constructor
   Inventory() : itemCount(0) {
       categories[0] = "Clothing";
       categories[1] = "Electronics";
       categories[2] = "Entertainment";
   }


   // Add item to inventory with validation
   void addItem() {
       if (itemCount >= MAX_ITEMS) {
           cout << "Inventory is full!" << endl;
           return;
       }


       string id, name, category;
       int quantity;
       double price;


       // Ensure the user enters a valid category
       do {
           cout << "Enter category (Clothing, Electronics, Entertainment): ";
           cin >> category;
           if (!isValidCategory(category)) {
               cout << "Category '" << category << "' does not exist! Please try again." << endl;
           }
       } while (!isValidCategory(category));


       // Validate unique item ID
       while (true) {
           cout << "Enter ID: ";
           cin >> id;
           if (findItemByID(id) != -1) {
               cout << "Item ID '" << id << "' already exists! Please enter a unique ID." << endl;
           } else {
               break; // Unique ID, exit the loop
           }
       }


       cout << "Enter Name: ";
       cin >> name;


       // Validate quantity input
       while (true) {
           cout << "Enter Quantity: ";
           cin >> quantity;
           if (!validateInput(quantity) || quantity < 0) {
               cout << "Invalid input! Please enter a valid non-negative number for quantity." << endl;
           } else {
               break;
           }
       }


       // Validate price input
       while (true) {
           cout << "Enter Price: ";
           cin >> price;
           if (!validateInput(price) || price < 0.0) {
               cout << "Invalid input! Please enter a valid non-negative number for price." << endl;
           } else {
               break;
           }
       }


       // Add the item after all inputs are valid
       items[itemCount] = new Item(id, name, quantity, price, category);
       itemCount++;
       cout << "Item added successfully!" << endl;
   }


   // Update item in inventory
   void updateItem() {
       string id;
       cout << "Enter ID of the item to update: ";
       cin >> id;


       int itemIndex = findItemByID(id);
       if (itemIndex == -1) {
           cout << "Item not found!" << endl;
           return;
       }


       char choice;
       while (true) {
           cout << "Update Quantity (q), Price (p), or ID (i)? ";
           cin >> choice;


           if (choice == 'q') {
               int newQuantity;
               while (true) {
                   cout << "Enter new quantity: ";
                   cin >> newQuantity;


                   if (!validateInput(newQuantity) || newQuantity < 0) {
                       cout << "Invalid input! Please enter a valid non-negative number for quantity." << endl;
                   } else {
                       break;
                   }
               }


               int oldQuantity = items[itemIndex]->getQuantity();
               items[itemIndex]->setQuantity(newQuantity);
               cout << "Quantity of Item '" << items[itemIndex]->getName() << "' is updated from "
                    << oldQuantity << " to " << newQuantity << endl;
               break;


           } else if (choice == 'p') {
               double newPrice;
               while (true) {
                   cout << "Enter new price: ";
                   cin >> newPrice;


                   if (!validateInput(newPrice) || newPrice < 0.0) {
                       cout << "Invalid input! Please enter a valid non-negative number for price." << endl;
                   } else {
                       break;
                   }
               }


               double oldPrice = items[itemIndex]->getPrice();
               items[itemIndex]->setPrice(newPrice);
               cout << "Price of Item '" << items[itemIndex]->getName() << "' is updated from "
                    << fixed << setprecision(2) << oldPrice << " to " << fixed << setprecision(2) << newPrice << endl;
               break;


           } else if (choice == 'i') {
               string newID;
               while (true) {
                   cout << "Enter new ID: ";
                   cin >> newID;


                   // Check if the new ID is unique
                   if (findItemByID(newID) != -1 && newID != items[itemIndex]->getItemID()) {
                       cout << "Item ID '" << newID << "' already exists! Please enter a unique ID." << endl;
                   } else {
                       items[itemIndex]->setItemID(newID);
                       cout << "ID of Item is updated to '" << newID << "'." << endl;
                       break;
                   }
               }
               break;


           } else {
               cout << "Invalid choice! Please enter 'q', 'p', or 'i'." << endl;
           }
       }
   }


   // Remove item from inventory
   void removeItem() {
       string id;
       cout << "Enter ID of the item to remove: ";
       cin >> id;


       int itemIndex = findItemByID(id);
       if (itemIndex == -1) {
           cout << "Item not found!" << endl;
           return;
       }


       cout << "Item '" << items[itemIndex]->getName() << "' has been removed from the inventory." << endl;
       delete items[itemIndex];  // Free the allocated memory
       items[itemIndex] = items[itemCount - 1]; // Replace with the last item
       itemCount--;
   }


   // Display items by category
   void displayItemsByCategory() {
       string category;
       cout << "Enter category: ";
       cin >> category;


       if (!isValidCategory(category)) {
           cout << "Category '" << category << "' does not exist!" << endl;
           return;
       }


       bool found = false;
       cout << "ID | Name | Quantity | Price" << endl;
       for (int i = 0; i < itemCount; i++) {
           if (items[i]->getCategory() == category) {
               items[i]->displayItem();
               found = true;
           }
       }
       if (!found) {
           cout << "No items found in category '" << category << "'." << endl;
       }
   }


   // Display all items
   void displayAllItems() {
       cout << "ID | Name | Quantity | Price" << endl;
       for (int i = 0; i < itemCount; i++) {
           items[i]->displayItem();
       }
   }


   // Search for an item by ID
   void searchItem() {
       string id;
       cout << "Enter ID to search: ";
       cin >> id;


       int itemIndex = findItemByID(id);
       if (itemIndex == -1) {
           cout << "Item not found!" << endl;
       } else {
           cout << "Found Item: ";
           items[itemIndex]->displayItem();
       }
   }


   // Sorting functions
   static bool sortByQuantityAsc(const Item* a, const Item* b) {
       return a->getQuantity() < b->getQuantity();
   }
  
   static bool sortByQuantityDesc(const Item* a, const Item* b) {
       return a->getQuantity() > b->getQuantity();
   }


   static bool sortByPriceAsc(const Item* a, const Item* b) {
       return a->getPrice() < b->getPrice();
   }


   static bool sortByPriceDesc(const Item* a, const Item* b) {
       return a->getPrice() > b->getPrice();
   }


   void sortItems() {
       int sortOption, orderOption;


       while (true) {
           cout << "Sort by: 1 - Quantity, 2 - Price: ";
           cin >> sortOption;


           if (cin.fail() || (sortOption != 1 && sortOption != 2)) {
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cout << "Invalid option! Please enter 1 for Quantity or 2 for Price." << endl;
           } else {
               break;
           }
       }


       while (true) {
           cout << "Order: 1 - Ascending, 2 - Descending: ";
           cin >> orderOption;


           if (cin.fail() || (orderOption != 1 && orderOption != 2)) {
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cout << "Invalid option! Please enter 1 for Ascending or 2 for Descending." << endl;
           } else {
               break;
           }
       }


       // Perform sorting based on user selections
       if (sortOption == 1) { // Sort by quantity
           if (orderOption == 1) {
               sort(items, items + itemCount, sortByQuantityAsc);
           } else {
               sort(items, items + itemCount, sortByQuantityDesc);
           }
       } else if (sortOption == 2) { // Sort by price
           if (orderOption == 1) {
               sort(items, items + itemCount, sortByPriceAsc);
           } else {
               sort(items, items + itemCount, sortByPriceDesc);
           }
       }


       // Display the sorted items
       displayAllItems();
   }


   // Display low stock items (quantity <= 5)
   void displayLowStockItems() {
       cout << "ID | Name | Quantity | Price | Category" << endl;
       for (int i = 0; i < itemCount; i++) {
           if (items[i]->getQuantity() <= 5) {
               items[i]->displayItem();
           }
       }
   }


   // Menu for inventory actions
   void menu() {
       while (true) {
           int choice;


           cout << "\nInventory Menu:\n";
           cout << "1. Add Item\n";
           cout << "2. Update Item\n";
           cout << "3. Remove Item\n";
           cout << "4. Display Items by Category\n";
           cout << "5. Display All Items\n";
           cout << "6. Search Item\n";
           cout << "7. Sort Items\n";
           cout << "8. Display Low Stock Items\n";
           cout << "9. Exit\n";


           // Input validation for menu choice
           while (true) {
               cout << "Enter your choice: ";
               cin >> choice;


               if (cin.fail() || choice < 1 || choice > 9) {
                   cin.clear();
                   cin.ignore(numeric_limits<streamsize>::max(), '\n');
                   cout << "Invalid option! Please enter a number between 1 and 9." << endl;
               } else {
                   break;
               }
           }


           switch (choice) {
               case 1: addItem(); break;
               case 2: updateItem(); break;
               case 3: removeItem(); break;
               case 4: displayItemsByCategory(); break;
               case 5: displayAllItems(); break;
               case 6: searchItem(); break;
               case 7: sortItems(); break;
               case 8: displayLowStockItems(); break;
               case 9: cout << "Exiting program." << endl; return;
               default: cout << "Invalid option! Please try again." << endl;
           }
       }
   }


   // Destructor to free allocated memory
   ~Inventory() {
       for (int i = 0; i < itemCount; i++) {
           delete items[i];
       }
   }
};


int main() {
   Inventory inv;
   inv.menu();
   return 0;
}



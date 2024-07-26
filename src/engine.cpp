#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <nlohmann/json.hpp>

#include "engine.h"
#include "get_nutrition_facts.h"
#include "User.h"
#include "Product.h"

using namespace std;
using json=nlohmann::json;

void Engine(User u)
{
  int command;
  int subcommand;
  json pj, uj;

  Product *p;

  cout << "Welcome to the Interface!" << endl;

  while (1) {
    cout << "What Would You Like to do? (Enter a Number):" << endl;
    cout << "    0: Edit User Data" << endl;
    cout << "    1: Show User Data" << endl;
    cout << "    2: Add Product" << endl;
    cout << "    3: Edit Product Data" << endl;
    cout << "    4: Show Product Data" << endl;
    cout << "    5: Show All Product Data" << endl;
    cout << "    6: Add Today's Macros" << endl;
    cout << "    7: Edit Macros" << endl;
    cout << "    8: Show Todays Statistics" << endl;
    cout << "    9: Show This Weeks Statistics" << endl;
    cout << "   10: Show This Months Statistics" << endl;
    cout << "   11: Exit" << endl;
    cin >> command;

    if (cin.fail()) {
        cout << "Invalid Command: Must be an Integer Value" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        switch (command) {
            case(0):
                u.EditUserData();
                break;
            case(1):
                u.ShowUserData();
                break;
            case(2):
                pj = SearchDatabase();
                if (pj["status_verbose"] == "product not found") {
                    cout << "Product Not Found" << endl;
                } else {
                    p = new Product;

                    p->SetAllProductData(pj);

                    u.AddProductData(p);
                }
                break;
            case(3):
                break;
            case(4):
                cout << "Which Product Would You Like to See?:" << endl;
                for (size_t i = 0; i < u.GetAllProductData().size(); i++) {
                    cout << "    " << i << ": " << u.GetAllProductData()[i]->GetAllProductData()["userdefinedproductname"] << endl;
                }
                cout << "    " << u.GetAllProductData().size() << ": " << "Exit" << endl;
                while (1) {
                    cin >> subcommand;
                    if (cin.fail()) {
                        cout << "Invalid Command: Must be an Integer Value" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                        if (subcommand < 0 || subcommand > u.GetAllProductData().size()) {
                            cout << "Invalid Command: Must be a Value From 0 to " << u.GetAllProductData().size() << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else if (subcommand < u.GetAllProductData().size()){
                            u.GetAllProductData()[subcommand]->PrintProductData();
                            break;
                        } else {
                            break;
                        }
                    }
                
                }

                break;
            case(5):
                break;
            case(6):
                break;
            case(7):
                break;
            case(8):
                break;
            case(9):
                break;
            case(10):
                break;
            case(11):
                break;
            default:
                cout << "Invalid Command: Must be a Value From 0 to 11" << endl;
                break;
        }
        if (command == 11) break;
    }

  }

  u.SaveUserData();

}


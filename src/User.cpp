#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "User.h"
#include "Product.h"

using namespace std;
using json = nlohmann::json;

User::User(){}
	
User::~User(){}

void User::SetAllUserData(json all_data)
{
  userData = all_data;
}
	
json User::GetAllUserData(){
  return userData;
}

void User::SetAllProductData(json all_data)
{
  Product *p;

  for (const auto& p_json : all_data["productdata"]) {
    p = new Product;
    p->SetAllProductData(p_json);
    productData.push_back(p);
  }
}

void User::AddAllProductData(vector <Product*> vp)
{
  productData = vp;

  for (size_t i = 0; i < vp.size(); i++) {
	userData["productdata"][vp[i]->productName] = vp[i]->GetAllProductData();
  }
}
	
vector <Product*> User::GetAllProductData()
{
  return productData;
}

void User::AddProductData(Product *p)
{
  productData.push_back(p);
  userData["productdata"][p->userDefinedProductName] = p->GetAllProductData();
}

Product* User::GetProductData(string p_name)
{
  for (size_t i = 0; i < productData.size(); i++) {
	if (productData[i]->productName == p_name) {
		return productData[i];
	}
  }
  return productData[0];
}

void User::UpdateUserData()
{
  userData["username"] = userName;
  userData["userage"] = userAge;
  userData["usergender"] = userGender;
  userData["userheight"] = userHeight;
  userData["userweight"] = userWeight;
  userData["userbmi"] = userBmi;
  userData["caloriegoal"] = calorieGoal;
  userData["proteingoal"] = proteinGoal;
}

void User::UpdateUserLocal()
{
  userName = userData["username"];
  userAge = userData["userage"];
  userGender = userData["usergender"];
  userHeight = userData["userheight"];
  userWeight = userData["userweight"];
  userBmi = userData["userbmi"];
  calorieGoal = userData["caloriegoal"];
  proteinGoal = userData["proteingoal"];
}

void User::SaveUserData()
{
  string u_data_dump;
  ofstream save_stream;

  save_stream.open("../user_data/" + userName + ".json");

  if (save_stream.fail()) {
    cout << "Could not write save data" << endl;
    return;
  }

  u_data_dump = userData.dump();
  save_stream << u_data_dump; 
}

void User::LoadUserData(string filepath)
{
  ifstream load_stream;
  string str_data;
  json all_data;

  load_stream.open(filepath);

  if (load_stream.fail()) {
    cout << "Could not open save data" << endl;
    return;
  }

  getline(load_stream, str_data);

  all_data = json::parse(str_data);

  SetAllUserData(all_data);

  SetAllProductData(all_data);

  UpdateUserLocal();
}

void User::EditUserData()
{
  int command;
  int ival;
  double dval;
  string strcom, old_path, new_path;

  cout << "What Has Changed?: (Enter a Number)" << endl;
  cout << "    0: Name" << endl;
  cout << "    1: Age" << endl;
  cout << "    2: Gender" << endl;
  cout << "    3: Height" << endl;
  cout << "    4: Weight" << endl;
  cout << "    5: Calorie Goal" << endl;
  cout << "    6: Protein Goal" << endl;
  cout << "    7: Exit" << endl;

  while (1) {
    cin >> command;

    if (cin.fail()) {
        cout << "Invalid Command: Must be an Integer Value" << endl;
    } else {
        switch (command) {
            case(0):
                cout << "Enter Your New Name" << endl;
                cin >> strcom;
                old_path = "../user_data/" + userName + ".json";
                userName = strcom;
                new_path = "../user_data/" + userName + ".json";
                filesystem::rename(old_path, new_path);
                break;
            case(1):
                cout << "Enter Your New Age" << endl;
                while (1) {
                    cin >> ival;
                    if (cin.fail()) {
                        cout << "Invalid Command: Must be an Integer Value" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else break;
                }
                userAge = ival;
                break;
            case(2):
                cout << "Enter Your New Gender" << endl;
                while (1) {
                    cin >> strcom;
                    if (strcom != "m" && strcom !="f") {
                        cout << "Invalid Command: Must be either m or f" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else break;
                }
                userGender = strcom;
                break;
            case(3):
                cout << "Enter Your New Height" << endl;
                while (1) {
                    cin >> ival;
                    if (cin.fail()) {
                        cout << "Invalid Command: Must be an Integer Value" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else break;
                }
                userHeight = ival;
                break;
            case(4):
                cout << "Enter Your New Weight" << endl;
                while (1) {
                    cin >> dval;
                    if (cin.fail()) {
                        cout << "Invalid Command: Must be an Double Value" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else break;
                }
                userWeight = dval;
                break;
            case(5):
                cout << "Enter Your New Daily Calorie Goal" << endl;
                while (1) {
                    cin >> ival;
                    if (cin.fail()) {
                        cout << "Invalid Command: Must be an Integer Value" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else break;
                }
                calorieGoal = ival;
                break;
            case(6):
                cout << "Enter Your New Daily Protein Goal" << endl;
                while (1) {
                    cin >> ival;
                    if (cin.fail()) {
                        cout << "Invalid Command: Must be an Integer Value" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else break;
                }
                proteinGoal = ival;
                break;
            case(7):
                break;
            default:
                cout << "Must be a Value From 0 to 7" << endl;
                break;
        }
        if (command == 7) break;
    }
  }

  userBmi = 703 * userWeight/(double) (pow(userHeight, 2));

  UpdateUserData();

  cout << GetAllUserData().dump(1) << endl;

  return;
}

void User::ShowUserData()
{
  cout << endl;
  cout << "Name: " << userName << endl;
  cout << "Age: " << userAge << endl;
  cout << "Gender: " << userGender << endl;
  cout << "Weight: " << userWeight << endl;
  cout << "Height: " << userHeight << endl;
  cout << "BMI: " << userBmi << endl;
  cout << "Daily Calorie Goal: " << calorieGoal << endl;
  cout << "Daily Protein Goal: " << proteinGoal << endl;
  cout << endl;
}

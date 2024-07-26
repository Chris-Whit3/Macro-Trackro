#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <filesystem>
#include <algorithm>

#include <nlohmann/json.hpp>

#include "engine.h"
#include "get_nutrition_facts.h"
#include "User.h"
#include "Product.h"

using namespace std;
using json=nlohmann::json;

User LoadUser(string filepath)
{
  User u;

  u.LoadUserData(filepath);

  return u;
}

User CreateNewUser()
{
  User u;
  string u_name;
  string u_gender;
  int u_age;
  int u_height;
  double u_weight;
  int cal_goal;
  int prot_goal;

  cout << "Welcome! What Shall We Call You?" << endl;
  cin >> u_name;
  u.userName = u_name;

  cout << "What is Your Age?" << endl;
  cin >> u_age;
  u.userAge = u_age;

  cout << "Hello " << u.userName << "!" << endl;
  while(1) {
    cout << "What is Your Gender? [m/f]" << endl;
    cin >> u_gender;
    if (u_gender != "m" && u_gender != "f") {
        cout << u_gender << " is Not a Gender." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
        u.userGender = u_gender;
        break;
    }
  }

  cout << "What is Your Height in Inches?" << endl;
  cin >> u_height;
  u.userHeight = u_height;

  cout << "Awesome! How Much Do You Weigh in Lbs?" << endl;
  cin >> u_weight;
  u.userWeight = u_weight;

  u.userBmi = 703 * u.userWeight/(double) (pow(u.userHeight, 2));
  
  cout << "Based on Your Weight and Height, Your Bmi is: " << u.userBmi << endl;

  cout << "What is Your Daily Calorie Goal?" << endl;

  while (1) {
    cin >> cal_goal;

    if (cin.fail()) {
        cout << "Invalid Command: Must be an Integer Value" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        u.calorieGoal = cal_goal;
        cout << "Aiming For: " << u.calorieGoal << " calories a day" << endl;
        break;
    }
  }

  cout << "What is Your Daily Protein Goal? (in grams)[Enter -1 for default calculation]" << endl;
  
  while (1) {
    cin >> prot_goal;

    if (cin.fail()) {
        cout << "Invalid Command: Must be an Integer Value" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        if (prot_goal == -1) u.proteinGoal = u.userWeight * 0.82;
        else u.proteinGoal = prot_goal;
        cout << "Aiming For: " << u.proteinGoal << " grams of protein a day" << endl;
        break;
    }
  }

  u.UpdateUserData();

  cout << u.GetAllUserData().dump(1) << endl;

  u.SaveUserData();

  return u;
}

User FindUser()
{
  char delim;
  string input;
  string filename;
  string user_name;
  stringstream buf;
  ifstream userDataIn;

  User u;

  filesystem::path dir = "../user_data";

  if (!filesystem::exists(dir) && filesystem::is_directory(dir)) {
    cout << "No user_data directory, cannot search for user save data" << endl;
    try {
        if (filesystem::create_directory(dir)) {
            cout << "user_data directory successfully created" << endl;
        } else {
            cout << "user_data could not be created, try manual creation" << endl;
            exit(1);
        }
    } catch (const filesystem::filesystem_error & e) {
        cerr << "Filesystem error: " << e.what() << endl;
    }
  } else {
    for (const auto& entry : filesystem::directory_iterator(dir)) {
        buf << entry.path();
        delim = '/';

        getline(buf, filename, delim);
        getline(buf, filename, delim);

        delim = '.';
        buf.clear();
        buf << filename;
        getline(buf, user_name, delim);

        while(1) {
            cout << "Load User " << user_name << "? [y/n]" << endl;
            
            cin >> input;

            if (input == "y") {
                u = LoadUser(entry.path()); 
                return u;
            } else if (input == "n") {
                break;
            } else {
                cout << input << " is Not an Option" << endl;
            }

        }
    }
  }

  cout << "No User Data Available" << endl;
  cout << "Create New User? [y/n]" << endl;
  cin >> input;

  while(1) {
    if (input == "n") {
        cout << "Bye! :)" << endl;
        exit(0);
    }
    else if (input == "y") {
        u = CreateNewUser();
        return u;
    }
    else {
        cout << "Unknown Command. Exitting" << endl;
        exit(1);
    }

  }
  
  return u;
}

int main (){
  
  User u;

  u = FindUser();

  Engine(u);
}


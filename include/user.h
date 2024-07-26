#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "Product.h"


class User 
{
  public:

	User();
	~User();

	void SetAllUserData(nlohmann::json all_data);
	nlohmann::json GetAllUserData();

    void SetAllProductData(nlohmann::json all_data);
	void AddAllProductData(std::vector <Product*> vp);
	std::vector <Product*> GetAllProductData();

	void AddProductData(Product *p);
	Product* GetProductData(string p_name);

    void UpdateUserData();
    void UpdateUserLocal();

    void SaveUserData();
    void LoadUserData(string filepath);

    void EditUserData();
    void ShowUserData();

	string userName;
    int userAge;
    string userGender;
	int userHeight;
	double userWeight;
	double userBmi;

    int calorieGoal;
    int proteinGoal;

  private:

	nlohmann::json userData;
	std::vector <Product*> productData;

};


#pragma once

#include <string>
#include <nlohmann/json.hpp>

using namespace std;

class Product
{
  public:

	Product();
	~Product();

	void SetAllProductData(nlohmann::json alldata);
    nlohmann::json GetAllProductData();

    void SetProductValue(string datatype, string value, double serving_size);

    void PrintProductData();

    string userDefinedProductName;
    string productName;

	double calcium100g;
	double carbohydrates100g;
	double cholesterol100g;
	double energy100g;
	double energykcal100g;
	double fat100g;
	double fiber100g;
	double fvl100g;
	double fvn100g;
	double iron100g;
	double novagroup100g;
	double nutritionscorefr100g;
	double proteins100g;
	double salt100g;
	double saturatedfat100g;
	double sodium100g;
	double sugars100g;
	double transfat100g;
	double vitamina100g;
	double vitaminc100g;

    double servingsizeg;
	
  private:

    nlohmann::json productData;

	
};


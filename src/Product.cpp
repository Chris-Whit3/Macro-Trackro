#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Product.h"

using namespace std;
using json = nlohmann::json;


Product::Product(){}
Product::~Product(){}

void Product::SetAllProductData(json alldata)
{
  string ssgs;
  productData = alldata;

  userDefinedProductName = productData["userdefinedproductname"];
  productName = productData["productname"];

  calcium100g = productData["calcium100g"];
  carbohydrates100g = productData["carbohydrates100g"];
  cholesterol100g = productData["cholesterol100g"];
  energy100g = productData["energy100g"];
  energykcal100g = productData["energykcal100g"];
  fat100g = productData["fat100g"];
  fiber100g = productData["fiber100g"];
  fvl100g = productData["fvl100g"];
  fvn100g = productData["fvn100g"];
  iron100g = productData["iron100g"];
  novagroup100g = productData["novagroup100g"];
  nutritionscorefr100g = productData["nutritionscorefr100g"];
  proteins100g = productData["proteins100g"];
  salt100g = productData["salt100g"];
  saturatedfat100g = productData["saturatedfat100g"];
  sodium100g = productData["sodium100g"];
  sugars100g = productData["sugars100g"];
  transfat100g = productData["transfat100g"];
  vitamina100g = productData["vitamina100g"];
  vitaminc100g = productData["vitaminc100g"];

  ssgs = productData["servingsizeg"];
  servingsizeg = stoi(ssgs);
}

json Product::GetAllProductData(){
  return productData;
}

void Product::SetProductValue(string datatype, string value, double serving_size)
{
  double value100g;

  if (datatype == "name") {
    productName = value; 
  } else if (datatype == "calcium") {
    calcium100g = stod(value) * serving_size / 100;
  } else if (datatype == "carbohydrates") {
    carbohydrates100g = stod(value) * serving_size / 100;
  } else if (datatype == "cholesterol") {
    cholesterol100g = stod(value) * serving_size / 100;
  } else if (datatype == "energy") {
    energy100g = stod(value) * serving_size / 100;
  } else if (datatype == "energykcal") {
    energykcal100g = stod(value) * serving_size / 100;
  } else if (datatype == "fat") {
    fat100g = stod(value) * serving_size / 100;
  } else if (datatype == "fiber") {
    fiber100g = stod(value) * serving_size / 100;
  } else if (datatype == "fvl") {
    fvl100g = stod(value) * serving_size / 100;
  } else if (datatype == "fvn") {
    fvn100g = stod(value) * serving_size / 100;
  } else if (datatype == "iron") {
    iron100g = stod(value) * serving_size / 100;
  } else if (datatype == "novagroup") {
    novagroup100g = stod(value) * serving_size / 100;
  } else if (datatype == "nutritionscorefr") {
    nutritionscorefr100g = stod(value) * serving_size / 100;
  } else if (datatype == "proteins") {
    proteins100g = stod(value) * serving_size / 100;
  } else if (datatype == "salt") {
    salt100g = stod(value) * serving_size / 100;
  } else if (datatype == "saturatedfat") {
    saturatedfat100g = stod(value) * serving_size / 100;
  } else if (datatype == "sodium") {
    sodium100g = stod(value) * serving_size / 100;
  } else if (datatype == "sugars") {
    sugars100g = stod(value) * serving_size / 100;
  } else if (datatype == "transfat") {
    transfat100g = stod(value) * serving_size / 100;
  } else if (datatype == "vitamina") {
    vitamina100g = stod(value) * serving_size / 100;
  } else if (datatype == "vitaminc") {
    vitaminc100g = stod(value) * serving_size / 100;
  } else if (datatype == "servingsize") {
    servingsizeg = stod(value);
  }
}

void Product::PrintProductData()
{
  cout << productData.dump(4) << endl;
}

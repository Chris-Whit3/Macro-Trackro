#pragma once

#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "User.h"
#include "Product.h"

enum day {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

class Day {

  public:
  
    Day();
    ~Day();

    void AddProduct (Product p);



};

#pragma once

#include <nlohmann/json.hpp>

void sockettest();
nlohmann::json BuildItemJson(nlohmann::json stats);
size_t WriteStream(void* contents, size_t size, size_t nmemb, std::string* output);
nlohmann::json SearchDatabase();

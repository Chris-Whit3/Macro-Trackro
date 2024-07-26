#include "ZXing/ReadBarcode.h"

#include <nlohmann/json.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;
using namespace cv;
using json = nlohmann::json;

json BuildItemJson(json stats)
{
  string usrinp;
  json rj;

  if (stats["status_verbose"] == "product not found") {
    return rj = NULL;
  }

  if (stats["product"].contains("product_name_en")) {
    rj["productname"] = stats["product"]["product_name_en"];
  } else {
    rj["productname"] = "nil";
  }

  if (stats["product"]["nutriments"].contains("calcium_100g")) {
    if (stats["product"]["nutriments"]["calcium_100g"] != "null") rj["calcium100g"] = stats["product"]["nutriments"]["calcium_100g"];
    else rj["calcium100g"] = 0;
  } else {
    rj["calcium100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("carbohydrates_100g")) {
    if (stats["product"]["nutriments"]["carbohydrates_100g"] != "null") rj["carbohydrates100g"] = stats["product"]["nutriments"]["carbohydrates_100g"];
    else rj["carbohydrates100g"] = 0;
  } else {
    rj["carbohydrates100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("cholesterol_100g")) {
    if (stats["product"]["nutriments"]["cholesterol_100g"] != "null") rj["cholesterol100g"] = stats["product"]["nutriments"]["cholesterol_100g"];
    else rj["cholesterol100g"] = 0;
  } else {
    rj["cholesterol100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("energy_100g")) {
    if (stats["product"]["nutriments"]["energy_100g"] != "null") rj["energy100g"] = stats["product"]["nutriments"]["energy_100g"];
    else rj["energy100g"] = 0;
  } else {
    rj["energy100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("energy-kcal_100g")) {
    if (stats["product"]["nutriments"]["energy-kcal_100g"] != "null") rj["energykcal100g"] = stats["product"]["nutriments"]["energy-kcal_100g"];
    else rj["energykcal100g"] = 0;
  } else {
    rj["energykcal100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("fat_100g")) {
    if (stats["product"]["nutriments"]["fat_100g"] != "null") rj["fat100g"] = stats["product"]["nutriments"]["fat_100g"];
    else rj["fat100g"] = 0;
  } else {
    rj["fat100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("fiber_100g")) {
    if (stats["product"]["nutriments"]["fiber_100g"] != "null") rj["fiber100g"] = stats["product"]["nutriments"]["fiber_100g"];
    else rj["fiber100g"] = 0;
  } else {
    rj["fiber100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("fruits-vegetables-legumes-estimate-from-ingredients_100g")) {
    if (stats["product"]["nutriments"]["fruits-vegetables-legumes-estimate-from-ingredients_100g"] != "null") rj["fvl100g"] = stats["product"]["nutriments"]["fruits-vegetables-legumes-estimate-from-ingredients_100g"];
    else rj["fvl100g"] = 0;
  } else {
    rj["fvl100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("fruits-vegetables-nuts-estimate-from-ingredients_100g")) {
    if (stats["product"]["nutriments"]["fruits-vegetables-nuts-estimate-from-ingredients_100g"] != "null") rj["fvn100g"] = stats["product"]["nutriments"]["fruits-vegetables-nuts-estimate-from-ingredients_100g"];
    else rj["fvn100g"] = 0;
  } else {
    rj["fvn100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("iron_100g")) {
    if (stats["product"]["nutriments"]["iron_100g"] != "null") rj["iron100g"] = stats["product"]["nutriments"]["iron_100g"];
    else rj["iron100g"] = 0;
  } else {
    rj["iron100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("nova-group_100g")) {
    if (stats["product"]["nutriments"]["nova-group_100g"] != "null") rj["novagroup100g"] = stats["product"]["nutriments"]["nova-group_100g"];
    else rj["novagroup100g"] = 0;
  } else {
    rj["novagroup100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("nutrition-score-fr_100g")) {
    if (stats["product"]["nutriments"]["nutrition-score-fr_100g"] != "null") rj["nutritionscorefr100g"] = stats["product"]["nutriments"]["nutrition-score-fr_100g"];
    else rj["nutritionscorefr100g"] = 0;
  } else {
    rj["nutritionscorefr100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("proteins_100g")) {
    if (stats["product"]["nutriments"]["proteins_100g"] != "null") rj["proteins100g"] = stats["product"]["nutriments"]["proteins_100g"];
    else rj["proteins100g"] = 0;
  } else {
    rj["proteins100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("salt_100g")) {
    if (stats["product"]["nutriments"]["salt_100g"] != "null") rj["salt100g"] = stats["product"]["nutriments"]["salt_100g"];
    else rj["salt100g"] = 0;
  } else {
    rj["salt100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("saturated-fat_100g")) {
    if (stats["product"]["nutriments"]["saturated-fat_100g"] != "null") rj["saturatedfat100g"] = stats["product"]["nutriments"]["saturated-fat_100g"];
    else rj["saturatedfat100g"] = 0;
  } else {
    rj["saturatedfat100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("sodium_100g")) {
    if (stats["product"]["nutriments"]["sodium_100g"] != "null") rj["sodium100g"] = stats["product"]["nutriments"]["sodium_100g"];
    else rj["sodium100g"] = 0;
  } else {
    rj["sodium100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("sugars_100g")) {
    if (stats["product"]["nutriments"]["sugars_100g"] != "null") rj["sugars100g"] = stats["product"]["nutriments"]["sugars_100g"];
    else rj["sugars100g"] = 0;
  } else {
    rj["sugars100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("trans-fat_100g")) {
    if (stats["product"]["nutriments"]["trans-fat_100g"] != "null") rj["transfat100g"] = stats["product"]["nutriments"]["trans-fat_100g"];
    else rj["transfat100g"] = 0;
  } else {
    rj["transfat100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("vitamin-a_100g")) {
    if (stats["product"]["nutriments"]["vitamin-a_100g"] != "null") rj["vitamina100g"] = stats["product"]["nutriments"]["vitamin-a_100g"];
    else rj["vitamina100g"] = 0;
  } else {
    rj["vitamina100g"] = 0;
  }
  if (stats["product"]["nutriments"].contains("vitamin-c_100g")) {
    if (stats["product"]["nutriments"]["vitamin-c_100g"] != "null") rj["vitaminc100g"] = stats["product"]["nutriments"]["vitamin-c_100g"];
    else rj["vitaminc100g"] = 0;
  } else {
    rj["vitaminc100g"] = 0;
  }

  if (stats["product"].contains("serving_quantity")) {
    if (stats["product"]["serving_quantity"] != "null") rj["servingsizeg"] = stats["product"]["serving_quantity"];
    else rj["servingsizeg"] = 1;
  } else {
    rj["servingsizeg"] = 1;
  }

  cout << "Product Name: " << rj["productname"] << endl;
  cout << "Is This Okay?[y/n]" << endl;

  while (1) {
    cin >> usrinp;

    if (usrinp == "y"){
        rj["userdefinedproductname"] = rj["productname"];
        break;
    }
    else if (usrinp == "n") {
        cout << "Enter New Product Name" << endl;
        cin >> usrinp;
        rj["userdefinedproductname"] = usrinp;
        break;
    } else {
        cout << "Invalid Command: Must be 'y' or 'n'" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  /* cout << rj.dump(1) << endl; */

  return rj;
}

size_t WriteStream(void* contents, size_t size, size_t nmemb, std::string* output)
{
  size_t totalSize = size * nmemb;
  output->append(static_cast<char*>(contents), totalSize);
  return totalSize; 
}

json SearchDatabase()
{
  int width, height;
  unsigned char* data;

  string img_path;
  string readBuffer;
  string barcode_num;

  json stats, rj;

  Mat img;
  CURL* curl;
  CURLcode res;

  int serverSocket;
  int clientSocket;
  int totalbytes, bytestoread;
  char vbuf[4];
  char *buf;
  struct sockaddr_in serverAddress;

  int brk;

  if (fork() == 0) {
    execl("/bin/sh", "sh", "-c", "../camera_port/build/camera_port.exe > ../cam_logs/cam_logs.txt", (char *) NULL);
    perror("execl");
    exit(1);
  }

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8888);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
 
  bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

  listen(serverSocket, 5);

  clientSocket = accept(serverSocket, nullptr, nullptr);
  recv(clientSocket, vbuf, sizeof(vbuf), 0);

  width = stoi(vbuf);

  recv(clientSocket, vbuf, sizeof(vbuf), 0);
  height = stoi(vbuf);

  buf = (char *)malloc(sizeof(char)* width*height + 1);
 
  brk = 0;
  while (1) {
    bytestoread = width*height;
    totalbytes = 0;

    while (totalbytes != bytestoread) {
      totalbytes += recv(clientSocket, buf+totalbytes, bytestoread-totalbytes, 0);
    }

    Mat img(height, width, CV_8UC1, buf);
  
    imshow("Display windows", img);
    int k = waitKey(10);

    data = img.data;

    auto image = ZXing::ImageView(data, width, height, ZXing::ImageFormat::Lum);
    auto options = ZXing::ReaderOptions().setFormats(ZXing::BarcodeFormat::Any);
    auto barcodes = ZXing::ReadBarcodes(image, options);

    for (const auto& b : barcodes) {
        /* cout << ZXing::ToString(b.format()) << ": " << b.text() << endl; */
  	    barcode_num = b.text();
        brk = 1;
    }

    if (brk){
        send(clientSocket, "close\0", 6, 0);
        break;
    } else {
        send(clientSocket, "open\0", 5, 0);
    }
  }

  destroyAllWindows();

  close(serverSocket);

  curl = curl_easy_init();
  if (curl) {
  	string url;
  	url = "https://world.openfoodfacts.net/api/v2/product/" + barcode_num;

  	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteStream);
  	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
  	
  	res = curl_easy_perform(curl);
  	
  	curl_easy_cleanup(curl);

  	stats = json::parse(readBuffer);
  }

  rj = BuildItemJson(stats);
  
  return rj;
}

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "8888"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
int main(int argc, char** argv) {

WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    const char *imgbuf;
    string imgwidth, imgheight, strcommand;
    char command[6];
    int iResult, rResult;

    Mat frame;
    Mat grayframe;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
        WSACleanup();
        return 1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return 1;
        }

        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "Unable to connect to server!" << std::endl;
        WSACleanup();
        return 1;
    }

    VideoCapture cap(0);

    if(!cap.isOpened()) {
        cerr << "Error: Could not open camera" << endl;
        return -1;
    }

    // namedWindow("camera", cv::WINDOW_AUTOSIZE);

    cap >> frame;

    imgwidth = to_string(frame.cols);
    imgheight = to_string(frame.rows);

    iResult = send(ConnectSocket, imgwidth.c_str(), 4, 0);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }  

    iResult = send(ConnectSocket, imgheight.c_str(), 4, 0);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }  

    while(true) {

        cap >> frame;
        
        if (frame.empty())
            break;

        cvtColor(frame, grayframe, cv::COLOR_BGR2GRAY); 

        imgbuf = reinterpret_cast<const char*>(grayframe.data);
        
        iResult = send(ConnectSocket, imgbuf, grayframe.rows*grayframe.cols, 0);
        if (iResult == SOCKET_ERROR ||  iResult == WSAECONNRESET || iResult == WSAECONNABORTED) {
            std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        } 
        cout << "Bytes Sent: " << iResult << endl;

        Sleep(60);

        rResult = recv(ConnectSocket, command, 6, 0);
        strcommand = command;
        cout << "rres: " << rResult << " " << strcommand << endl;

        if (!strcmp(command, "close")) {
            cout << "closing" << endl;
            break;
        }

        if (rResult <= 0 || rResult == 6) {
            cout << "alt close" << endl;
            break;
        }

    }

cout << "Closing connection" << endl;
    closesocket(ConnectSocket);
    WSACleanup();

cout << "Releasing camera" << endl;
    cap.release();

cout << "Destroying windows" << endl;
    cv::destroyAllWindows();

    return 0;
}
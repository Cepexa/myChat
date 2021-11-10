#pragma once
#include "NetworkStream.h"
class TcpClient {
private:
    NetworkStream* nStream;
public:
    SOCKET client_socket;
    TcpClient() {
        client_socket = INVALID_SOCKET;
        nStream = new NetworkStream();
    }
    ~TcpClient() {
        if (nStream != nullptr) {
            delete nStream;
        }
    }
    int Connect(const string& ip, const string& port) {
        // служебная структура для хранение информации
        // о реализации Windows Sockets
        WSADATA wsaData;
        // старт использования библиотеки сокетов процессом
        // (подгружается Ws2_32.dll)
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw "WSAStartup failed! ";
        }
        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_socket == INVALID_SOCKET) {
            WSACleanup();
            throw "INVALID SOCKET! ";
        }
        sockaddr_in peer;
        peer.sin_family = AF_INET;
        peer.sin_port = htons(std::stoi(port.c_str()));
        peer.sin_addr.s_addr = inet_addr(ip.c_str());
        /*соединяемся по определённому порту с хостом*/
        return connect(client_socket, (sockaddr*)&peer, sizeof(peer));
    }
    NetworkStream* GetStream() {
        return nStream;
    }
    void Close() {
        if(nStream!=nullptr)
        nStream->Close(client_socket);
    }

};
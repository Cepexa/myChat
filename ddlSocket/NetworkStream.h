#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <sstream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <msclr/marshal_cppstd.h>
#pragma comment(lib, "Ws2_32.lib")
#include <list>
#include <thread>
#include <ctime>
using std::string;
using std::list;
using std::thread;
using std::exception;
using namespace msclr::interop;
class NetworkStream {
protected:
    const int max_client_buffer_size = 65536;
    char* buf;
public:
    sockaddr_in peer;
    int sizeofaddr;
    NetworkStream() {
        sizeofaddr = sizeof(peer);
        peer.sin_addr.s_addr = INADDR_ANY;
        peer.sin_port = IPPORT_RESERVED;
        peer.sin_family = AF_INET;
        
        buf = new char[max_client_buffer_size];
        
    }
    ~NetworkStream() {
        if (buf != nullptr) {
            delete buf;
        }
    }
    int Read(SOCKET& client_socket,string& msg) {
        int size = recv(client_socket, buf, max_client_buffer_size, 0);
        buf[size] = '\0';
        msg = string(buf);
        return size;
    }
    int Write(SOCKET& client_socket,string& msg) {
        return send(client_socket, msg.c_str(),msg.length(), 0);
    }
    void Close(SOCKET& client_socket) {
        closesocket(client_socket);
    }
};
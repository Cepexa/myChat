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
    NetworkStream* GetStream() {
        return nStream;
    }
    void Close() {
        nStream->Close(client_socket);
    }

};
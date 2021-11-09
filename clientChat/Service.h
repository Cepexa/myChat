#pragma once
#include "TcpClient.h"
class ServiceClient
{
public:
    string userName;
    string pswrd;
    string host;
    string port = "8888";
    TcpClient* client;
    NetworkStream* stream;
    ServiceClient(string host, string port, string userName,string pswrd):
                    host(host),port(port),userName(userName),pswrd(pswrd){
        if (userName == "")
        {
            throw "Имя не может быть пустым!";
        }
        client = new TcpClient();
    }
    void start()
    {
        if (client->Connect(host, port))
        {
            throw "Error calling connect";
        }
        //подключение клиента
        stream = client->GetStream(); // получаем поток
        stream->Write(client->client_socket, userName);
    }
    //Отправка сообщений
    void SendMessage(string message)
    {
        stream->Write(client->client_socket, message);
    }
    //Получение сообщений
    string ReceiveMessage()
    {
        string msg;
        stream->Read(client->client_socket, msg);
        return msg;
    }
    void Disconnect()
    {
        
        if (client != nullptr) {
            client->Close();//отключение клиента
        }
    }
};
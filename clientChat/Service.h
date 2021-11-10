#pragma once
#include "TcpClient.h"
#include "nlohmann/json.hpp"
#include "messageJSon.h"
using nlohmann::json;
class ServiceClient
{
public:
    string userName;
    string pswrd;
    string host;
    string port;
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
        MessageJSon msgJSon(command::login, userName, pswrd);
        json j{};
        j["command"] = msgJSon.cmd;
        j["login"] = msgJSon.login;
        j["password"] = msgJSon.password;
        stream->Write(client->client_socket, j.dump());
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
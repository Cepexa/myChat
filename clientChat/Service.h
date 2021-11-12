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
    string uuid;
    TcpClient* client;
    NetworkStream* stream;
    ServiceClient(string host, string port, string userName,string pswrd):
                    host(host),port(port),userName(userName),pswrd(pswrd){
        if (userName == "")
        {
            throw "��� �� ����� ���� ������!";
        }
        client = new TcpClient();
    }
    ~ServiceClient() {
        if (client != nullptr) {
            delete client; client = nullptr;
        }

    }
    void start()
    {
        if (client->Connect(host, port))
        {
            throw "Error calling connect";
        }
        //����������� �������
        stream = client->GetStream(); // �������� �����
        MessageJSon msgJSon(command::login, userName, pswrd);
        stream->Write(client->client_socket, msgJSon.serialize());
        //stream->Write(client->client_socket, userName);
    }
    //�������� ���������
    void SendMessage(string message)
    {
        MessageJSon msgJSon(command::message, message, uuid);
        stream->Write(client->client_socket, msgJSon.serialize());
        //stream->Write(client->client_socket, message);
    }
    //��������� ���������
    string ReceiveMessage()
    {
        MessageJSon msgJSon;
        string msg;
        if (stream->Read(client->client_socket, msg) <= 0) {
            msg = "������ ����������!";
        }
        string answer = msgJSon.deserialize(msg);
        if (msgJSon.cmd == command::login || msgJSon.cmd == command::ping || msgJSon.cmd == command::logout) {
            uuid = answer;
            answer = "ID ������: " + answer;
        }
        return answer;
    }
    void Disconnect()
    {
        MessageJSon msgJSon(command::logout, uuid);
        stream->Write(client->client_socket, msgJSon.serialize());
        if (client != nullptr) {
            client->Close();//���������� �������
        }
    }
};
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
            throw "��� �� ����� ���� ������!";
        }
        client = new TcpClient();
    }
    void start()
    {
        if (client->Connect(host, port))
        {
            throw "Error calling connect";
        }
        //����������� �������
        stream = client->GetStream(); // �������� �����
        stream->Write(client->client_socket, userName);
    }
    //�������� ���������
    void SendMessage(string message)
    {
        stream->Write(client->client_socket, message);
    }
    //��������� ���������
    string ReceiveMessage()
    {
        string msg;
        stream->Read(client->client_socket, msg);
        return msg;
    }
    void Disconnect()
    {
        
        if (client != nullptr) {
            client->Close();//���������� �������
        }
    }
};
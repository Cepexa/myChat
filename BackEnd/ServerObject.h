#pragma once
#include "ClientObject.h"

 class ServerObject
 {
 private:
     bool stopped;
     list<ClientObject*>* clients; // ��� �����������
 public:
     TcpListener* tcpListener; // ������ ��� �������������
     ~ServerObject() {
         if(tcpListener!=nullptr)
             delete tcpListener; tcpListener = nullptr;
         if (clients != nullptr)
             delete clients; clients = nullptr;
     }
     ServerObject()
     {
         clients = new list<ClientObject*>();
         stopped = false;
     }
     void RemoveConnection(string id)
     {
         // �������� �� id �������� �����������
         // � ������� ��� �� ������ �����������
         if (clients->empty())return;
         for (list<ClientObject*>::iterator it = clients->begin(); it != clients->end();it++) {
             if ((*it)->Id() == id) {
                 delete* it;
                 clients->erase(it);
                 break;
             }
         }
     }
     // ������������� �������� �����������
     void Listen(string ip, string port,string &systemMsg)
     {
         try
         {
             tcpListener = new TcpListener();
             tcpListener->Start(ip, port);
             systemMsg = "������ �������. �������� �����������...";

             while (!stopped)
             {
                 TcpClient* tcpClient = tcpListener->AcceptTcpClient();
                 if (tcpClient->client_socket == INVALID_SOCKET) continue;
                 ClientObject* clientObject = new ClientObject(tcpClient);
                 clientObject->th = new thread(&ServerObject::Process,this,clientObject,ref(systemMsg));
                 clientObject->th->detach();
                 clients->push_back(clientObject);
             }
             systemMsg = "������ ����������...";
         }
         catch (...)
         {
             systemMsg = "������ ����������...";
         }
     }
     void Process(ClientObject* clientObject,string& systemMsg)
     {
         try
         {
             clientObject->nStream = clientObject->client->GetStream();
             // �������� ��� ������������
             clientObject->userName =marshal_as<string> ("(" + clientObject->client->client_socket.ToString() + ") ") + clientObject->GetMessage();
             string message =" ����� � ���";
             string answer = "������� ���������: ";
             if (true){
                 MessageJSon msgJSon(command::login, status::ok, clientObject->Id());
                 answer = msgJSon.serialize();
             }
             else {
                 MessageJSon msgJSon(command::login, status::failed, "��������� �� ������");
                 answer = msgJSon.serialize();
             }
             //�������� ����� ������������
             if (stopped)return;
             if (clientObject->client->GetStream()->Write(clientObject->client->client_socket, answer) <= 0)
             {
                 throw "Error calling send";
             }//�������� ������
             ////���� ����������� �� ������ �������
             if (false) {
                 return;
             }
             // �������� ��������� � ����� � ��� ���� ������������ �������������
             BroadcastMessage(message, clientObject->Id());
             systemMsg = clientObject->userName + message;
             // � ����������� ����� �������� ��������� �� �������
             while (!stopped)
             {
                 try
                 {
                     message = clientObject->GetMessage();
                     if (stopped) { return; }
                     if (message == "")  throw new exception();
                     message =  message;
                     BroadcastMessage(message, clientObject->Id());
                     systemMsg = clientObject->userName + ": " + message;
                 }
                 catch (...)
                 {  
                     message = "������� ���";
                     if (stopped) {return;}
                     BroadcastMessage(message, clientObject->Id());
                     systemMsg = clientObject->userName +": " + message;
                     break;
                 }
             }
         }
         catch (const char* e) 
         {
             systemMsg = string(e);
         }
         catch (string e)
         {
             systemMsg = e;
         }
         catch (const exception& e)
         {
             systemMsg = e.what();
         }
         finally
         {
             // � ������ ������ �� ����� ��������� �������
             if (!stopped) RemoveConnection(clientObject->Id());

         }
     }

     // ���������� ��������� ������������ ��������
     void BroadcastMessage(string message, string id)
     {
         string sender_login;
         for (auto client : *clients) {
             if (client->Id() == id) {
                 sender_login = client->userName;
             }
         }
         if (stopped) { return; }
         for (auto client : *clients)
         {
             if (stopped) { return; }
             if (client->Id() != id) // ���� id ������� �� ����� id �������������
             {
             MessageJSon msgJSon(command::message, message, sender_login, client->Id());
             string sendMsg = msgJSon.serialize();
                if (stopped) { return; }

                 if (client->nStream->Write(client->client->client_socket, sendMsg) <= 0)
                 {
                    if (stopped) { return; }
                    throw "Error calling send";
                 }//�������� ������
             }
             if (stopped) { return; }
         }
     }
     // ���������� ���� ��������
     void Disconnect()
     {
         BroadcastMessage("������ ����������!", "");
         stopped = true;
         for (auto client : *clients) {
             delete client;
         }
         clients->clear();
         tcpListener->Stop(); //��������� �������
     }
 };
    
    
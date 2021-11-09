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
         delete tcpListener; 
         if (clients != nullptr)
         delete clients;
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
         for (list<ClientObject*>::iterator it = clients->begin(); it != clients->end();) {
             if ((*it)->Id() == id) {
                 (*it)->Close();
                 clients->erase(it++);
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
             string message = clientObject->userName + " ����� � ���";
             // �������� ��������� � ����� � ��� ���� ������������ �������������
             BroadcastMessage(message, clientObject->Id());
             systemMsg = message;
             // � ����������� ����� �������� ��������� �� �������
             while (!stopped)
             {
                 try
                 {
                     message = clientObject->GetMessage();
                     if (stopped) { return; }
                     if (message == "")  throw new exception();
                     message = clientObject->userName + ": " + message;
                     BroadcastMessage(message, clientObject->Id());
                     systemMsg = message;
                 }
                 catch (...)
                 {  
                     if (stopped) {return;}
                     message = clientObject->userName + ": ������� ���";
                     BroadcastMessage(message, clientObject->Id());
                     systemMsg = message;
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
         for (auto client : *clients)
         {
             if (client->Id() != id) // ���� id ������� �� ����� id �������������
             {
                 if (client->nStream->Write(client->client->client_socket, message) <= 0)
                 {
                     throw "Error calling send";
                 }//�������� ������
             }
         }
     }
     // ���������� ���� ��������
     void Disconnect()
     {
         stopped = true;
         BroadcastMessage("������ ����������!", "");
         tcpListener->Stop(); //��������� �������
         for (auto client : *clients)
         {
             client->Close(); //���������� �������
         }
         clients->clear();
     }
 };
    
    
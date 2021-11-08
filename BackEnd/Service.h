#pragma once
#include "ClientObject.h"

 class ServerObject
 {
 private:
     bool stopped;
     vector<ClientObject*> clients; // ��� �����������
 public:
     TcpListener* tcpListener; // ������ ��� �������������
     ~ServerObject() {
         if(tcpListener!=nullptr)
         delete tcpListener; 
     }
     ServerObject()
     {
         stopped = false;
     }
     void RemoveConnection(string id)
     {
         // �������� �� id �������� �����������
         // � ������� ��� �� ������ �����������
         if (clients.empty())return;
         for (vector<ClientObject*>::iterator it = clients.begin(); it != clients.end();) {
             if ((*it)->Id == id) {
                 (*it)->Close();
                 clients.erase(it++);
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
                 clients.push_back(clientObject);
                 thread clientThread (&ServerObject::Process,this,clientObject,ref(systemMsg));
                 clientThread.detach();
             }
             systemMsg = "������ ����������...";
         }
         catch (const std::exception& ex)
         {
             systemMsg = ex.what();
             Disconnect();
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
             BroadcastMessage(message, clientObject->Id);
             systemMsg = message;
             // � ����������� ����� �������� ��������� �� �������
             while (!stopped)
             {
                 try
                 {
                     message = clientObject->GetMessage();
                     if (message == "")  throw new exception();
                     message = clientObject->userName + ": " + message;
                     BroadcastMessage(message, clientObject->Id);
                     systemMsg = message;
                 }
                 catch (...)
                 {
                     message = clientObject->userName + ": ������� ���";
                     BroadcastMessage(message, clientObject->Id);
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
             RemoveConnection(clientObject->Id);
         }
     }

     // ���������� ��������� ������������ ��������
     void BroadcastMessage(string message, string id)
     {
         if (stopped)return;
         for (int i = 0; i < clients.size(); i++)
         {
             if (clients.at(i)->Id != id) // ���� id ������� �� ����� id �������������
             {
                 clients.at(i)->nStream->Write(clients.at(i)->client->client_socket,message); //�������� ������
             }
         }
     }
     // ���������� ���� ��������
     void Disconnect()
     {
         stopped = true;
         tcpListener->Stop(); //��������� �������

         for (int i = 0; i < clients.size(); i++)
         {
             clients.at(i)->Close(); //���������� �������
         }
         clients.clear();
         //Environment::Exit(0); //���������� ��������
     }
 };
    
    
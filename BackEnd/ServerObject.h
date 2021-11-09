#pragma once
#include "ClientObject.h"

 class ServerObject
 {
 private:
     bool stopped;
     vector<ClientObject*> clients; // все подключения
 public:
     TcpListener* tcpListener; // сервер для прослушивания
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
         // получаем по id закрытое подключение
         // и удаляем его из списка подключений
         if (clients.empty())return;
         for (vector<ClientObject*>::iterator it = clients.begin(); it != clients.end();) {
             if ((*it)->Id == id) {
                 (*it)->Close();
                 clients.erase(it++);
                 break;
             }
         }
     }
     // прослушивание входящих подключений
     void Listen(string ip, string port,string &systemMsg)
     {
         try
         {
             tcpListener = new TcpListener();
             tcpListener->Start(ip, port);
             systemMsg = "Сервер запущен. Ожидание подключений...";

             while (!stopped)
             {
                 TcpClient* tcpClient = tcpListener->AcceptTcpClient();
                 if (tcpClient->client_socket == INVALID_SOCKET) continue;
                 ClientObject* clientObject = new ClientObject(tcpClient);
                 clients.push_back(clientObject);
                 thread clientThread (&ServerObject::Process,this,clientObject,ref(systemMsg));
                 clientThread.detach();
             }
             systemMsg = "Сервер остановлен...";
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
             // получаем имя пользователя
             clientObject->userName =marshal_as<string> ("(" + clientObject->client->client_socket.ToString() + ") ") + clientObject->GetMessage();
             string message = clientObject->userName + " вошел в чат";
             // посылаем сообщение о входе в чат всем подключенным пользователям
             BroadcastMessage(message, clientObject->Id);
             systemMsg = message;
             // в бесконечном цикле получаем сообщения от клиента
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
                     message = clientObject->userName + ": покинул чат";
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
             // в случае выхода из цикла закрываем ресурсы
             RemoveConnection(clientObject->Id);
         }
     }

     // трансляция сообщения подключенным клиентам
     void BroadcastMessage(string message, string id)
     {
         if (stopped)return;
         for (int i = 0; i < clients.size(); i++)
         {
             if (clients.at(i)->Id != id) // если id клиента не равно id отправляющего
             {
                 clients.at(i)->nStream->Write(clients.at(i)->client->client_socket,message); //передача данных
             }
         }
     }
     // отключение всех клиентов
     void Disconnect()
     {
         stopped = true;
         tcpListener->Stop(); //остановка сервера

         for (int i = 0; i < clients.size(); i++)
         {
             clients.at(i)->Close(); //отключение клиента
         }
         clients.clear();
         //Environment::Exit(0); //завершение процесса
     }
 };
    
    
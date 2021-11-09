#pragma once
#include "ClientObject.h"

 class ServerObject
 {
 private:
     bool stopped;
     list<ClientObject*>* clients; // все подключения
 public:
     TcpListener* tcpListener; // сервер для прослушивания
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
         // получаем по id закрытое подключение
         // и удаляем его из списка подключений
         if (clients->empty())return;
         for (list<ClientObject*>::iterator it = clients->begin(); it != clients->end();) {
             if ((*it)->Id() == id) {
                 (*it)->Close();
                 clients->erase(it++);
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
                 clientObject->th = new thread(&ServerObject::Process,this,clientObject,ref(systemMsg));
                 clientObject->th->detach();
                 clients->push_back(clientObject);
             }
             systemMsg = "Сервер остановлен...";
         }
         catch (...)
         {
             systemMsg = "Сервер остановлен...";
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
             BroadcastMessage(message, clientObject->Id());
             systemMsg = message;
             // в бесконечном цикле получаем сообщения от клиента
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
                     message = clientObject->userName + ": покинул чат";
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
             // в случае выхода из цикла закрываем ресурсы
             if (!stopped) RemoveConnection(clientObject->Id());

         }
     }

     // трансляция сообщения подключенным клиентам
     void BroadcastMessage(string message, string id)
     {
         for (auto client : *clients)
         {
             if (client->Id() != id) // если id клиента не равно id отправляющего
             {
                 if (client->nStream->Write(client->client->client_socket, message) <= 0)
                 {
                     throw "Error calling send";
                 }//передача данных
             }
         }
     }
     // отключение всех клиентов
     void Disconnect()
     {
         stopped = true;
         BroadcastMessage("Сервер остановлен!", "");
         tcpListener->Stop(); //остановка сервера
         for (auto client : *clients)
         {
             client->Close(); //отключение клиента
         }
         clients->clear();
     }
 };
    
    
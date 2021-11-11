#pragma once
#include "ClientObject.h"
#include <fstream>
class Person {
public:
    string login;
    string password;
};
 class ServerObject
 {
 private:
     bool stopped;
     list<ClientObject*>* clients;// все подключения
     list<Person*>* perons;
 public:
     TcpListener* tcpListener; // сервер для прослушивания
     ~ServerObject() {
         for (auto prn : *perons) {
             delete prn;
         }
         if(tcpListener!=nullptr)
             delete tcpListener; tcpListener = nullptr;
         if (clients != nullptr)
             delete clients; clients = nullptr;
         if (perons != nullptr)
             delete perons; perons = nullptr;
     }
     ServerObject()
     {
         std::fstream fin("..\\db.JSon");
         string db; 
         if (fin.is_open())
         {
             while (!fin.eof()) {
                 string temp;
                 fin >> temp;
                 db += temp;
             }
         }
         fin.close();
         perons = new list<Person*>;
         json j = json::parse(MessageJSon::convertToUtf8(db));
         for (size_t i = 0; i < j.size(); i++)
         {
             Person* prn = new Person();
             prn->login = MessageJSon::convertFromUtf8(j[i]["login"].get<string>());
             prn->password = MessageJSon::convertFromUtf8(j[i]["password"].get<string>());
             perons->push_back(prn);
         }
            
         clients = new list<ClientObject*>();
         stopped = false;
     }
     void RemoveConnection(string id)
     {
         // получаем по id закрытое подключение
         // и удаляем его из списка подключений
         if (clients->empty())return;
         for (list<ClientObject*>::iterator it = clients->begin(); it != clients->end();it++) {
             if ((*it)->Id() == id) {
                 delete* it;
                 clients->erase(it);
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
             MessageJSon msgJSon;
             msgJSon.handlerServer(clientObject->GetMessage());
             bool statusClient = false;
             for (auto prn : *perons) {
                 if (prn->login == msgJSon.login && prn->password == msgJSon.password) {
                     statusClient = true;
                     break;
                 }
             }
             string answer;
             if (statusClient){
                 MessageJSon msgJSon(command::login, status::ok, clientObject->Id());
                 answer = msgJSon.serialize();
             }
             else {
                 MessageJSon msgJSon(command::login, status::failed, "Неверный логин или пароль!");
                 answer = msgJSon.serialize();
             }
             //Посылаем ответ пользователю
             if (stopped)return;
             if (clientObject->client->GetStream()->Write(clientObject->client->client_socket, answer) <= 0)
             {
                 throw "Error calling send";
             }//передача данных
             ////если авторизация не прошла успешно
             if (!statusClient) {
                 throw msgJSon.login+": ошибка входа";
             }
             // получаем имя пользователя
             clientObject->userName =marshal_as<string> ("(" + clientObject->client->client_socket.ToString() + ") ") + msgJSon.login;
             string message =" вошел в чат";
             // посылаем сообщение о входе в чат всем подключенным пользователям
             BroadcastMessage(message, clientObject->Id());
             systemMsg = clientObject->userName + message;
             // в бесконечном цикле получаем сообщения от клиента
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
                     message = "покинул чат";
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
             // в случае выхода из цикла закрываем ресурсы
             if (!stopped) RemoveConnection(clientObject->Id());

         }
     }

     // трансляция сообщения подключенным клиентам
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
             if (client->Id() != id) // если id клиента не равно id отправляющего
             {
             MessageJSon msgJSon(command::message, message, sender_login, client->Id());
             string sendMsg = msgJSon.serialize();
                if (stopped) { return; }

                 if (client->nStream->Write(client->client->client_socket, sendMsg) <= 0)
                 {
                    if (stopped) { return; }
                    throw "Error calling send";
                 }//передача данных
             }
             if (stopped) { return; }
         }
     }
     // отключение всех клиентов
     void Disconnect()
     {
         BroadcastMessage("Сервер остановлен!", "");
         stopped = true;
         for (auto client : *clients) {
             delete client;
         }
         clients->clear();
         tcpListener->Stop(); //остановка сервера
     }
 };
 
    
    
#pragma once
#include "TcpListener.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "nlohmann/json.hpp"
#include "messageJSon.h"
using nlohmann::json;

class ClientObject
{
    string _Id;
public:
    string Id() {return _Id;}
    string userName;
    NetworkStream* nStream;
    TcpClient* client;
    thread* th;
    ClientObject(TcpClient* tcpClient)//, ServerObject* serverObject
    {
        boost::uuids::random_generator uuid_gen;
        boost::uuids::uuid u = uuid_gen();
        _Id = boost::uuids::to_string(u);
        client = tcpClient;
    }
    ~ClientObject() {
        Close();
    }
    // закрытие подключения
    void Close()
    {
        if (nStream != nullptr)
            nStream->Close(client->client_socket);
        if (client != nullptr)
            client->Close();
        if (th != nullptr)
            th->~thread();
    }
    // чтение входящего сообщения и преобразование в строку
    string GetMessage()
    {
        string msg;
        int size = 0;
        size = nStream->Read(client->client_socket,msg);
        if (size == 0) {
             // соединение закрыто клиентом
             throw "connection closed...";
        }
        else if (size > 0) {
             /// <summary>
             /// Конвертируем строку обратно в объект и обрабатываем объект
             /// </summary>
             /// <returns></returns>
            MessageJSon msgJSon;
            return msgJSon.handlerServer(msg);
        }
        else {
             // ошибка получения данных
             Close();
             throw marshal_as<string>("recv failed: " + size);
        }
    }


};

#pragma once
#include "TcpClient.h"

class TcpListener {
private:
	addrinfo hints;
	addrinfo* addr;
	int result;
	int mySocket;
public:
    TcpListener() {
		// служебная структура для хранение информации
		// о реализации Windows Sockets
		WSADATA wsaData;
		// старт использования библиотеки сокетов процессом
		// (подгружается Ws2_32.dll)
		result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		// Если произошла ошибка подгрузки библиотеки
		if (result != 0) {
			throw "WSAStartup failed: " + result;
			return;
		}
		addr = NULL; // структура, хранящая информацию
		// об IP-адресе  слущающего сокета
		// Шаблон для инициализации структуры адреса
		ZeroMemory(&hints, sizeof(hints));

		// AF_INET определяет, что используется сеть для работы с сокетом
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM; // Задаем потоковый тип сокета
		hints.ai_protocol = IPPROTO_TCP; // Используем протокол TCP
		// Сокет биндится на адрес, чтобы принимать входящие соединения
		hints.ai_flags = AI_PASSIVE;
		// Создание сокетов
		mySocket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
		// Если создание сокета завершилось с ошибкой, выводим сообщение,
		// освобождаем память, выделенную под структуру addr,
		// выгружаем dll-библиотеку и закрываем программу
		if (mySocket == INVALID_SOCKET) {
			throw "Error at socket: " + WSAGetLastError();
			freeaddrinfo(addr);
			WSACleanup();
			return;
		}
    }
    void Start(string ip, string port) {
		// Инициализируем структуру, хранящую адрес сокета - addr.
		result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &addr);
		// Если инициализация структуры адреса завершилась с ошибкой,
		// выведем сообщением об этом и завершим выполнение программы 
		if (result != 0) {
			throw "getaddrinfo failed: " + result;
			WSACleanup(); // выгрузка библиотеки Ws2_32.dll
			return;
		}
		// Привязываем сокет к IP-адресу
		result = bind(mySocket, addr->ai_addr, (int)addr->ai_addrlen);
		// Если привязать адрес к сокету не удалось, то выводим сообщение
		// об ошибке, освобождаем память, выделенную под структуру addr.
		// и закрываем открытый сокет.
		// Выгружаем DLL-библиотеку из памяти и закрываем программу.
		if (result == SOCKET_ERROR) {
			throw "bind failed with error: " + WSAGetLastError();
			freeaddrinfo(addr);
			closesocket(mySocket);
			WSACleanup();
			return;
		}
		// Инициализируем слушающий сокет
		if (listen(mySocket, SOMAXCONN) == SOCKET_ERROR) {
			throw "listen failed with error: " + WSAGetLastError();
			closesocket(mySocket);
			WSACleanup();
			return;
		}
    }
    void Stop() {
		closesocket(mySocket);
		freeaddrinfo(addr);
		WSACleanup();
    }
    TcpClient* AcceptTcpClient() {
        TcpClient* client = new TcpClient();
		NetworkStream* nStreeam = client->GetStream();
		client->client_socket = accept(mySocket, (sockaddr*)&nStreeam->peer, &nStreeam->sizeofaddr);
        return client;
    }
};

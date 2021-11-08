#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <sstream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <msclr/marshal_cppstd.h>
#pragma comment(lib, "Ws2_32.lib")
#include <vector>
#include <thread>
#include <ctime>
using std::string;
using std::vector;
using std::thread;
using namespace msclr::interop;
class MyMessage;
class Client;

class MySocket
{
public:
	MySocket();
	void listener(string &ip, string &port);
	string sender(string &ip, string &port, string &msg);
	void handler(int& client_socket);
	void disconnect();
	addrinfo* addr;
	string ipSocket;
	u_short portSocket;
	string msg;
	vector<int> includeSession;
	addrinfo hints;

private:
	bool stopped;
	int mySocket;
	int result;
};
MySocket::MySocket()
{
	//переменная для остановки цикла прослушивания
	stopped = false;
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

}
void MySocket::listener(string &ip, string &port) {
	//addr->ai_addr = &sockAddr;
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
	// Инициализируем структуру, хранящую адрес сокета - addr.
	result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &addr);
	// Если инициализация структуры адреса завершилась с ошибкой,
	// выведем сообщением об этом и завершим выполнение программы 
	if (result != 0) {
		//throw "getaddrinfo failed: " + result;
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
		//throw "bind failed with error: " + WSAGetLastError();
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

	const int max_client_buffer_size = 65536;
	char buf[max_client_buffer_size];
	int client_socket = INVALID_SOCKET;

	while (!stopped) {
		sockaddr_in peer;
		int sizeofaddr = sizeof(peer);
		peer.sin_addr.s_addr = INADDR_ANY;
		peer.sin_port = IPPORT_RESERVED;
		peer.sin_family = AF_INET;
		// Принимаем входящие соединения
		client_socket = accept(mySocket, (sockaddr*)&peer, &sizeofaddr);
		if (client_socket == INVALID_SOCKET) {
			closesocket(mySocket);
			WSACleanup();
			return;
		}
		result = recv(client_socket, buf, max_client_buffer_size, 0);
		
		if (result == SOCKET_ERROR) {
			// ошибка получения данных
			//throw "recv failed: " + result;
			closesocket(client_socket);
			continue;
		}

		else if (result == 0) {
			// соединение закрыто клиентом
			//throw "connection closed...";
			continue;
		}
		else if (result > 0) {
			msg = string(buf);
			ipSocket = string(inet_ntoa(peer.sin_addr));
			portSocket = htons(peer.sin_port);
			// Мы знаем размер полученных данных, поэтому ставим метку конца строки
			// В буфере запроса.
			buf[result] = '\0';
			//Обработаем запрос и отправим ответ
			handler(client_socket);
			if (result == SOCKET_ERROR) {
				// произошла ошибка при отправле данных
				//throw "send failed: " + WSAGetLastError();
				continue;
			}
			// Закрываем соединение с клиентом
			closesocket(client_socket);
		}
		//delete peer;
	}
}

string MySocket::sender(string &ip, string &port, string &msg)
{
	mySocket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
	if (mySocket == INVALID_SOCKET) {
		freeaddrinfo(addr);
		WSACleanup();
		return marshal_as <string>("Error at socket : " + WSAGetLastError());
	}
	sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(std::stoi(port.c_str()));
	peer.sin_addr.s_addr = inet_addr(ip.c_str());

	/*соединяемся по определённому порту с хостом*/
	int result = connect(mySocket, (sockaddr*)&peer, sizeof(peer));
	if (result)
	{
		return "Error calling connect";
	}

	/*посылаем данные
	 *
	 * Если быть точным, данные не посланы, а записаны где-то в стеке, когда и как они будут
	 * отправлены реализации стека TCP/IP виднее. Зато мы сразу получаем управление, не
	 * дожидаясь у моря погоды.*/
	result = send(mySocket,msg.c_str(), 13, 0);
	if (result <= 0)
	{
		return "Error calling send";
	}
	/* читаем ответ сервера */
	const int max_client_buffer_size = 65536;
	char buffer[max_client_buffer_size];
	result = recv(mySocket, buffer, max_client_buffer_size, 0);
	if (result < 0) {
		return "Error calling recv";
	}
	/* закрываем соединения для посылки данных */
	/*if (shutdown(socket_listener, 1) < 0)
	{
		return "Error calling shutdown";
	}*/
	//delete peer;
	return buffer;
}
//обработчик
void MySocket::handler(int& client_socket) {
	std::stringstream response; // сюда будет записываться ответ клиенту
	std::stringstream response_body; // тело ответа
	// Данные успешно получены
	// формируем тело ответа (HTML)
	response_body << "<title>Test C++ HTTP Server</title>\n"
		<< "<h1>Test page</h1>\n"
		<< "<p>This is body of the test page...</p>\n"
		<< "<h2>Request headers</h2>\n"
		<< "<pre>" << msg.c_str() << "</pre>\n"
		<< "<em><small>Test C++ Http Server</small></em>\n";

	// Формируем весь ответ вместе с заголовками
	response << "HTTP/1.1 200 OK\r\n"
		<< "Version: HTTP/1.1\r\n"
		<< "Content-Type: text/html; charset=utf-8\r\n"
		<< "Content-Length: " << response_body.str().length()
		<< "\r\n\r\n"
		<< response_body.str();

	// Отправляем ответ клиенту с помощью функции send
	result = send(client_socket, (ipSocket + ":" +
		marshal_as<string>(portSocket.ToString())
		//+"\n" + response.str()
		).c_str(),
		response.str().length(), 0);
}
inline void MySocket::disconnect()
{
	stopped = true;
	// Убираем за собой
	closesocket(mySocket);
	freeaddrinfo(addr);
	WSACleanup();
}


	



enum class command {
	HELLO,
	login,
	message,
	message_reply,
	ping,
	ping_reply,
	logout,
	logout_reply
};
enum class status {
	ok,
	failed
};
class MyMessage
{
public:
	MyMessage(unsigned int id, command cmd, string&& ar...);
	//~MyMessage();
	unsigned int id;
	unsigned int client_id;
	string ip;
	u_short port;
	string login;
	string password;
	string auth_method;
	string session;
	string message;
	string body;
	string sender_login;

};
template <class Arg, class ... Args>
constexpr int countArgs(const Arg& x, const Args& ... args)
{
	return countArgs(args...) + 1;
}
MyMessage::MyMessage(unsigned int id, command cmd, string&& ar...)
{
	if (cmd == command::HELLO) {
		auth_method = ar.length();
	}
}



class Client
{
public:
	Client(string login, string pswrd, string ip, u_short port);
	string genSession();
	string* session;
	string ip;
	u_short port;
	unsigned int id;

private:
	static unsigned int nextId;
	string login;
	string pass;
};
unsigned int Client::nextId = 1;
Client::Client(string login, string pswrd, string ip, u_short port) :login(login), pass(pswrd), ip(ip), port(port)
{
	id = nextId++;
}
string Client::genSession() {
	time_t now = time(0);
	*session = marshal_as<string>((now.ToString()) + id.ToString());
	return *session;
};
//string Client::connect() {
//	this->addr.ai_addr = addr;
//	return genSession();
//};

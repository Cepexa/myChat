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
		// ��������� ��������� ��� �������� ����������
		// � ���������� Windows Sockets
		WSADATA wsaData;
		// ����� ������������� ���������� ������� ���������
		// (������������ Ws2_32.dll)
		result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		// ���� ��������� ������ ��������� ����������
		if (result != 0) {
			throw "WSAStartup failed: " + result;
			return;
		}
		addr = NULL; // ���������, �������� ����������
		// �� IP-������  ���������� ������
		// ������ ��� ������������� ��������� ������
		ZeroMemory(&hints, sizeof(hints));

		// AF_INET ����������, ��� ������������ ���� ��� ������ � �������
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM; // ������ ��������� ��� ������
		hints.ai_protocol = IPPROTO_TCP; // ���������� �������� TCP
		// ����� �������� �� �����, ����� ��������� �������� ����������
		hints.ai_flags = AI_PASSIVE;
		// �������� �������
		mySocket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
		// ���� �������� ������ ����������� � �������, ������� ���������,
		// ����������� ������, ���������� ��� ��������� addr,
		// ��������� dll-���������� � ��������� ���������
		if (mySocket == INVALID_SOCKET) {
			throw "Error at socket: " + WSAGetLastError();
			freeaddrinfo(addr);
			WSACleanup();
			return;
		}
    }
    void Start(string ip, string port) {
		// �������������� ���������, �������� ����� ������ - addr.
		result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &addr);
		// ���� ������������� ��������� ������ ����������� � �������,
		// ������� ���������� �� ���� � �������� ���������� ��������� 
		if (result != 0) {
			throw "getaddrinfo failed: " + result;
			WSACleanup(); // �������� ���������� Ws2_32.dll
			return;
		}
		// ����������� ����� � IP-������
		result = bind(mySocket, addr->ai_addr, (int)addr->ai_addrlen);
		// ���� ��������� ����� � ������ �� �������, �� ������� ���������
		// �� ������, ����������� ������, ���������� ��� ��������� addr.
		// � ��������� �������� �����.
		// ��������� DLL-���������� �� ������ � ��������� ���������.
		if (result == SOCKET_ERROR) {
			throw "bind failed with error: " + WSAGetLastError();
			freeaddrinfo(addr);
			closesocket(mySocket);
			WSACleanup();
			return;
		}
		// �������������� ��������� �����
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

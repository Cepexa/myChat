#pragma once
#include "pch.h"
#include <WinSock2.h>
#include <string>
using std::string;
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
struct MessageJSon
{
	MessageJSon() {
		_id++;
	}
	string idSession;
	status st;
	command cmd;
	string login;
	string password;
	string auth_method;
	string message;
	string body;
	string sender_login;
	static UINT id() { return _id; }
private:
	static UINT _id;
};
UINT MessageJSon::_id = 0;
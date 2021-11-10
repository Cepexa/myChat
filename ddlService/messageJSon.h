#pragma once
#include "pch.h"
#include <WinSock2.h>
#include <string>
#include "nlohmann/json.hpp"
using nlohmann::json;
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
	MessageJSon(command cmd):MessageJSon() {
		this->cmd = cmd;
	}
	MessageJSon(command cmd, string arg1, string arg2 = "", string arg3 = ""):MessageJSon(cmd) {
		if (cmd == command::login) {
			login = arg1;
			password = arg2;
		}
		else if (cmd == command::message) {
			if (arg3 != "") {
				body = arg1;
				sender_login = arg2;
				idSession = arg3;
			}
			else {
				body = arg1;
				idSession = arg2;
			}
		}
		else if (cmd == command::HELLO) {
			auth_method = arg1;
		}
	}
	MessageJSon(command cmd, status st, string arg="") :MessageJSon(cmd) {
		this->st = st;
		if (cmd == command::login || cmd == command::ping || cmd == command::logout) {
			idSession = arg;
		}
		else if (cmd == command::message_reply) {
			if (st == status::ok) {
				client_id = arg;
			}
			else {
				message = arg;
			}
		}
		else if (cmd == command::ping_reply) {
			if (st == status::failed) {
				message = arg;
			}
		}
	}
	command cmd;
	string idSession;
	status st;
	string login;
	string password;
	string auth_method;
	string message;
	string body;
	string client_id;
	string sender_login;
	static UINT id() { return _id; }
	string handlerClient() {
		if (cmd == command::login) {
			
		}
	}
	string handlerServer(string msg) {
			json j = json::parse(msg);
			cmd = j["command"].get<command>();

		if (cmd == command::login) {
			login = j["login"].get<string>();
			password = j["password"].get<string>();
			return login;
		}
		//заглушка
		return msg;
	}
private:
	
	static UINT _id;
};
UINT MessageJSon::_id = 0;
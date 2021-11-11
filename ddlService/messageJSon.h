#pragma once
#include "pch.h"
#include <WinSock2.h>
#include <string>
#include "nlohmann/json.hpp"
using nlohmann::json;
using std::string;
enum class command {
	null = -1,
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
	null = -1,
	ok,
	failed
};
struct MessageJSon
{	
	MessageJSon() {
		_id++;
		cmd = command::null;
		st = status::null;
	}
	MessageJSon(command cmd):MessageJSon() {
		this->cmd = cmd;
	}
	MessageJSon(command cmd, string arg1, string arg2 = "", string arg3 = ""):MessageJSon(cmd) {
		if (cmd == command::login) {
			login = convertToUtf8(arg1);
			password = convertToUtf8(arg2);
		}
		else if (cmd == command::message) {
			if (arg3 != "") {
				body = convertToUtf8(arg1);
				sender_login = convertToUtf8(arg2);
				idSession = convertToUtf8(arg3);
			}
			else {
				body = convertToUtf8(arg1);
				idSession = convertToUtf8(arg2);
			}
		}
		else if (cmd == command::HELLO) {
			auth_method = convertToUtf8(arg1);
		}
	}
	MessageJSon(command cmd, status st, string arg="") :MessageJSon(cmd) {
		this->st = st;
		if (cmd == command::login || cmd == command::ping || cmd == command::logout) {
			idSession = convertToUtf8(arg);
		}
		else if (cmd == command::message_reply) {
			if (st == status::ok) {
				client_id = convertToUtf8(arg);
			}
			else {
				message = convertToUtf8(arg);
			}
		}
		else if (cmd == command::ping_reply) {
			if (st == status::failed) {
				message = convertToUtf8(arg);
			}
		}
	}
	command cmd;
	status st;
	string idSession;
	string login;
	string password;
	string auth_method;
	string message;
	string body;
	string client_id;
	string sender_login;
	static UINT id() { return _id; }
	string serialize() {
		json j{};
		if(cmd != command::null)j["command"]	  = cmd;
		if (st != status::null) j["status"]		  = st;
		if (idSession != "")    j["session"]	  = idSession;
		if (login != "")        j["login"]        = login;
		if (password != "")     j["password"]     = password;
		if (auth_method != "")  j["auth_method"]  = auth_method;
		if (message != "")      j["message"]      = message;
		if (body != "")         j["body"]         = body;
		if (client_id != "")    j["client_id"]    = client_id;
		if (sender_login != "") j["sender_login"] = sender_login;
		string result =	convertFromUtf8(j.dump());
		return result;
	}
	string deserialize(string msg) {
		json j = json::parse(convertToUtf8(msg));
		cmd = j["command"].get<command>();
		if (cmd == command::login || cmd == command::ping || cmd == command::logout) {
				idSession = j["session"].get<string>();
			return convertFromUtf8(idSession);
		}
		else if (cmd == command::message_reply) {
			if (st == status::ok) {
					client_id = j["client_id"].get<string>();
				return convertFromUtf8(client_id);
			}
			else {
					message = j["message"].get<string>();
				return convertFromUtf8(message);
			}
		}
		else if (cmd == command::ping_reply) {
			if (st == status::failed) {
					message = j["message"].get<string>();
					return convertFromUtf8(message);
			}
		}
		else if (cmd == command::message) {
			body = j["body"].get<string>();
			idSession = j["session"].get<string>();
			try {
				sender_login = j["sender_login"].get<string>();
				return convertFromUtf8(sender_login) +": " + convertFromUtf8(body)+"\0";
			}
			catch (...) {
				return convertFromUtf8(body);
			}
		}
	}
	string handlerServer(string msg) {
		try {
		json j = json::parse(convertToUtf8(msg));
			cmd = j["command"].get<command>();

		if (cmd == command::login) {
			
			login = j["login"].get<string>();

			try {
				password = j["password"].get<string>();
			}catch(...){}
			return convertFromUtf8(login);
			
		}
		else if (cmd == command::message) {
				body = j["body"].get<string>();
				idSession = j["session"].get<string>();
				try { sender_login = j["sender_login"].get<string>(); 
				return convertFromUtf8(sender_login) + convertFromUtf8(body);
				}
				catch (...) {
				return convertFromUtf8(body);
				}
		}
		else if (cmd == command::HELLO) {
			auth_method = j["auth_method"].get<string>();
			return convertFromUtf8(auth_method);
		}
		}
		catch (...) {
			throw "������ ��������� �������";
		}
	}
private:
		static UINT _id;
	string convertToUtf8(string codepage_str) {
		int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(), codepage_str.length(), nullptr, 0);
		std::wstring utf16_str(size, '\0');
		MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(), codepage_str.length(), &utf16_str[0], size);
		int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), nullptr, 0, nullptr, nullptr);
		std::string utf8_str(utf8_size, '\0');
		WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), &utf8_str[0], utf8_size, nullptr, nullptr);
		return utf8_str;
	}
	string convertFromUtf8(string utf8_str) {
		int size = MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, utf8_str.c_str(), utf8_str.length(), nullptr, 0);
		std::wstring utf16_str(size, '\0');
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, utf8_str.c_str(), utf8_str.length(), &utf16_str[0], size);
		int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), nullptr, 0, nullptr, nullptr);
		std::string codepage_str(utf8_size, '\0');
		WideCharToMultiByte(CP_ACP, 0, utf16_str.c_str(), utf16_str.length(), &codepage_str[0], utf8_size, nullptr, nullptr);
		return codepage_str;
	}
};
UINT MessageJSon::_id = 0;
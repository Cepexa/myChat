#pragma once
#include "pch.h"
#include <WinSock2.h>
#include <string>
#include <codecvt>
#include <locale>
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
	MessageJSon(command cmd, list<string> &arg) :MessageJSon(cmd) {
		if (cmd == command::HELLO) {
			listPersStr = "";
			for (auto per : arg) {
				listPersStr += "\\-" + convertToUtf8(per);
			}
		}
	}
	command cmd;
	status st;
	string idSession;
	string login;
	string password;
	string listPersStr;
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
		if (listPersStr != "")  j["listPersStr"]     = listPersStr;
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
				idSession = convertFromUtf8(j["session"].get<string>());
			return idSession;
		}
		else if (cmd == command::message_reply) {
			if (st == status::ok) {
					client_id = convertFromUtf8(j["client_id"].get<string>());
				return client_id;
			}
			else {
					message = convertFromUtf8(j["message"].get<string>());
				return message;
			}
		}
		else if (cmd == command::ping_reply) {
			if (st == status::failed) {
					message = convertFromUtf8(j["message"].get<string>());
					return message;
			}
		}
		else if (cmd == command::message) {
			body = convertFromUtf8(j["body"].get<string>());
			idSession = convertFromUtf8(j["session"].get<string>());
			try {
				sender_login = convertFromUtf8(j["sender_login"].get<string>());
				return sender_login +": " + body;
			}
			catch (...) {
				return body;
			}
		}
		
	}
	list<string> getListPer(string msg) {
		json j = json::parse(convertToUtf8(msg));
		cmd = j["command"].get<command>();
		if (cmd == command::HELLO) {
			listPersStr = convertFromUtf8(j["auth_method"].get<string>());
			list<string> listPers;
			string temp = "";
				for (size_t i = 1; i < listPersStr.length(); i++)
				{
					if (listPersStr[i - 1] == '\\' && listPersStr[i] == '-') {
						if (temp != "") listPers.push_back(temp);
						temp = "";
						continue;
					}
					temp += listPersStr[i];
				}
			return listPers;
		}
	}
	string handlerServer(string msg) {
		try {
		json j = json::parse(convertToUtf8(msg));
			cmd = j["command"].get<command>();

		if (cmd == command::login) {
			
			login = convertFromUtf8(j["login"].get<string>());

			try {
				password = convertFromUtf8(j["password"].get<string>());
			}catch(...){}
			return login;
			
		}
		else if (cmd == command::message) {
				body = convertFromUtf8(j["body"].get<string>());
				idSession = convertFromUtf8(j["session"].get<string>());
				try { sender_login = convertFromUtf8(j["sender_login"].get<string>());
				return sender_login + body;
				}
				catch (...) {
				return body;
				}
		}
		}
		catch (...) {
			throw "ошибка обработки сервера";
		}
	}
	static string convertToUtf8(string codepage_str) {
		using wcvt = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>;
		std::u32string wstr(codepage_str.size(), U'\0');
		std::use_facet<std::ctype<char32_t>>(std::locale(".1251")).widen(codepage_str.data(), codepage_str.data() + codepage_str.size(), &wstr[0]);
		return wcvt{}.to_bytes(wstr.data(), wstr.data() + wstr.size());
		/*int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(), codepage_str.length(), nullptr, 0);
		std::wstring utf16_str(size, '\0');
		MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(), codepage_str.length(), &utf16_str[0], size);
		int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), nullptr, 0, nullptr, nullptr);
		std::string utf8_str(utf8_size, '\0');
		WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), &utf8_str[0], utf8_size, nullptr, nullptr);
		return utf8_str;*/
	}
	static string convertFromUtf8(string utf8_str) {

		using wcvt = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>;
		auto wstr = wcvt{}.from_bytes(utf8_str);
		std::string result(wstr.size(), '0');
		std::use_facet<std::ctype<char32_t>>(std::locale(".1251")).narrow(wstr.data(), wstr.data() + wstr.size(), '?', &result[0]);
		return result;
		/*std::wstring_convert<std::codecvt_utf8<wchar_t>> wconv;
		std::wstring wstr = wconv.from_bytes(utf8_str.c_str());
		// wstring to string
		std::vector<char> buf(wstr.size());
		std::use_facet<std::ctype<wchar_t>>(std::locale(".1251")).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());
		return string(buf.data(), buf.size());
		*/
		/*int size = MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, utf8_str.c_str(), utf8_str.length(), nullptr, 0);
		std::wstring utf16_str(size, '\0');
		MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, utf8_str.c_str(), utf8_str.length(), &utf16_str[0], size);
		int codepage_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), nullptr, 0, nullptr, nullptr);
		std::string codepage_str(codepage_size, '\0');
		WideCharToMultiByte(CP_ACP, 0, utf16_str.c_str(), utf16_str.length(), &codepage_str[0], codepage_size, nullptr, nullptr);
		return codepage_str;*/
	}
private:
		static UINT _id;
};
UINT MessageJSon::_id = 0;
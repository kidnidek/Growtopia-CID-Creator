#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include "json.hpp"
#include <string>
#include <windows.h>
#include <direct.h>
#include <regex>
#include "HTTPRequest.hpp"
#include "proton/rtparam.hpp"
#define GetCurrentDir _getcwd

using namespace std;
using json = nlohmann::json;

vector<GrowtopiaBot> bots;

GrowtopiaBot bot = { "", "", "", -1 };



int main() {
	SetConsoleTitleA("CidScript for PC by upy#5939");
	init();

	

	string gid, gps, vr,em, ip;
	int port;
	system("cls");
	cout << " Custom GrowID: " << endl;
	getline(cin, gid);
	cout << " Custom Password: " << endl;
	getline(cin, gps);
	cout << " Custom Game Version: " << endl;
	getline(cin, vr);
	cout << " Custom Gmail: " << endl;
	getline(cin, em);

	Growid_acc = gid;
	Password_acc = gps;
	gameVersion = vr;
	Gmail_acc = em;

	http::Request request{ "http://growtopia2.com/growtopia/server_data.php" };

	const auto response = request.send("POST", "version=1&protocol=128", { "Content-Type: application/x-www-form-urlencoded" });

	rtvar var = rtvar::parse({ response.body.begin(), response.body.end() });

	var.serialize();
	if (var.get("server") == "127.0.0.1") {
		return false;
	}
	if (var.find("server")) {
		bot.SERVER_HOST = var.get("server");
		bot.SERVER_PORT = std::stoi(var.get("port"));
	}

	cout << "Parsing port and ip is done. port is " << to_string(bot.SERVER_PORT).c_str() << " and ip is " <<bot.SERVER_HOST << endl;


	bot.userInit();
	bots.push_back(bot);

	while (true) {
		bot.eventLoop();
	}
}

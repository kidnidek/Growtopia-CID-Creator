// CPPBot.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include <string>
#include <unistd.h>
#include <stdint.h>
#include "json.hpp"
#include "proton/rtparam.hpp"
#include "HTTPRequest.hpp"

using json = nlohmann::json;
using namespace std;

vector<GrowtopiaBot> bots;

GrowtopiaBot bot = { "", "", "", -1 };

void ParseServer() {
    http::Request request{ "http://growtopia1.com/growtopia/server_data.php" };
    const auto response = request.send("POST", "version=1&protocol=128", { "Content-Type: application/x-www-form-urlencoded" });
    rtvar var = rtvar::parse({ response.body.begin(), response.body.end() });

    var.serialize();
    if (var.get("server") == "127.0.0.1") {
        return;
    }
    if (var.find("server")) {
        bot.SERVER_HOST = var.get("server");
        bot.SERVER_PORT = std::stoi(var.get("port"));
    }
    cout << "Parsed Server " << bot.SERVER_HOST << ":" << std::to_string(bot.SERVER_PORT) << "." << endl;
}

int main() {
	ParseServer();
	init();
	string gid,gps,em,ip;
	int port;
	cout << " Custom GrowID: " << endl;
	getline(cin, gid);
	cout << " Custom Password: " << endl;
	getline(cin, gps);
	cout << " Custom Gmail: " << endl;
	getline(cin, em);
	
	Growid_acc = gid;
	Password_acc = gps;
	Gmail_acc = em;
	
	bot.userInit();
	bots.push_back(bot);

	while (true) {
		bot.eventLoop();
	}
}

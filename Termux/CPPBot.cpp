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

int main() {
	//Auto parser soon.
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
	
        bot.SERVER_HOST = "213.179.209.168";
        bot.SERVER_PORT = 17246;

	bot.userInit();
	bots.push_back(bot);

	while (true) {
		bot.eventLoop();
	}
}

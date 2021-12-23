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
	cout << " Custom IP: " << endl;
	getline(cin, ip);
	cout << " Custom Port: " << endl;
	cin >> port;

	Growid_acc = gid;
	Password_acc = gps;
	gameVersion = vr;
	Gmail_acc = em;
	bot.SERVER_HOST = ip;
	bot.SERVER_PORT = port;
	
	bot.userInit();
	bots.push_back(bot);

	while (true) {
		bot.eventLoop();
	}
}

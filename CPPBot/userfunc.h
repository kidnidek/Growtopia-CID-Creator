#pragma once

//    Growtopia Bot
//    Copyright (C) 2018  Growtopia Noobs
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "json.hpp"
#include <sstream>
#include <vector>
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <regex>
#include <iterator>
#include <algorithm>

#include "utilsfunc.h"
#include "corefunc.h"
#include "enet/include/enet.h"
#include "utils.h"
//#define WORLD_GO
using namespace std;
char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string hexStr(unsigned char data)
{
	std::string s(2, ' ');
	s[0] = hexmap[(data & 0xF0) >> 4];
	s[1] = hexmap[data & 0x0F];
	return s;
}

string generateMeta()
{
	string x = to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255) + "." + to_string(rand() % 255);
	return x;
}

string generateMac()
{
	string x;
	for (int i = 0; i < 6; i++)
	{
		x += hexStr(rand());
		if (i != 5)
			x += ":";
	}
	return x;
}

string generateRid()
{
	string x;
	for (int i = 0; i < 16; i++)
	{
		x += hexStr(rand());
	}
	for (auto& c : x) c = toupper(c);
	return x;
}

string stripMessage(string msg) {
	regex e("\\x60[a-zA-Z0-9!@#$%^&*()_+\\-=\\[\\]\\{};':\"\\\\|,.<>\\/?]");
	string result = regex_replace(msg, e, "");
	result.erase(std::remove(result.begin(), result.end(), '`'), result.end());
	return result;
}
void updateVersion(std::string text) {
	utils::replace(text, "action|log\nmsg|`4UPDATE REQUIRED!`` : The `$V", "");
	utils::replace(text, "`` update is now available for your device.  Go get it!  You'll need to install it before you can play online.", "");
	gameVersion = text;
	cout << "Version has been updated to " << text << endl;
}
void GrowtopiaBot::onLoginRequested()
{
	string token;
	if (!login_user && !login_token) {
		token = "";
	}
	else {
		token = "\nuser|" + std::to_string(login_user) + "\ntoken|" + std::to_string(login_token);
	}
	string ver = gameVersion;
	string hash = std::to_string((unsigned int)rand());
	string hash2 = std::to_string((unsigned int)rand());
	SendPacket(2, "tankIDName|" + uname + "\ntankIDPass|" + upass + "\nrequestedName|SmellZero\nf|1\nprotocol|127\ngame_version|" + ver + "\nfz|5367464\nlmode|0\ncbits|0\nplayer_age|18\nGDPR|1\nhash2|" + hash2 + "\nmeta|" + generateMeta() + "\nfhash|-716928004\nrid|" + generateRid() + "\nplatformID|0\ndeviceVersion|0\ncountry|us\nhash|" + hash + "\nmac|" + generateMac() + "\nwk|" + generateRid() + "\nzf|-496303939" + token, peer);
}
void GrowtopiaBot::packet_type3(string text)
{
	if (text.find("msg|`4UPDATE REQUIRED!`` :") != std::string::npos) {
		updateVersion(text);
	}
	if (text.find("LOGON ATTEMPTS") != string::npos)
	{
		cout << "Ugh... Max number of logon attempts reached.. Seems like you reached max logon attempts (IP blocked for one hour.)" << endl;
	}
	if (text.find("action|logon_fail") != string::npos)
	{
		cout << "Ugh... Logon failed." << endl;
		connectClient();
		objects.clear();
	}
}

void GrowtopiaBot::packet_type6(string text)
{
	SendPacket(2, "action|enter_game\n", peer);
	enet_host_flush(client);
}

void GrowtopiaBot::packet_unknown(ENetPacket* packet)
{
}
void GrowtopiaBot::WhenConnected()
{
	cout << uname << " Connected to server, creating account!" << endl;
}

void GrowtopiaBot::WhenDisconnected()
{
	cout << uname << " Disconnected from server..." << endl;
	connectClient();
}

void GrowtopiaBot::userInit() {
	connectClient();
}
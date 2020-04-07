#pragma once

using namespace std;

struct TEAM {
	string name;
	string tag;
	string playerNames[5];
};

struct DATE {
	short int day;
	short int month;
	short int year;
	short int hour;
	short int min;
};

struct TOURNAMENT_INFO {
	string name;
	DATE date;
	DATE startTime;
	DATE endTime;
	DATE duration;
	short int playersOnTeam;
	TEAM teams[16];
	int teamCount;
	string prize;
	size_t id;
};
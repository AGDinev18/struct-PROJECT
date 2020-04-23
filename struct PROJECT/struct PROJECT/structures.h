#pragma once

using namespace std;

struct TEAM {
	string name;
	string tag;
	string playerNames[5];
};

struct DATE {
	int day;
	int month;
	int year;
	int hour;
	int min;
};

struct TOURNAMENT_INFO {
	string name;
	DATE date;
	DATE startTime;
	DATE endTime;
	DATE duration;
	int playersOnTeam;
	TEAM teams[16];
	int teamCount;
	string prize;
	size_t id;
};

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
};

struct HOUR {
	short int hour;
	short int min;
};

struct TOURNAMENT_INFO {
	string name;
	DATE date;
	HOUR startTime;
	HOUR endTime;
	TEAM teams[16];
	string prize;
};
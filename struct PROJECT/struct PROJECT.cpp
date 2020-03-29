#include "pch.h"
#include <iostream>
#include <windows.h>
using namespace std;

struct TEAM {
	string name;
	string playerNames[5];
};

struct DATE {
	int day;
	int month;
	int year;
};

struct HOUR {
	short int min;
	short int hour;
};

struct TOURNAMENT_INFO{
	string name;
	DATE date;
	HOUR startTime;
	HOUR endTime;
	TEAM teams[16];
	string prize;
};

class Project
{
public:

	void Greetings() {
		DisplayMenu();
	}

	void DisplayMenu() {
	}

	void MenuChoice() {
		int choice;
		cin >> choice;
		switch (choice)
		{
		default:
			break;
		}

	}
};

int main()
{
	Project project;
	system("color 0b");
	project.Greetings();
}
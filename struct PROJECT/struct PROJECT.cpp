#include "pch.h"
#include <iostream>
#include "structures.h"
#include <string>
using namespace std;

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

class Tournament {
private:

	short int tournamentCount = 0;
	short int teamCount = 0;
	short int playersCountPerTeam = 0;
	TOURNAMENT_INFO tournaments[100];

public:

	void create(TOURNAMENT_INFO tournament) {
		tournaments[tournamentCount++] = tournament;
	}

	void insert() {
		cout << "\nEnter tournament name: "; 
		cin >> tournaments[tournamentCount].name;
		cout << "Enter date: ";
		cout << "\nDay: "; 
		cin >> tournaments[tournamentCount].date.day;
		cout << "Month: "; 
		cin >> tournaments[tournamentCount].date.month;
		cout << "Year: "; 
		cin >> tournaments[tournamentCount].date.year;
		cout << "Enter start time:"; 
		cout << "\nHour: ";
		cin >> tournaments[tournamentCount].startTime.hour;
		cout << "Minutes: ";
		cin >> tournaments[tournamentCount].startTime.min;
		cout << "Enter end time:";
		cout << "\nHour: "; 
		cin >> tournaments[tournamentCount].endTime.hour;
		cout << "Minutes: "; 
		cin >> tournaments[tournamentCount].endTime.min;
		cout << "Enter team name: ";
		cin >> tournaments[tournamentCount].teams[teamCount].name;
		cout << "Enter team tag: ";
		cin >> tournaments[tournamentCount].teams[teamCount].tag;
		cout << "Enter how much players are in a team: ";
		cin >> tournaments[tournamentCount].playersOnTeam;
		cout << "Enter players' names\n";
		for (int i = 1; i <= tournaments[tournamentCount].playersOnTeam; i++)
		{
			cout << "Player " << i << ": ";
			cin >> tournaments[tournamentCount].teams[teamCount].playerNames[playersCountPerTeam++];
		}
		playersCountPerTeam = 0;
		cout << "Enter tournament's prize: ";
		cin >> tournaments[tournamentCount].prize;
	}

};

int main()
{
	//TOURNAMENT_INFO t = { "T1", { 1, 1, 1111 }, { 21, 0 }, { 23, 0 }, { { "team1", "t1", { "p1", "p2", "p3", "p4", "p5" } } }, "kupa" };

	Tournament tournament;
	//tournament.create(t);

	Project project;
	system("color 0b");
	tournament.insert();

}
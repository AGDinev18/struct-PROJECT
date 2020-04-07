// struct PROJECT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "structures.h"
#include <string>
using namespace std;


class Tournament {
private:

	short int tournamentCount = 0;
	TOURNAMENT_INFO tournaments[100];

public:

	void create(TOURNAMENT_INFO tournament) {
		tournaments[tournamentCount++] = tournament;
	}

};


class TournamentMenu
{

private:
	Tournament tournament;

public:

	TournamentMenu(Tournament t) {
		this->tournament = t;
	}

	void Greetings() {
		DisplayMenu();
	}

	void DisplayMenu() {

	}

	void CreateTournamentMenu() {

		
		TOURNAMENT_INFO ti;
		cout << "\nEnter tournament name: ";
		getline(cin, ti.name);
		cout << "Enter date: ";
		cout << "\nDay: ";
		cin >> ti.date.day;
		cout << "Month: ";
		cin >> ti.date.month;
		cout << "Year: ";
		cin >> ti.date.year;
		cout << "Enter start time:";
		cout << "\nHour: ";
		cin >> ti.startTime.hour;
		cout << "Minutes: ";
		cin >> ti.startTime.min;
		cout << "Enter end time:";
		cout << "\nHour: ";
		cin >> ti.endTime.hour;
		cout << "Minutes: ";
		cin >> ti.endTime.min;
		cout << "Enter tournament's prize: ";
		cin.ignore();
		getline(cin, ti.prize);
		cout << "Team count: ";
		cin >> ti.teamCount;
		cout << "Enter how much players are in a team: ";
		cin >> ti.playersOnTeam;

		for (int j = 0; j < ti.teamCount; j++)
		{
			cout << "Enter data for team " << j + 1 << ": \n";
			cout << "Team name: ";
			cin.ignore();
			getline(cin, ti.teams[j].name);
			cout << "Team tag: ";
			cin.ignore();
			getline(cin, ti.teams[j].tag);
			cout << "Enter players' names\n";
			for (int i = 1; i <= ti.playersOnTeam; i++)
			{
				cout << "Player " << i << ": ";
				cin.ignore();
				getline(cin, ti.teams[j].playerNames[i]);
			}

		}

		tournament.create(ti);
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
	//TOURNAMENT_INFO t = { "T1", { 1, 1, 1111 }, { 21, 0 }, { 23, 0 }, { { "team1", "t1", { "p1", "p2", "p3", "p4", "p5" } } }, "kupa" };

	Tournament tournament;

	//tournament.create(t);

	TournamentMenu menu(tournament);
	system("color 0b");
	menu.CreateTournamentMenu();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

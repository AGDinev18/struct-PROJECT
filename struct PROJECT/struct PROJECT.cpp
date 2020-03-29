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

class Tournamet {
private:
	int tournamentCount = 0;
	TOURNAMENT_INFO tournaments[100];

public:
	void create(TOURNAMENT_INFO tournament) {
		tournaments[tournamentCount++] = tournament;
	}
};

int main()
{
	int tournamentCount = 0;
	TOURNAMENT_INFO tournaments[100];

	TOURNAMENT_INFO t = { "T1", { 1, 1, 1111 }, { 21, 0 }, { 23, 0 }, { { "team1", "t1", { "p1", "p2", "p3", "p4", "p5" } } }, "kupa" };

	Tournamet tournament;
	tournament.create(t);

	Project project;
	system("color 0b");
	project.Greetings();

}
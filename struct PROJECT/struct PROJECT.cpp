#include <iostream>
#include <string>
#include <sstream>
#include "structures.h"
#include "helpers.h"

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

	void greetings() {
		displayMenu();
	}

	void displayMenu() {

	}

	bool checkIncorrectDate(DATE start, DATE end) {

		if (start.year > end.year
			|| (start.year == end.year && start.month > end.month)
			|| (start.month == end.month && start.day > end.day)
			|| (start.day == end.day && start.hour > end.hour)
			|| (start.hour == end.hour && start.min >= end.min))
			return false;

		return true;
	}
	void durationCalc(DATE start, DATE end, DATE& dur) {

		bool stop = true;

		dur.day = 0;
		dur.month = 0;
		dur.year = 0;

		if (start.min > end.min) {
			end.hour--;
			end.min += 60;
		}

		dur.min = end.min - start.min;
		dur.hour = end.hour - start.hour;

		do
		{
			if (end.day > start.day) {
				end.day--;
				dur.day++;
			}
			else
			{
				stop = false;
			}

		} while (stop);

		stop = true;

		do
		{
			if (end.month > start.month) {
				end.month--;
				dur.month++;
			}
			else
			{
				stop = false;
			}
		} while (stop);

		stop = true;

		do
		{
			if (end.year > start.year) {
				end.year--;
				dur.year++;
			}
			else
			{
				stop = false;
			}
		} while (stop);
	}

	void createTournamentMenu() {

		TOURNAMENT_INFO ti;

		bool stop;

		cout << "\nEnter tournament name: ";
		cin.ignore();
		getline(cin, ti.name);

		// DATE
		do
		{
			designInputMenu();
			cout << "Enter start date:\n";
			enterDate(ti.startTime.year, ti.startTime.month, ti.startTime.day);
			enterTime(ti.startTime.hour, ti.startTime.min);
			designInputMenu();
			cout << "Enter end date:\n";
			enterDate(ti.endTime.year, ti.endTime.month, ti.endTime.day);
			enterTime(ti.endTime.hour, ti.endTime.min);
			stop = checkIncorrectDate(ti.startTime, ti.endTime);
			if (stop != true)
			{
				cout << "Error: The starting date is after the ending date!\n";
				cout << "Please try again!:\n";
			}
			cout << endl;
		} while (stop != true);

		durationCalc(ti.startTime, ti.endTime, ti.duration);
		printf("%02dy %02dm %02dd %02dh:%02dm\n\n", ti.duration.year, ti.duration.month, ti.duration.day, ti.duration.hour, ti.duration.min);
		cout << "Enter tournament's prize: ";
		cin.ignore();
		getline(cin, ti.prize);
		designInputMenu();
		cout << "Team count: ";
		cin >> ti.teamCount;
		cout << "Enter how much players are in a team: ";
		cin >> ti.playersOnTeam;
		designInputMenu();

		for (int j = 0; j < ti.teamCount; j++)
		{
			cout << "Enter data for team " << j + 1 << ": \n";
			cout << " Team name: ";
			cin.ignore();
			getline(cin, ti.teams[j].name);

			cout << " Team tag: ";
			cin.ignore();
			getline(cin, ti.teams[j].tag);

			cout << "Enter player's names\n";

			for (int i = 1; i <= ti.playersOnTeam; i++)
			{
				cout << " Player " << i << ": ";
				cin.ignore();
				getline(cin, ti.teams[j].playerNames[i]);
			}
			designInputMenu();
		}

		tournament.create(ti);
	}

	void menuChoice() {
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
	menu.createTournamentMenu();

}
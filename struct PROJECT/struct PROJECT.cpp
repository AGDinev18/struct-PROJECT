#include "pch.h"
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

	void greetings() {
		displayMenu();
	}

	void displayMenu() {

	}

	bool isLeap(int year)
	{
		// Return true if year  
		// is a multiple pf 4 and 
		// not multiple of 100. 
		// OR year is multiple of 400. 
		return (((year % 4 == 0) &&
			(year % 100 != 0)) ||
			(year % 400 == 0));
	}

	// Returns true if given 
	// year is valid or not. 
	bool isValidDate(int d, int m, int y)
	{
		const int MAX_VALID_YR = 9999;
		const int MIN_VALID_YR = 1800;
		// If year, month and day  
		// are not in given range 
		if (y > MAX_VALID_YR ||
			y < MIN_VALID_YR)
			return false;
		if (m < 1 || m > 12)
			return false;
		if (d < 1 || d > 31)
			return false;

		// Handle February month  
		// with leap year 
		if (m == 2)
		{
			if (isLeap(y))
				return (d <= 29);
			else
				return (d <= 28);
		}

		// Months of April, June,  
		// Sept and Nov must have  
		// number of days less than 
		// or equal to 30. 
		if (m == 4 || m == 6 ||
			m == 9 || m == 11)
			return (d <= 30);

		return true;
	}

	void durationCalc(DATE start, DATE end, DATE& dur) {

		if (start.min > end.min) {
			end.hour--;
			end.min += 60;
		}

		dur.min = end.min - start.min;
		dur.hour = end.hour - start.hour;
	
	}

	DATE dateInput() {
		DATE date;
		bool dateTest = true;
		do
		{

			cout << "\nDay: ";
			cin >> date.day;
			cout << "Month: ";
			cin >> date.month;
			cout << "Year: ";
			cin >> date.year;

			dateTest = isValidDate(date.day, date.month, date.year);

			if (!dateTest)
			{
				cout << "Incorect date, please try again:\n";
			}

		} while (!dateTest);
		return date;
	}

	void createTournamentMenu() {

		TOURNAMENT_INFO ti;

		cout << "\nEnter tournament name: ";
		cin.ignore();
		getline(cin, ti.name);

		// DATE

		cout << "Enter start date:";
		ti.startTime = dateInput();
		cout << "Enter end date:";
		ti.endTime = dateInput();

		// TIME

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
		durationCalc(ti.startTime, ti.endTime, ti.duration);
		printf("%02d:%02d", ti.duration.hour, ti.duration.min);
		cout << endl;

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
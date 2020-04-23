#include <iostream>
#include <string>
#include <sstream>
#include "structures.h"
#include "helpers.h"

using namespace std;

class Tournament {
private:

public:

	TOURNAMENT_INFO tournaments[100];
	int idCount = 0;
	int tournamentCount = 0;

	void create(TOURNAMENT_INFO tournament) {
		tournament.id = idCount++;
		tournaments[tournamentCount++] = tournament;
	}

};

class TournamentMenu {
private:
	Tournament tournament;

public:

	TournamentMenu(Tournament t) {
		this->tournament = t;
	}

	void greetings() {

	}

	void displayMenu() {
		cout << "\n   ---Main Menu---\n";
		cout << "1. Show all tournaments\n";
		cout << "2. Create a tournament\n";
		cout << "3. Edit a tournament\n";
		cout << "4. Delete a tournament\n";
		cout << "9. Exit\n";
		cout << "\nYour choice: ";

		menuChoice();
	}

	void displayTournaments() {
		if (tournament.tournamentCount > 0)
		{
			cout << "\nList of all tournaments:\n";
			designInputMenu();
			for (int i = 0; i < tournament.tournamentCount; i++)
			{
				cout << "ID = " << tournament.tournaments[i].id << endl;
				cout << "\nTournament's name: " << tournament.tournaments[i].name << "\n";

				designInputMenu();
				printf("Start time: %02dd.%02dm.%02dy %02dh:%02dm\n\n",
					tournament.tournaments[i].startTime.day,
					tournament.tournaments[i].startTime.month,
					tournament.tournaments[i].startTime.year,
					tournament.tournaments[i].startTime.hour,
					tournament.tournaments[i].startTime.min);

				printf("End time: %02dd.%02dm.%02dy %02dh:%02dm\n\n",
					tournament.tournaments[i].endTime.day,
					tournament.tournaments[i].endTime.month,
					tournament.tournaments[i].endTime.year,
					tournament.tournaments[i].endTime.hour,
					tournament.tournaments[i].endTime.min);

				printDuration(i);
				designInputMenu();
				cout << "Prize: " << tournament.tournaments[i].prize << "\n\n";
				for (int j = 0; j < tournament.tournaments[i].teamCount; j++)
				{
					cout << "Team " << j + 1 << " name: " << tournament.tournaments[i].teams[j].name << endl;
					cout << "Team " << j + 1 << " tag: " << tournament.tournaments[i].teams[j].tag << endl;
					cout << "Players' names:" << endl;

					for (int z = 0; z < tournament.tournaments[i].playersOnTeam; z++)
					{
						cout << "Player " << z + 1 << " name: " << tournament.tournaments[i].teams[j].playerNames[z] << endl;
					}
					designInputMenu();
				}
			}
		}
		else
		{
			cout << "\nYou haven't created any tournaments!\n";
		}
	}

	void printDuration(int index) {

		bool testYear = false, testMonth = false, testDay = false;

		cout << "Duration: ";
		if (tournament.tournaments[index].duration.year > 0)
		{
			printf("%0002dy.", tournament.tournaments[index].duration.year);
			testYear = true;
		}
		if (tournament.tournaments[index].duration.month > 0 || testYear == true)
		{
			printf("%02dm.", tournament.tournaments[index].duration.month);
			testMonth = true;
		}
		if (tournament.tournaments[index].duration.day > 0 || testMonth == true)
		{
			printf("%02dd.", tournament.tournaments[index].duration.day);
			testDay = true;
		}
		if (tournament.tournaments[index].duration.hour > 0 || testDay == true)
		{
			printf("%02dh:", tournament.tournaments[index].duration.hour);
		}

		printf("%02dm\n", tournament.tournaments[index].duration.min);

	}

	bool checkIncorrectDate(DATE start, DATE end) {

		if (start.year > end.year
			|| (start.year == end.year && start.month > end.month)
			|| (start.month == end.month && start.day > end.day)
			|| (start.day == end.day && start.hour > end.hour)
			|| (start.hour == end.hour && start.min > end.min))
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

		if (start.hour > end.hour)
		{
			end.day--;
			end.hour += 24;
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
				cout << "\nError: The starting date is after the ending date!\n";
				cout << "Please try again!\n";
			}

			durationCalc(ti.startTime, ti.endTime, ti.duration);

			if (ti.duration.year == 0 && ti.duration.month == 0 && ti.duration.day == 0 && ti.duration.hour == 0 && ti.duration.min < 30)
			{
				cout << "\nA tournament have to last at least 30 minutes!\n";
				cout << "Please try again!\n";
				stop = false;
			}

		} while (stop != true);
		
		designInputMenu();
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

			for (int i = 0; i < ti.playersOnTeam; i++)
			{
				cout << " Player " << i + 1 << ": ";
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
		case 1:
			displayTournaments();
			break;
		case 2:
			createTournamentMenu();
			break;
		case 3:

			break;
		case 4:

			break;
		case 9:

			break;

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
	while (true)
	{
		menu.displayMenu();
	}


}
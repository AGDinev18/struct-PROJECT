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

	void displayMenu(bool& isEntered) {

		designInputMenu();
		cout << "    <---Main Menu-->\n";
		cout << "1. Create a tournament\n";

		if (isEntered)
		{
			cout << "2. Show all tournaments\n";
			cout << "3. Edit a tournament\n";
			cout << "4. Delete a tournament\n";
		}

		cout << "9. Exit\n";
		cout << "\nEnter your choice: ";

		menuChoice(isEntered);
	}

	void displayTournaments() {
		if (tournament.tournamentCount > 0)
		{

			cout << "\nList of all tournaments:\n";

			designInputMenu();
			for (int i = 0; i < tournament.tournamentCount; i++)
			{
				cout << "ID = " << tournament.tournaments[i].id << endl;

				cout << "Tournament's name: " << tournament.tournaments[i].name << endl;
				cout << "Prize: " << tournament.tournaments[i].prize << endl;
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

				for (int j = 0; j < tournament.tournaments[i].teamCount; j++)
				{
					cout << "Team " << j + 1 << ":\n";
					cout << "Name: " << tournament.tournaments[i].teams[j].name << endl;
					cout << "Tag: " << tournament.tournaments[i].teams[j].tag << endl;
					cout << "Players' names:" << endl;

					for (int z = 0; z < tournament.tournaments[i].playersOnTeam; z++)
					{
						cout << "Player " << z + 1 << " name: " << tournament.tournaments[i].teams[j].playerNames[z] << endl;
					}
					if (i != tournament.tournaments[i].teamCount - 2)
					{
						designInputMenu();
					}

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
			printf("%02dd ", tournament.tournaments[index].duration.day);
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

	void calcDuration(DATE start, DATE end, DATE& dur) {

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

	void editTournament(int editChoice, int id)
	{
		bool stop = false;
		cin.ignore();

		switch (editChoice)
		{
		case 1:
			cout << "Enter the new name: ";
			getline(cin, tournament.tournaments[id].name);
			break;
		case 2:
			cout << "Enter the new prize: ";
			getline(cin, tournament.tournaments[id].prize);
			break;
		case 3:
			cout << "Enter the new date of starting: " << endl;

			do
			{
				designInputMenu();
				cout << "Enter start date:\n";
				enterDate(tournament.tournaments[id].startTime.year,
					tournament.tournaments[id].startTime.month,
					tournament.tournaments[id].startTime.day);

				enterTime(
					tournament.tournaments[id].startTime.hour,
					tournament.tournaments[id].startTime.min
				);

				designInputMenu();

				stop = checkIncorrectDate(tournament.tournaments[id].startTime, tournament.tournaments[id].endTime);

				if (stop != true)
				{
					cout << "\nError: The starting date is after the ending date!\n";
					cout << "Please try again!\n";
				}

				calcDuration(
					tournament.tournaments[id].startTime,
					tournament.tournaments[id].endTime,
					tournament.tournaments[id].duration
				);

				if (tournament.tournaments[id].duration.year == 0
					&& tournament.tournaments[id].duration.month == 0
					&& tournament.tournaments[id].duration.day == 0
					&& tournament.tournaments[id].duration.hour == 0
					&& tournament.tournaments[id].duration.min < 30
					&& stop == true)
				{
					cout << "\nA tournament have to last at least 30 minutes!\n";
					cout << "Please try again!\n";
					stop = false;
				}

			} while (stop != true);
			break;

		case 4: cout << "Enter the new date of ending: " << endl;

			do
			{
				designInputMenu();
				cout << "Enter end date:\n";
				enterDate(
					tournament.tournaments[id].endTime.year,
					tournament.tournaments[id].endTime.month,
					tournament.tournaments[id].endTime.day
				);

				enterTime(
					tournament.tournaments[id].endTime.hour,
					tournament.tournaments[id].endTime.min
				);

				designInputMenu();

				stop = checkIncorrectDate(tournament.tournaments[id].startTime, tournament.tournaments[id].endTime);

				if (stop != true)
				{
					cout << "\nError: The starting date is after the ending date!\n";
					cout << "Please try again!\n";
				}

				calcDuration(
					tournament.tournaments[id].startTime,
					tournament.tournaments[id].endTime,
					tournament.tournaments[id].duration
				);

				if (tournament.tournaments[id].duration.year == 0
					&& tournament.tournaments[id].duration.month == 0
					&& tournament.tournaments[id].duration.day == 0
					&& tournament.tournaments[id].duration.hour == 0
					&& tournament.tournaments[id].duration.min < 30)
				{
					cout << "\nA tournament have to last at least 30 minutes!\n";
					cout << "Please try again!\n";
					stop = false;
				}

			} while (stop != true);
			break;


		}
	}

	bool checkTeamNumber(int number, int id) {
		if (tournament.tournaments[id].teamCount > number)
		{
			return true;
		}
		return false;
	}

	bool checkPlayerByNumber(int number, int id, int teamIndex) {

		if (tournament.tournaments[id].playersOnTeam >= number && number > 0)
		{
			return true;
		}
		return false;
	}

	void editTeam(int choice, int id, int teamIndex) {
		int editPlayerNameNumber;
		bool checkPlayerNumber;

		switch (choice)
		{
		case 1:
			cout << "Enter new team's name: ";
			cin.ignore();
			getline(cin, tournament.tournaments[id].teams[teamIndex].name);
			break;

		case 2:
			cout << "Enter new team's tag: ";
			cin.ignore();
			getline(cin, tournament.tournaments[id].teams[teamIndex].tag);
			break;

		case 3:
			do
			{
				cout << "Enter the player's number: ";
				cin >> editPlayerNameNumber;
				checkPlayerNumber = checkPlayerByNumber(editPlayerNameNumber, id, teamIndex);
				if (checkPlayerNumber != true)
				{
					cout << "There is no player with this number!\nPlease try again!\n";
				}
				else
				{
					cout << "Enter new player's name: ";
					cin.ignore();
					getline(cin, tournament.tournaments[id].teams[teamIndex].playerNames[editPlayerNameNumber - 1]);
				}
			} while (checkPlayerNumber != true);

		default:
			break;
		}

	}

	void editTournamentMenu() {
		int id, checkId, editChoice, editTeamChoice, teamNumber;
		bool teamNumberCheck;

		do
		{
			cout << "\nEnter the tournament's ID: ";
			cin >> id;
			checkId = getTournamentIndexById(id);

			if (checkId != -1)
			{
				designInputMenu();
				cout << "Edit options:\n";
				cout << "1. Change the tournament's name \n";
				cout << "2. Change the tournament's prize \n";
				cout << "3. Change the date of starting \n";
				cout << "4. Change the date of ending \n";
				cout << "5. Edit a team \n";
				cout << "\nEnter your choice: ";
				cin >> editChoice;
				editTournament(editChoice, id);
				if (editChoice == 5)
				{
					do
					{
						cout << "\nEnter the team's number: ";
						cin >> teamNumber;
						teamNumberCheck = checkTeamNumber(teamNumber - 1, id);
						if (teamNumberCheck != true)
						{
							cout << "There is no team with that number!\nPlease try again!\n";
						}

					} while (teamNumberCheck != true);

					designInputMenu();
					cout << "Edit options: \n";
					cout << "1. Change team's name \n";
					cout << "2. Change team's tag \n";
					cout << "3. Change player's name \n";
					cout << "\nEnter what you want to edit: ";
					cin >> editTeamChoice;
					editTeam(editTeamChoice, id, teamNumber - 1);

				}
				//editTournament(editChoice, id);
			}
			else
			{
				cout << "There is not tournament with this ID!\nPlease try again:\n";
			}
		} while (checkId == -1);

	}

	int getTournamentIndexById(int id)
	{
		for (int i = 0; i < tournament.tournamentCount; i++)
		{
			if (tournament.tournaments[i].id == id)
			{
				return i;
			}
		}

		return -1;
	}

	void deleteTournamentMenu()
	{
		int Id, checkId;

		do
		{
			cout << "\n\nEnter the tournament's ID: ";
			cin >> Id;

			checkId = getTournamentIndexById(Id);

			if (checkId != -1)
			{
				deleteTournament(Id, checkId);
			}
			else
			{
				cout << "There is not tournament with this ID!\nPlease try again:\n";
			}
		} while (checkId == -1);
	}

	void deleteTournament(int deleteID, int index)
	{
		for (int i = index; i < tournament.tournamentCount - 1; i++)
		{
			tournament.tournaments[i] = tournament.tournaments[i + 1];
		}
		tournament.tournamentCount--;
	}

	void createTournamentMenu() {

		TOURNAMENT_INFO ti;

		bool stop, checkPlayersCount = true, checkTeamCount = true;

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

			calcDuration(ti.startTime, ti.endTime, ti.duration);

			if (ti.duration.year == 0
				&& ti.duration.month == 0
				&& ti.duration.day == 0
				&& ti.duration.hour == 0
				&& ti.duration.min < 30)
			{
				cout << "\nA tournament have to last at least 30 minutes!\n";
				cout << "Please try again!\n";
				stop = false;
			}

		} while (stop != true);

		designInputMenu();

		cout << "Enter tournament's prize: ";
		//cin.ignore();
		getline(cin, ti.prize);
		designInputMenu();

		do
		{
			cout << "Team count: ";
			cin >> ti.teamCount;
			if (ti.teamCount > 16)
			{
				cout << "There can't be more than 16 teams in a tournament!\nPlease try again:\n";
				checkTeamCount = false;
			}
		} while (checkTeamCount != true);

		do
		{
			cout << "Enter how much players are in a team: ";
			cin >> ti.playersOnTeam;
			if (ti.playersOnTeam > 5)
			{
				cout << "There must be less than or equal to 5 players in a team!\nPlease try again:\n";
				checkPlayersCount = false;
			}



		} while (checkPlayersCount != true);
		designInputMenu();

		cin.ignore(INT_MAX, '\n');
		for (int j = 0; j < ti.teamCount; j++)
		{
			cout << "Enter data for team " << j + 1 << ": " << endl;
			cout << " Team name: ";

			getline(cin, ti.teams[j].name);

			cout << " Team tag: ";
			getline(cin, ti.teams[j].tag);

			cout << "Enter player's names: " << endl;

			for (int i = 0; i < ti.playersOnTeam; i++)
			{
				cout << " Player " << i + 1 << ": ";
				getline(cin, ti.teams[j].playerNames[i]);
			}

			if (j < ti.teamCount - 1) {
				designInputMenu();
			}

		}
		tournament.create(ti);
	}

	void menuChoice(bool& isEntered) {
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			createTournamentMenu();
			isEntered = true;
			break;
		case 2:
			displayTournaments();
			break;
		case 3:
			editTournamentMenu();
			break;
		case 4:
			deleteTournamentMenu();
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
	bool isEntered = false;
	system("color 0b");

	while (true)
	{
		menu.displayMenu(isEntered);
	}
}
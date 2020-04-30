#include <iostream>
#include <string>
#include <sstream>
#include "structures.h"
#include "helpers.h"

using namespace std;

class Data {
private:

public:

	TOURNAMENT_INFO tournaments[100];
	int idCount = 0;
	int tournamentCount = 0;

	// A function that returns nothing and collect the given tournament data
	void createTournament(TOURNAMENT_INFO tournament) {
		tournament.id = idCount++;
		tournaments[tournamentCount++] = tournament;
	}

	// A function that delete a tournament by given id
	void deleteTournament(int index)
	{
		for (int i = index; i < tournamentCount - 1; i++)
		{
			tournaments[i] = tournaments[i + 1];
		}
		tournamentCount--;
	}

	// A function that checks if there is a tournament with the given id
	int getTournamentIndexById(int id)
	{
		for (int i = 0; i < tournamentCount; i++)
		{
			if (tournaments[i].id == id)
			{
				return i;
			}
		}

		return -1;
	}

	// A function that calculate the tournament's duration by given start and end time
	void calcDuration(DATE start, DATE end, DATE& dur) {

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

		calcSpecTime(start.day, end.day, dur.day);
		calcSpecTime(start.month, end.month, dur.month);
		calcSpecTime(start.year, end.year, dur.year);

	}

	// A function that checks if there can be team with the given number
	bool checkTeamNumber(int number, int id) {
		if (tournaments[id].teamCount > number && number > 0)
		{
			return true;
		}
		return false;
	}

	// A function that checks if the player's count is more than the max
	bool checkPlayerByNumber(int number, int id) {

		if (tournaments[id].playersOnTeam >= number && number > 0)
		{
			return true;
		}
		return false;
	}
};

class Presentation {
private:
	Data data;

public:

	// The constructor for the presentation class
	Presentation(Data t) {
		this->data = t;
	}

	void greetings() {
		cout << "\tHello User!\nWelcome to our application!\n\n";
	}

	// A function that displays the user's options
	bool displayMenu(bool& isEntered) {
		printSeperator();
		cout << "   <---Main Menu--->\n";
		cout << "1. Create a tournament\n";

		if (isEntered)
		{
			cout << "2. Show all tournaments\n";
			cout << "3. Edit a tournament\n";
			cout << "4. Delete a tournament\n";
		}

		cout << "9. Exit\n";
		cout << "\nEnter your choice: ";

		return menuChoice(isEntered);
	}

	// A function that displays the created tournaments
	void displayTournaments() {
		if (data.tournamentCount > 0)
		{

			cout << "\nList of all tournaments:\n";

			for (int i = 0; i < data.tournamentCount; i++)
			{
				printSeperator();
				cout << "ID = " << data.tournaments[i].id << endl;

				cout << "Tournament's name: " << data.tournaments[i].name << endl;
				cout << "Prize: " << data.tournaments[i].prize << endl;
				printSeperator();

				printf("Start time: %02dd.%02dm.%02dy %02dh:%02dm\n\n",
					data.tournaments[i].startTime.day,
					data.tournaments[i].startTime.month,
					data.tournaments[i].startTime.year,
					data.tournaments[i].startTime.hour,
					data.tournaments[i].startTime.min);

				printf("End time: %02dd.%02dm.%02dy %02dh:%02dm\n\n",
					data.tournaments[i].endTime.day,
					data.tournaments[i].endTime.month,
					data.tournaments[i].endTime.year,
					data.tournaments[i].endTime.hour,
					data.tournaments[i].endTime.min);

				printDuration(i);
				printSeperator();

				for (int j = 0; j < data.tournaments[i].teamCount; j++)
				{
					cout << "Team " << j + 1 << ":\n";
					cout << "Name: " << data.tournaments[i].teams[j].name << endl;
					cout << "Tag: " << data.tournaments[i].teams[j].tag << endl;
					cout << "Players' names:" << endl;

					for (int z = 0; z < data.tournaments[i].playersOnTeam; z++)
					{
						cout << "Player " << z + 1 << " name: " << data.tournaments[i].teams[j].playerNames[z] << endl;
					}
					printSeperator();
				}
				cout << "\n\n";
			}
		}
		else
		{
			cout << "\nYou haven't created any tournaments!\n";
		}
	}

	// A function that print the duration of the tournament
	void printDuration(int id) {

		bool testYear = false, testMonth = false, testDay = false;

		cout << "Duration: ";
		if (data.tournaments[id].duration.year > 0)
		{
			printf("%0002dy.", data.tournaments[id].duration.year);
			testYear = true;
		}
		if (data.tournaments[id].duration.month > 0 || testYear == true)
		{
			printf("%02dm.", data.tournaments[id].duration.month);
			testMonth = true;
		}
		if (data.tournaments[id].duration.day > 0 || testMonth == true)
		{
			printf("%02dd ", data.tournaments[id].duration.day);
			testDay = true;
		}
		if (data.tournaments[id].duration.hour > 0 || testDay == true)
		{
			printf("%02dh:", data.tournaments[id].duration.hour);
		}

		printf("%02dm\n", data.tournaments[id].duration.min);

	}

	// A function that edit the tournament's information
	void editTournament(int editChoice, int index)
	{
		TOURNAMENT_INFO ti;

		bool stop = false;
		cin.ignore();

		switch (editChoice)
		{
			case 1:
				cout << "Enter the new name: ";
				getline(cin, data.tournaments[index].name);
				break;
			case 2:
				cout << "Enter the new prize: ";
				getline(cin, data.tournaments[index].prize);
				break;
			case 3:
				cout << "Enter the new date of starting: " << endl;

				do
				{
					printSeperator();
					cout << "Enter start date:\n";
					enterDate(data.tournaments[index].startTime.year,
						data.tournaments[index].startTime.month,
						data.tournaments[index].startTime.day);

					enterTime(
						data.tournaments[index].startTime.hour,
						data.tournaments[index].startTime.min
					);

					printSeperator();

					stop = checkIncorrectDate(data.tournaments[index].startTime, data.tournaments[index].endTime);

					if (stop != true)
					{
						cout << "\nError: The starting date is after the ending date!\n";
						cout << "Please try again!\n";
					}

					data.calcDuration(
						data.tournaments[index].startTime,
						data.tournaments[index].endTime,
						data.tournaments[index].duration
					);

					if (data.tournaments[index].duration.year == 0
						&& data.tournaments[index].duration.month == 0
						&& data.tournaments[index].duration.day == 0
						&& data.tournaments[index].duration.hour == 0
						&& data.tournaments[index].duration.min < 30
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
					printSeperator();
					cout << "Enter end date:\n";
					enterDate(
						data.tournaments[index].endTime.year,
						data.tournaments[index].endTime.month,
						data.tournaments[index].endTime.day
					);

					enterTime(
						data.tournaments[index].endTime.hour,
						data.tournaments[index].endTime.min
					);

					printSeperator();

					stop = checkIncorrectDate(data.tournaments[index].startTime, data.tournaments[index].endTime);

					if (stop != true)
					{
						cout << "\nError: The starting date is after the ending date!\n";
						cout << "Please try again!\n";
					}

					data.calcDuration(
						data.tournaments[index].startTime,
						data.tournaments[index].endTime,
						data.tournaments[index].duration
					);

					if (data.tournaments[index].duration.year == 0
						&& data.tournaments[index].duration.month == 0
						&& data.tournaments[index].duration.day == 0
						&& data.tournaments[index].duration.hour == 0
						&& data.tournaments[index].duration.min < 30)
					{
						cout << "\nA tournament have to last at least 30 minutes!\n";
						cout << "Please try again!\n";
						stop = false;
					}

				} while (stop != true);
				break;
			default: break;
		}
	}

	// A function that edit the choosen team's information
	void editTeam(int choice, int id, int teamIndex) {
		int editPlayerNumber;
		bool checkPlayerNumber;

		switch (choice)
		{
			case 1:
				cout << "Enter new team's name: ";
				cin.ignore();
				getline(cin, data.tournaments[id].teams[teamIndex].name);
				break;

			case 2:
				cout << "Enter new team's tag: ";
				cin.ignore();
				getline(cin, data.tournaments[id].teams[teamIndex].tag);
				break;

			case 3:
				do
				{
					cout << "Enter the player's number: ";
					cin >> editPlayerNumber;
					checkPlayerNumber = data.checkPlayerByNumber(editPlayerNumber, id);
					if (checkPlayerNumber != true)
					{
						cout << "There is no player with this number!\nPlease try again!\n";
					}
					else
					{
						cout << "Enter new player's name: ";
						cin.ignore();
						getline(cin, data.tournaments[id].teams[teamIndex].playerNames[editPlayerNumber - 1]);
					}
				} while (checkPlayerNumber != true);

			default:
				break;
		}

	}

	// A function that shows the user's edit options
	void editTournamentMenu() {
		int id, tIndex, editChoice, editTeamChoice, teamIndex;
		bool teamNumberCheck;

		do
		{
			cout << "Enter the tournament's ID: ";
			cin >> id;
			tIndex = data.getTournamentIndexById(id);

			if (tIndex != -1)
			{
				printSeperator();
				cout << "Edit options:\n";
				cout << "1. Change the tournament's name \n";
				cout << "2. Change the tournament's prize \n";
				cout << "3. Change the date of starting \n";
				cout << "4. Change the date of ending \n";
				cout << "5. Edit a team \n";
				cout << "9. Back to the main menu\n";
				cout << "\nEnter your choice: ";
				cin >> editChoice;

				if (editChoice != 5 && editChoice != 9)
					editTournament(editChoice, tIndex);

				if (editChoice == 5)
				{
					do
					{
						cout << "\nEnter the team's number: ";
						cin >> teamIndex;
						teamNumberCheck = data.checkTeamNumber(teamIndex, id);
						if (teamNumberCheck != true)
						{
							cout << "There is no team with that number!\nPlease try again!\n";
						}

					} while (teamNumberCheck != true);

					printSeperator();
					cout << "Edit options: \n";
					cout << "1. Change team's name \n";
					cout << "2. Change team's tag \n";
					cout << "3. Change player's name \n";
					cout << "\nEnter what you want to edit: ";
					cin >> editTeamChoice;
					editTeam(editTeamChoice, id, teamIndex - 1);

				}
			}
			else
			{
				cout << "There is not tournament with this ID!\nPlease try again:\n";
			}
		} while (tIndex == -1);
	}

	// A function that ask which tournament the user want to delete
	void deleteTournamentMenu()
	{
		int Id, checkId;

		do
		{
			cout << "\nEnter the tournament's ID: ";
			cin >> Id;

			checkId = data.getTournamentIndexById(Id);

			if (checkId != -1)
			{
				data.deleteTournament(checkId);
			}
			else
			{
				cout << "\nThere is not any tournament with this ID!\nPlease try again:";
			}
		} while (checkId == -1);
	}

	// A function that create a single tournament
	void createTournamentMenu() {

		TOURNAMENT_INFO ti;

		bool stop, checkPlayersCount = true, checkTeamCount = true;

		cout << "\nEnter tournament name: ";
		cin.ignore();
		getline(cin, ti.name);

		do
		{
			printSeperator();
			cout << "Enter start date:\n";
			enterDate(ti.startTime.year, ti.startTime.month, ti.startTime.day);
			enterTime(ti.startTime.hour, ti.startTime.min);
			printSeperator();
			cout << "Enter end date:\n";
			enterDate(ti.endTime.year, ti.endTime.month, ti.endTime.day);
			enterTime(ti.endTime.hour, ti.endTime.min);

			stop = checkIncorrectDate(ti.startTime, ti.endTime);

			if (stop != true)
			{
				cout << "\nError: The starting date is after the ending date!\n";
				cout << "Please try again!\n";
			}

			data.calcDuration(ti.startTime, ti.endTime, ti.duration);

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

		printSeperator();

		cout << "Enter tournament's prize: ";
		getline(cin, ti.prize);
		printSeperator();

		do
		{
			ti.teamCount = enterInt(1, 16, "Team count: ");
			if (ti.teamCount > 16)
			{
				cout << "There can't be more than 16 teams in a tournament!\nPlease try again:\n";
				checkTeamCount = false;
			}
		} while (checkTeamCount != true);

		do
		{
			ti.playersOnTeam = enterInt(1, 5, "Enter how much players are in a team: ");
			if (ti.playersOnTeam > 5)
			{
				cout << "There must be less than or equal to 5 players in a team!\nPlease try again:\n";
				checkPlayersCount = false;
			}

		} while (checkPlayersCount != true);
		printSeperator();

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
				printSeperator();
			}

		}
		data.createTournament(ti);
	}

	// A function that manages the main menu
	bool menuChoice(bool& isEntered) {
		int choice;

		cin >> choice;

		if (!isEntered)
		{
			switch (choice)
			{
				case 1:
					createTournamentMenu();
					isEntered = true;
					break;
				case 9:
					return false;
					break;
				default:
					cout << "\nThere is no such a option!\n\n";
					break;
			}
		}
		else
		{
			switch (choice)
			{
				case 1:
					createTournamentMenu();
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
					return false;
					break;

				default:
					cout << "\nThere is no such a option!\n\n";
					break;
			}
			return true;
		}

	}
};

int main()
{
	system("color 0b");

	Data data;
	Presentation present(data);

	bool isEntered = false;
	bool stop = true;

	present.greetings();
	
	do
	{
		stop = present.displayMenu(isEntered);
	} while (stop);
}
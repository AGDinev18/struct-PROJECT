#include <iostream>
#include <string>
#include <sstream>
#include "structures.h"

using namespace std;

void printSeperator()
{
	cout << "-----------------------\n";
}

// A function that cheks if the given date is valid
bool checkIncorrectDate(DATE start, DATE end) {

	if (start.year > end.year
		|| (start.year == end.year && start.month > end.month)
		|| (start.month == end.month && start.day > end.day)
		|| (start.day == end.day && start.hour > end.hour)
		|| (start.hour == end.hour && start.min > end.min))
		return false;

	return true;
}

// A function that calculate the duration for specific time
void calcSpecTime(int& start, int& end, int& dur) {
	bool stop = true;
	do
	{
		if (end > start) {
			end--;
			dur++;
		}
		else
		{
			stop = false;
		}

	} while (stop);

}

// A function that checks if there are no letters in the input
bool tryReadInt(int& result, int min, int max) {

	string input = "";

	if (getline(cin, input))
	{
		stringstream ss(input);
		if (ss >> result)
		{
			if (result >= min && result <= max)
			{
				return true;
			}
		}
		else return false;
	}
	return false;
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
	const int MAX_VALID_YR = 3000;
	const int MIN_VALID_YR = 1900;
	// If year, month and day  
	// are not in given range 
	if (y > MAX_VALID_YR || y < MIN_VALID_YR)
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

// A function that is used to check if the input is valid
int enterInt(int min, int max, string text)
{
	bool isValid;
	int result;

	do
	{
		cout << text;
		isValid = tryReadInt(result, min, max);
		if (!isValid) {
			cout << "\nInvalid value!\n" << endl;
		}
	} while (!isValid);

	return result;
}

// A function that is used to enter the start and date
void enterDate(int& year, int& month, int& day)
{
	bool isDateValid;

	do
	{
		day = enterInt(1, 31, " Day: ");
		month = enterInt(1, 12, " Month: ");
		year = enterInt(2000, 2030, " Year: ");


		isDateValid = isValidDate(day, month, year);

	} while (!isDateValid);
}

// A function that is used to enter the hours and minutes of the tournament
void enterTime(int& hour, int& min) {

	hour = enterInt(0, 24, " Hour: ");
	min = enterInt(0, 59, " Minute: ");

}
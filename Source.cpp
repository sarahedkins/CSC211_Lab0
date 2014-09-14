/* 
Sarah Edkins
9/13/2014
CSC 211 
LAB 0

This program reads in dates from a file in MM/DD/YYYY format,
calculates the "day value" from start date of 01/01/1900
and prints the day value and the day of the week.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

// function prototypes
bool checkLeapYear(int YEAR);
int numDaysInMonth(int MONTH, int YEAR);
int daysInYear(int YEAR);
int dayValue(int YEAR, int MONTH, int DAY);
void separateDate(string DATE, int& input_day, int& input_month, int& input_year);
string getWEEKDAY(int dayValue);

int main() {

	// declare & initialize variables
	ifstream infile;
	string file_name = "dates.txt";
	int input_day = 0, input_month = 0, input_year = 0;
	string inputDATE = "00/00/0000";
	int day_value = 0;

	// get input from file
	infile.open(file_name);
	if (!infile)
	{
		cout << endl << "Error opening file " << file_name << endl;
		system("pause");
		return 0;
	}

	// loop in dates from file, compute "day value" and weekday
	while (!infile.eof()) {
		infile >> inputDATE;
		separateDate(inputDATE, input_day, input_month, input_year);
		day_value = dayValue(input_year, input_month, input_day);

		//print "day value" and weekday
		cout << endl << getWEEKDAY(day_value) << " " << inputDATE << " has a day value of " << day_value;
	}

	// pauses console
	cout << endl;
	system("pause");
	return 0;

} // end of main

// function definitions

// given a year, returns true if it is a leap year
bool checkLeapYear(int YEAR){
	if (YEAR % 4 == 0 && YEAR % 100 != 0)
		return true;
	else if (YEAR % 4 == 0 && YEAR % 100 == 0 && YEAR % 400 == 0)
		return true;
	else
		return false;
}

// returns the number of days in the given month, given a month & year
int numDaysInMonth(int MONTH, int YEAR){
	int monthDAYS = 31;
	int monthsWith30[] = { 4, 6, 9, 11 };

	for (int i = 0; i < 4; i++) {
		if (monthsWith30[i] == MONTH)
			monthDAYS = 30;
	}

	if (MONTH == 2) {
		if (checkLeapYear(YEAR))
			monthDAYS = 29;
		else monthDAYS = 28;
	}	

	return monthDAYS;
}

// given a year, outputs the number of days in that year
int daysInYear(int YEAR) {
	int sum = 0;
	for (int month = 1; month <= 12; month++)
		sum += numDaysInMonth(month, YEAR);

	return sum;
}

// given a date, output its "day value"
int dayValue(int YEAR, int MONTH, int DAY){
	int dayValue = 0;
	int yearCounter = 1900, monthCounter = 1;

		while (yearCounter < YEAR) {
			dayValue += daysInYear(yearCounter);
			yearCounter++;
		}

		while (monthCounter < MONTH) {
				dayValue += numDaysInMonth(MONTH, YEAR);
				monthCounter++;
			}
	
	dayValue += DAY;

	return dayValue;
}

// given a day value, determine the day of the week
string getWEEKDAY(int dayValue) {
	string weekday = "NONE";
	int dayNUM = dayValue % 7;

	switch (dayNUM) {
	case 1: weekday = "Monday";
		break;
	case 2: weekday = "Tuesday";
		break;
	case 3: weekday = "Wednesday";
		break;
	case 4: weekday = "Thursday";
		break;
	case 5: weekday = "Friday";
		break;
	case 6: weekday = "Saturday";
		break;
	case 0: weekday = "Sunday";
		break;
	default: weekday = "[Error: day of week unknown]";
	}

	return weekday;
}

// given date in 01/01/1900 format, separate into DAY, MONTH, YEAR variables
void separateDate(string DATE, int& input_day, int& input_month, int& input_year) {
	sscanf_s(DATE.c_str(), "%d/%d/%d", &input_month, &input_day, &input_year);
}
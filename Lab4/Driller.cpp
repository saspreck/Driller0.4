// Driller0.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <set>
#include <array>
#include <algorithm>

using namespace std;

/*
Function to check if the date stamp matches the correct one
*/
bool checkDateStamp(string dataLine, string dateStamp, int lineNum) {
	//creates a substring that contains only the date
	string dateCheck = dataLine.substr(0, dataLine.find(','));
	//checks if the substring doesn't match the correct one
	if (dateCheck != dateStamp) {
		//prints out the error message
		cout << "Non-matching date stamp " << dateCheck << " at line " << lineNum << "." << endl;
		return false;
	}
	else {
		return true;
	}

}

/*
Function to check if the time stamp is unique
*/
bool checkTimeStamp(string dataLine, set<string>& timeStamps, int lineNum) {

	//gets the initial size of the set
	int timeStampStartSize = (int)timeStamps.size();

	//makes a substring of everything except the date
	string dataLineMinusDate = dataLine.substr(dataLine.find(',') + 1);

	//makes a substring of the time stamp
	string timeStampToCheck = dataLineMinusDate.substr(0, dataLineMinusDate.find(','));

	//attempts to insert the time stamp into the set
	timeStamps.insert(timeStampToCheck);

	//if the size of the set did not increase then the time stamp was not unique
	if (timeStampStartSize == (int)timeStamps.size()) {

		//prints out error message
		cout << "Duplicate timestamp " << timeStampToCheck << " at line " << lineNum << "." << endl;
		return false;
	}
	else {
		return true;
	}

}

/*
Function to check that all the float values are positive
*/
bool checkFloatValues(string dataLine, int lineNum) {
	//declare variables
	string tempData;
	float floatData;

	//turn input string into a stringstream
	stringstream stringData(dataLine);

	//ignores the date and time stamps
	stringData.ignore(256, ',');
	stringData.ignore(256, ',');

	//iterates through each data point checking
	for (int i = 0; i < 16; i++) {
		//splits each piece of data off from the stringstream and turns it into a float
		getline(stringData, tempData, ',');
		floatData = stof(tempData);

		//checks if the data is positive and throws an error otherwise
		if (floatData <= 0) {
			cout << "Invalid floating-point data at line " << lineNum << "." << endl;
			return false;
		}
	}
	//returns true if all the data values are positive
	return true;
}

int main()
{
	//declare variables
	int dataLineNum = 1;
	string initialDateStamp = "";
	int validLines = 0;

	//declare set to hold all time stamps
	set<string> timeStamps;

	//declares DrillingRecordArray object to use
	ResizableArray<DrillingRecord>* mainRecordArray = new ResizableArray<DrillingRecord>;

	//declares variable to store file line in and then skips the first line
	string line = "";
	cin.ignore(1000, '\n');

	//while loop to iterate through the file collecting data line by line
	while (getline(cin, line)) {

		//assign date stamp
		if (initialDateStamp == "") {
			initialDateStamp = line.substr(0, line.find(','));
		}

		//calls the checkDateStamp function to ensure date stamps are correct
		if (checkDateStamp(line, initialDateStamp, dataLineNum)) {

			//calls the checkTimeStamp function to ensure time stamps are unique
			if (checkTimeStamp(line, timeStamps, dataLineNum)) {

				//calls the checkFloatValues method to ensure they are positive
				if (checkFloatValues(line, dataLineNum)) {

					//declares a drilling record to use and a string stream
					DrillingRecord* currentRecord = new DrillingRecord;

					//pulls off datestamp and puts it in correct array
					string dateStamp = line.substr(0, line.find(','));
					currentRecord->addString(dateStamp);

					//pulls off timestamp and puts it in correct array
					string noDateStamp = line.substr(line.find(',') + 1);
					string timeStamp = noDateStamp.substr(0, noDateStamp.find(','));
					currentRecord->addString(timeStamp);

					string noTimeStamp = noDateStamp.substr(noDateStamp.find(',') + 1);
					stringstream noStrings(noTimeStamp);

					//splices off each piece of data, turns it to a double, and then puts it into the correct array
					for (int i = 0; i < 16; i++) {
						string tempData = "";
						getline(noStrings, tempData, ',');
						double doubleData = stod(tempData);
						currentRecord->addNum(doubleData);

					}

					//adds the current drilling record to the drilling array and increments the number of valid lines
					mainRecordArray->add(*currentRecord);
					validLines++;

				}
			}
		}
		//increases the line number
		dataLineNum++;
	}

	//iterates through and prints out data
	for (int i = validLines - 1; i >= 0; i--) {

		//try/catch block to catch an IndexOutOfRange exception
		try {
			cout << mainRecordArray->get(i) << endl;
		}
		catch (ExceptionIndexOutOfRange* e) {
			delete e;
		}
	}

	return 0;

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


#include "DrillingRecord.h"
#include "Exceptions.h"
#include <iomanip>
#include <iostream>
using namespace std;


/*
Method to add num to array and increment the counter
*/
void DrillingRecord::addNum(double num) {
	nums[numCtr] = num;
	numCtr++;
}

/*
Method to add string to array and increment the counter
*/
void DrillingRecord::addString(string string) {
	strings[strCtr] = string;
	strCtr++;
}

/*
Returns the double at the given index
*/
double DrillingRecord::getNum(unsigned int index) const {
	
	//checks if index is less than numCtr and throws an exception otherwise
	if (index < this->numCtr) {
		return nums[index];
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}
}

/*
Returns the string at the given index
*/
string DrillingRecord::getString(unsigned int index) const {
	
	//checks if index is less than strCtr and throws an exception otherwise
	if (index < this->strCtr) {
		return strings[index];
	}
	else {
		throw new ExceptionIndexOutOfRange();
	}
}

/*
Overloaded ostream operator to create correct output
*/
ostream& operator<<(ostream& os, const DrillingRecord& record) {

	for (unsigned int i = 0; i < record.strCtr; i++) {

		//try/catch block to handle IndexOutOfRange exception in the ostream
		try {
			os << record.getString(i) << ";";
		}
		catch (ExceptionIndexOutOfRange* e) {
			delete e;
		}
		
	}

	for (unsigned int i = 0; i < record.numCtr; i++) {
		
		//try/catch block to handle IndexOutOfRange exception in the ostream
		try {
			if (i == record.numCtr - 1) {
				os << fixed << setprecision(2) << record.getNum(i);
			}
			else {
				os << fixed << setprecision(2) << record.getNum(i) << ";";
			}
		}
		catch (ExceptionIndexOutOfRange* e) {
			delete e;
		}
		

	}

	return os;
}
#pragma once

#include <string>
#include <vector>

#include "Shift.h"

using namespace std;

class Driver {
public:
	

	Driver(unsigned int ID, string name, unsigned int shiftsize, unsigned int weeklyhourlimit, unsigned int minresttime, vector<Shift> shifts);
	~Driver();

	//setters

	void setID(unsigned int ID);
	void setName(string name);
	void setShiftSize(unsigned int shiftsize);
	void setWeeklyHourLimit(unsigned int weeklyhourlimit);
	void setMinRestTime(unsigned int minresttime);
	void setShifts(vector<Shift> shifts);


	//getters

	unsigned int getID() const;
	string getName() const;
	unsigned int getShiftSize() const;
	unsigned int getWeeklyHourLimit() const;
	unsigned int getMinRestTime() const;
	vector<Shift> getShifts() const;

private:
	unsigned int ID; //the driver's unique ID
	string name; //the driver's name
	unsigned int shiftsize; //shift size - number of hours the driver can work per day
	unsigned int weeklyhourlimit; //number of hours the driver can work per week
	unsigned int minresttime; //minimum rest time between shifts (hours)
	vector<Shift> shifts; //list of shifts the driver was assigned to do
};


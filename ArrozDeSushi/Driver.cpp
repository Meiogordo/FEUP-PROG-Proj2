#include "Driver.h"

Driver::Driver() {}

Driver::Driver(string rawline) : weeklyhoursdrivensofar(0) {

	//Splitting the information by ";" - which is the information splitter
	vector<string> info = Utilities::splitString(rawline, ";");

	//Trimming the info to remove excess spaces
	for (int i = 0; i < info.size(); i++) {
		Utilities::trimString(info[i]);
	}

	//vector organization
	// 0 - ID
	// 1 - Name
	// 2 - Shift size
	// 3 - Weekly hour limit
	// 4 - Minimum rest time between shifts

	int ID = stoi(info[0]);
	string name = info[1]; //the driver's name
	int shiftsize = stoi(info[2]); //shift size - number of hours the driver can work per day
	int weeklyhourlimit = stoi(info[3]); //number of hours the driver can work per week
	int minresttime = stoi(info[4]); //minimum rest time between shifts (hours)

	//Assigning values to Driver object
	this->ID = ID;
	this->name = name;
	this->shiftsize = shiftsize;
	this->weeklyhourlimit = weeklyhourlimit;
	this->minresttime = minresttime;
	//Data not gotten from string from text file
	this->shifts = vector<Shift>(); //Empty vector of shifts
}

Driver::Driver(unsigned int ID, string name, unsigned int shiftsize, unsigned int weeklyhourlimit, unsigned int minresttime, const vector<Shift> &shifts)
	: ID(ID), name(name), shiftsize(shiftsize), weeklyhourlimit(weeklyhourlimit), minresttime(minresttime), shifts(shifts), weeklyhoursdrivensofar(0)
{}

Driver::~Driver() {}

unsigned int Driver::getID() const {
	return ID;
}

string Driver::getName() const {
	return name;
}

unsigned int Driver::getShiftSize() const {
	return shiftsize;
}

unsigned int Driver::getWeeklyHourLimit() const {
	return weeklyhourlimit;
}

unsigned int Driver::getMinRestTime() const {
	return minresttime;
}

vector<Shift> Driver::getShifts() const {
	return shifts;
}

unsigned int Driver::getWeeklyHoursDrivenSoFar() const {
	return weeklyhoursdrivensofar;
}

void Driver::setID(unsigned int ID) {
	this->ID = ID;
}

void Driver::setName(string name) {
	this->name = name;
}

void Driver::setShiftSize(unsigned int shiftsize) {
	this->shiftsize = shiftsize;
}

void Driver::setWeeklyHourLimit(unsigned int weeklyhourlimit) {
	this->weeklyhourlimit;
}

void Driver::setMinRestTime(unsigned int minresttime) {
	this->minresttime;
}

void Driver::setShifts(const vector<Shift> &shifts) {
	this->shifts = shifts;
}

unsigned int Driver::addShift(const Shift &newShift) {

	////Return values:
	/*
	0: Process possible, everything normal and the shift was added to the driver
	1: Max weekly hours were reached or will be overcome with this shift
	2: Time since last shift and until the next shift is >= than the minimum rest time
	3: Shift size is larger than the maximum shift size
	other: unexpected behaviour (as in not coded for now and should never happen because the returns are specific values, but just in case)
	*/

	//Verifying if the shift can be added

	//Getting the shift size in hours - the shifts are always a multiple of 1 hour so there is no problem with rounding values
	unsigned int newShiftSizeHours = (newShift.getEndTime() - newShift.getStartTime()) / 60;

	//#1
	//Checking if the weeklyhourlimit was overcome or will be overcome with the addition of the new Shift - if it is, return 1 as an error code
	if (weeklyhoursdrivensofar + newShiftSizeHours > weeklyhourlimit)
		return 1;

	//#2
	//Checking if the time since the last shift and the time until the next shift is >= than the minimum rest time

	//If the shifts vector is empty, then this criteria is always ok, so we only check it if the vector is not empty
	if (!shifts.empty()) {

		//The shift before is the one with the end time closest to the start time of the new shift
		//The shift after is the one with the start time closest to the end time of the new shift

		unsigned int indexOfShiftBefore = 0, indexOfShiftAfter = 0;

		for (int i = 0; i < shifts.size(); ++i) {
			//If the shift ends before the newShift starts, check if it is the closest before
			if (shifts[i].getEndTime() < newShift.getStartTime())
				//If the time from the shift end time to the start of new shift is less than the time from the previous closest before shift, then the shift at i is closer to the start of newShift
				if (shifts[i].getEndTime() - newShift.getStartTime() < shifts[indexOfShiftBefore].getEndTime() - newShift.getStartTime())
					indexOfShiftBefore = i; //As such, change the value of indexOfShiftBefore to i

			//If the shift starts after the newShift ends, check if it is the closest after
			if (shifts[i].getStartTime() > newShift.getEndTime())
				//If the time from the new shift end until the other shift start time is less than the time from the new shift end to the previous closest shift after start time, then the shift at i is closer to the end of newShift
				if (newShift.getEndTime() - shifts[i].getStartTime() < newShift.getEndTime() - shifts[indexOfShiftAfter].getStartTime())
					indexOfShiftAfter = i; //As such, change the value of indexOfShiftAfter to i
					
		}

		//The indexes are set, now to check if the time intervals from the end of the shift before to the start of newShift or the time from the end of the newShift to the start of the next shift are bigger than minresttime
		//Divided by 60 to convert from minutes to hours
		if (   (((shifts[indexOfShiftBefore].getEndTime() - newShift.getStartTime()) / 60) < minresttime) || (((newShift.getEndTime() - shifts[indexOfShiftAfter].getStartTime()) / 60) < minresttime)   )
			return 2; //if it is, return 2 as an error code
	}

	//#3
	//Checking if the newShift's size is larger than the maximum shift size
	if (newShiftSizeHours > shiftsize)
		return 3; //if it is, return 3 as an error code


	//If none of the above are verified, the shift can be assigned to driver
	//Thus, we push back the shift into the shifts vector, increment weeklyhoursdrivensofar and return 0 (process successful)
	shifts.push_back(newShift);
	weeklyhoursdrivensofar += newShiftSizeHours;
	//Also don't forget to sort the shifts to help with searching for the previous shift, for the rest time checks
	sort(shifts.begin(), shifts.end());
	return 0; //Process concluded successfuly
}

bool Driver::isAvailable() const {
	//If the driver hasn't hit the maximum number of weekly hours then he is available
	return weeklyhoursdrivensofar < weeklyhourlimit;
}

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Shift {
public:
	Shift(unsigned int busLineID, unsigned int driverID, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime);
	~Shift();

	//getters
	
	unsigned int getBusLineId() const;
	unsigned int getDriverId() const;
	unsigned int getBusOrderNumber() const; // order of the bus within the bus line
	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	

	//setters
	
	unsigned int setBusLineId(unsigned int busLineID);
	unsigned int setDriverId(unsigned int driverID);
	unsigned int setBusOrderNumber(unsigned int busOrderNumber);
	unsigned int setStartTime(unsigned int startTime);
	unsigned int setEndTime(unsigned int endTime);
	
	// other methods

private:
	unsigned int busLineID;
	unsigned int driverID;
	unsigned int busOrderNumber; //TODO: Understand what this is
	//TODO: Switch to the upcoming date/time class
	unsigned int startTime;
	unsigned int endTime;
};

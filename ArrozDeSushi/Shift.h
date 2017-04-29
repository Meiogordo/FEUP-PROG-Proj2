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
	
	void setBusLineId(unsigned int busLineID);
	void setDriverId(unsigned int driverID);
	void setBusOrderNumber(unsigned int busOrderNumber);
	void setStartTime(unsigned int startTime);
	void setEndTime(unsigned int endTime);
	
	// other methods

private:
	unsigned int busLineID;
	unsigned int driverID;
	unsigned int busOrderNumber; //TODO: Understand what this is
	//TODO: Switch to the upcoming date/time class
	unsigned int startTime;
	unsigned int endTime;
};

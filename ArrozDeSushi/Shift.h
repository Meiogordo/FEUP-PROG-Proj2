#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Shift {
public:
	Shift(unsigned int busLineID, unsigned int driverID, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime);
	~Shift();

	//getters
	
	unsigned int getBusLineID() const;
	unsigned int getDriverID() const;
	unsigned int getBusID() const; // order of the bus within the bus line
	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	
	//setters
	
	void setBusLineID(unsigned int busLineID);
	void setDriverID(unsigned int driverID);
	void setBusID(unsigned int busOrderNumber);
	void setStartTime(unsigned int startTime);
	void setEndTime(unsigned int endTime);
	
	// other methods

private:
	unsigned int busLineID;
	unsigned int driverID;
	unsigned int busID;
	unsigned int startTime;
	unsigned int endTime;
};

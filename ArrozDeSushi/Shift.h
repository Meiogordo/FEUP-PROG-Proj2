#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Shift {
public:
	Shift(unsigned int lineID, unsigned int driverID, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime);
	~Shift();

	//getters
	
	unsigned int getLineID() const;
	unsigned int getDriverID() const;
	unsigned int getBusOrderNumber() const;
	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	
	//setters
	
	void setLineID(unsigned int lineID);
	void setDriverID(unsigned int driverID);
	void setBusOrderNumber(unsigned int busOrderNumber);
	void setStartTime(unsigned int startTime);
	void setEndTime(unsigned int endTime);
	
	// other methods
	//Overloading less than operator for Shift to be able to use std::sort - will be sorted by startTime (it is the easier way to sort)
	bool operator<(const Shift &s) const;

private:
	unsigned int lineID;
	unsigned int driverID;
	unsigned int busOrderNumber;
	//In minutes, but considering whole week - [0,8639] (?)
	unsigned int startTime;
	unsigned int endTime;
};

//////////////////////////////////////////////////
//
// THIS DOES NOTHING FOR NOW, WE NEED TO UNDERSTAND WHAT IT IS USED FOR
//
//////////////////////////////////////////////////


#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Shift.h"


using namespace std;

class Bus {
public:

	Bus();
	Bus(unsigned int lineID, unsigned int startTime, unsigned int endTime);
	~Bus();

	//getters
	unsigned int getLineID() const;
	unsigned int getBusOrderInLine() const;
	static int getTotalBuses();
	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	vector<Shift> getRemainingWork() const;

	//setters
	void setLineID(unsigned int lineID);
	void setStartTime(unsigned int startTime);
	void setEndTime(unsigned int endTime);
	//Used to reset total buses between lines
	static void setTotalBuses(unsigned int totalBuses);
	//When work is assigned to the bus, it needs to be removed from the list of remaining work
	bool removeWork(unsigned int startTime, unsigned int endTime);

	// other methods
private:

	unsigned int lineID;
	unsigned int orderInLine;
	static unsigned int totalBuses;
	//Start and end times in minutes
	unsigned int startTime;
	unsigned int endTime;
	vector<Shift> remainingWork;
};

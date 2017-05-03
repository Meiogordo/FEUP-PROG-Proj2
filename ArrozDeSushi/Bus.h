//////////////////////////////////////////////////
//
// THIS DOES NOTHING FOR NOW, WE NEED TO UNDERSTAND WHAT IT IS USED FOR
//
//////////////////////////////////////////////////


#pragma once

#include <iostream>
#include <vector>

#include "Shift.h"


using namespace std;

class Bus {
public:
	Bus();
	Bus(unsigned int driverID, unsigned int lineID, unsigned int orderInLine, const vector<Shift> &shift);
	~Bus();
	//getters
	unsigned int getBusOrderInLine() const;
	unsigned int getDriverID() const;
	unsigned int getLineID() const;
	vector<Shift> getSchedule() const;
	static int getTotalBuses();
	bool getIsWorking();
	//setters
	void setDriverID(unsigned int driverID);
	void setLineID(unsigned int lineID);
	bool setIsWorking(bool isWorking);
	// other methods
private:
	unsigned int ID;
	unsigned int orderInLine;
	unsigned int driverID;
	unsigned int lineID;
	vector<Shift> schedule;
	static unsigned int totalBuses;
	bool isWorking;

};

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
	Bus(unsigned int ID, unsigned int driverID, unsigned int lineID);
	~Bus();
	//getters
	unsigned int getBusOrderInLine() const;
	unsigned int getDriverID() const;
	unsigned int getLineID() const;
	vector<Shift> getSchedule() const;
	//setters
	unsigned int setDriverID(unsigned int driverID);
	unsigned int setLineID(unsigned int lineID);
	// other methods
private:
	unsigned int ID; //not sure about this
	unsigned int orderInLine;
	unsigned int driverID;
	unsigned int lineID;
	vector<Shift> schedule;

};

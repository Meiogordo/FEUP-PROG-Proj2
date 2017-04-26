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
private:
	unsigned int orderInLine;
	unsigned int driverID;
	unsigned int lineID;
	vector<Shift> schedule;
public:
	Bus(unsigned int id, unsigned int driver, unsigned int line);
	// get methods
	unsigned int getBusOrderInLine() const;
	unsigned int getDriverID() const;
	unsigned int getLineID() const;
	vector<Shift> getSchedule() const;
	// set methods
	unsigned int setDriverID(unsigned int driverID);
	unsigned int setLineID(unsigned int lineID);
	// other methods

};

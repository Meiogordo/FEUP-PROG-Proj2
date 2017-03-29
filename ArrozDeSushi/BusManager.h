#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Utilities.h"
using namespace std;

class BusManager {
public:
	//Constructor manages file input while also checking if the file path is valid
	BusManager();
	~BusManager();
private:
	//Describing a driver
	struct driver {
		int ID; //the driver's unique ID
		string name; //the driver's name
		int shiftsize; //shift size - number of hours the driver can work per day
		int weeklyhourlimit; //number of hours the driver can work per day
		int minresttime; //minimum rest time between shifts (hours)
	};
	//Describing a line
	struct line {
		int ID; //line ID
		int frequency; //frequency of buses in the line (minutes)
		vector<string> stops; //list of stop names
		vector<int> delaybetweenstops; //times (int minutes) of travel between stops (TODO: Add note about indexes)
	};

	//Internal class data
	vector<driver> drivers;
	vector<line> lines;

	//Input data treatment
	//Generate driver from a line of text
	driver createDriverFromString(string rawline);
	//Generate line from a line of text
	line createLineFromString(string rawline);
};


#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class BusManager
{
public:
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
};


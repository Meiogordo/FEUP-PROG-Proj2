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

	//Data alteration - public so that the functions can be called from outside the class
	//Adds a new line, returns false if the line already exists (same ID)
	bool createNewLine();
	//Adds a new driver, returns false if the line already exists (same ID)
	bool createNewDriver();
	//Modifies a certain line, returns false if the line is not found
	bool modifyLine();
	//Modifies a certain driver, returns false if the driver is not found
	bool modifyDriver();
	//Deletes a line based on a given ID - returns true if successful, false if the ID returned no matches
	bool deleteLine();
	//Deletes a driver based on a given ID - returns true if successful, false if the ID returned no matches
	bool deleteDriver();

	//Data display - public so that the functions can be called from outside the class
	//Displays all the drivers
	void displayDrivers();
	//Displays drivers - if bool true, then only the available, if false, then only the occupied
	void displayDrivers(bool available);
	//Displays all the lines -> ID, First stop, Last stop
	void displayLines();

	//Data ouput - public so that the functions can be called from outside the class
	//Saves the updated list of drivers to the given file path. If the file exists it will be overwritten, if it does not it will be created
	void saveDriverstoFile(string filepath);
	//Saves the updated list of lines to the given file path. If the file exists it will be overwritten, if it does not it will be created
	void saveLinestoFile(string filepath);
	//Saves the list of schedules to the given file path. If the file exists it will be overwritten, if it does not it will be created
	void saveSchedulestoFile(string filepath);


	//External data management - public to be accessible from outside the class
	//TODO: Move stuff done from constructor into Load
	//Loads data from files into class - returns true if successful, false if aborted
	bool Load();
	//Saves the internal information into files
	void Save();
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
		vector<int> delaybetweenstops; //times (in minutes) of travel between stops (TODO: Add note about indexes)
	};

	//Internal class data
	vector<driver> drivers;
	vector<line> lines;
	//vector<schedule?> stopSchedules;
	//Resets internal class data
	void Reset();

	//Input data treatment
	//Generate driver from a line of text
	driver createDriverFromString(string rawline);
	//Generate line from a line of text
	line createLineFromString(string rawline);

	//Generating schedules and distributing drivers - For part 2
	void generateSchedule();
	void generateSchedule(int stopID);
	void distributeDrivers();

	//Internal class data handling - searches for ID and whatnot
	//Searches for a certain stop, by name. Returns the vector of all the lines it belongs to
	vector<line> findStopinLines(string stopname);
	//Searches for a line by its ID, returns the index of the line in the "lines" vector. If not found returns -1
	int findLineByID(int lineID);
	//Searches for a driver by its ID, returns the index of the driver in the "drivers" vector. If not found returns -1
	int findDriverByID(int driverID);
	//Other (TODO: Later on sort these into other categories if possible)

	//Not sure if still necessary given how I'm thinking
	//Prints the given driver onto the screen
	void printDriver(driver d);
	//Prints the given line onto the screen
	void printLine(line l);
};


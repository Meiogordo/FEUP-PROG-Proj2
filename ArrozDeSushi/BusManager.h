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
	//Detailed data display
	//Asks for and ID and then prints detailed info about that driver
	bool printDriver();
	//Asks for and ID and then prints detailed info about that line
	bool printLine();

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

	//Other
	//Finds which lines a stop belongs to
	void findStopsinLines();
	
private:
	//Describing a shift
	struct shift {
		unsigned int startHour; //hour at which the shift starts
		unsigned int endHour; //hour at which the shift ends
		unsigned int weekday; //day of week, starts at monday and is [0,6] with 0 being monday and 6 sunday
	};
	//Describing a driver
	struct driver {
		int ID; //the driver's unique ID
		string name; //the driver's name
		int shiftsize; //shift size - number of hours the driver can work per day
		int weeklyhourlimit; //number of hours the driver can work per week
		int minresttime; //minimum rest time between shifts (hours)
		vector<shift> shifts; //list of shifts the driver was assigned to do
		bool available; //true if the driver is available, false if not
	};
	//Describing a line
	struct line {
		int ID; //line ID
		int frequency; //frequency of buses in the line (minutes)
		vector<string> stops; //list of stop names
		vector<int> delaybetweenstops; //times (in minutes) of travel between stops (TODO: Add note about indexes)
	};

	//Internal class data
	vector<driver> drivers; //vector of all the drivers
	vector<line> lines; //vector of all the lines
	//vector<stops> stopsBelongToLines; //something to say in what lines a stop is
	//vector<schedule?> stopSchedules;
	//Schedule constants
	const unsigned int BUS_START_TIME = 8; //Service starts at 8:00
	const unsigned int BUS_END_TIME = 20; //Service ends at 20:00
	//Resets internal class data
	void Reset();

	//Input data treatment
	//Generate driver from a line of text
	driver createDriverFromString(string rawline);
	//Generate line from a line of text
	line createLineFromString(string rawline);

	//Generating schedules
	void generateSchedule();
	void generateSchedule(string stopname);

	//Distributing drivers - For part 2
	//void distributeDrivers();

	//Internal class data handling - searches for ID and whatnot
	//Searches for a certain stop, by name. Returns the vector of all the lines it belongs to
	vector<line> findStopinLines(string stopname);
	//Searches for a line by its ID, returns the index of the line in the "lines" vector. If not found returns -1
	int findLineByID(int lineID);
	//Searches for a driver by its ID, returns the index of the driver in the "drivers" vector. If not found returns -1
	int findDriverByID(int driverID);
	//Searches for a certain stop in all of the lines and returns a vector of line IDs to which the given stop belongs
	vector<int> findStopsinLines(string stopname);
	//Other (TODO: Later on sort these into other categories if possible)

	//These four are private because there is no need to access them externally, modify and print without parameters should be used for modification and printing and nothing else
	//Modify line helper, takes in the choice and position of the line in the lines vector and modifies the selected attribute
	bool modifyLine(unsigned int choice, int pos);
	//Modify driver helper, takes in the choice and position of the line in the lines vector and modifies the selected attribute
	bool modifyDriver(unsigned int choice, int pos);
	//Prints the driver with the given position in its vector onto the screen
	void printDriver(unsigned int pos);
	//Prints the line with the given position in its vector onto the screen
	void printLine(unsigned int pos);
};
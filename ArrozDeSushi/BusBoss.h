#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

#include "Utilities.h"
#include "Line.h"
#include "Driver.h"
#include "Shift.h"
#include "Bus.h"

using namespace std;

//Forward declarations to prevent conflicts
class Line;
class Driver;
class Shift;
class Bus;
struct Utilities::time;

//Overloading insertion operator: (Outside of class because the operands are of different types)
ostream& operator <<(ostream &os, const Line &l);
ostream& operator <<(ostream &os, const Driver &d);
ostream& operator <<(ostream &os, const Shift &s);
ostream& operator <<(ostream &os, const Bus &b);
ostream& operator <<(ostream &os, const Utilities::time &t);

class BusBoss {
public:
	BusBoss();
	~BusBoss();

	//Data alteration - public so that the functions can be called from outside the class
	//Adds a new driver, returns false if the line already exists (same ID)
	bool createNewDriver();
	//Modifies a certain driver, returns false if the driver is not found
	bool modifyDriver();
	//Deletes a driver based on a given ID - returns true if successful, false if the ID returned no matches
	bool deleteDriver();
	//Interactively assign a shift to a driver
	bool assignShift();

	//Data display - public so that the functions can be called from outside the class
	//Displays all the drivers
	void displayDrivers();
	//Displays drivers - if bool true, then only the available, if false, then only the occupied
	void displayDrivers(bool availability);
	//Displays all the lines -> ID, First stop, Last stop
	void displayLines();
	//Detailed data display
	//Asks for and ID and then prints detailed info about that driver
	bool printDriver();
	//Asks for and ID and then prints detailed info about that line
	bool printLine();
	//Prints a driver's assigned work
	bool printDriverShifts();
	//Prints a certain bus's information
	bool printBusInfo();
	//Lists the buses in a line
	bool listBusesInLine();
	//Lists all the unassigned periods for all buses of all lines
	bool listAllBusUnassignedPeriods();
	//Listing bus unassigned periods for a specific line
	bool listBusUnassignedPeriodsByLine();
	//Listing bus unassigned periods for a specific line and weekday
	bool listBusUnassignedPeriodsByLineAndWeekday();
	//Listing the periods in which the drivers do not have work assigned, for the available ones - just printing the shifts and saying that the remainder of the time they are free
	bool listDriverUnassignedPeriods();

	//External data management - public to be accessible from outside the class
	//Loads data from files into class - returns true if successful, false if aborted
	bool Load();
	//Saves the internal information into files
	bool Save();

	//Other
	//Finds which lines a stop belongs to - find which lines pass through a certain stop
	void findLinesinStop();
	//Calculates and displays the route between two given stops
	bool routeBetweenTwoStops();
	//Checks if the user has unsaved changes - getter method for hasUnsavedChanges - setter is not necessary because the setting is internal and done through direct access
	bool getIfHasUnsavedChanges();
	//Shows the schedule for a certain stop (includes all lines that pass there)
	bool showStopSchedule();
	//Shows the schedule for a certain line (all times for all stops in this certain line)
	bool showLineSchedule();
	//Get service start time in minutes
	static unsigned int getStartTime();
	//Get service end time in minutes
	static unsigned int getEndTime();

	//Checking if a given time interval can fit in an ordered vector of shifts - static since it does not depend on internal data and might be useful to use outside of the bb object or internally (same reason that it is public)
	static bool canFitInShiftInterval(unsigned int startTime, unsigned int endTime, const vector<Shift> &possibleShifts);

private:
	//Internal class data
	//Describing a route - used for storing data of paths between two stops
	struct route {
		bool switchesline; //defines if the route has a line switch
		
		//Data
		pair<unsigned int, unsigned int> lineIDs; //IDs of the lines that are being taken
		pair<short int, short int> directions; //direction of each of the routes to take, -1 for negative and 1 for positive
		pair<unsigned int, unsigned int> nStops; //number of stops to go through for each of the lines
		
		unsigned int totalTimeinMinutes; //total time in minutes that this route takes, used for sorting routes as well

		//Overloading less than operator for route to be able to use std::sort
		bool operator<(const BusBoss::route &r) const;
	};
	//Map of all the drivers, the key is the ID
	map<unsigned int, Driver> drivers;
	//Map of all the lines, the key is the ID
	map<unsigned int, Line> lines;
	//Company name
	string name;
	//Schedule constants
	//Service starts at 8:00
	static const unsigned int BUS_START_TIME_HOUR = 8;
	static const unsigned int BUS_START_TIME_MINUTE = 00;
	//Service ends at 20:00
	static const unsigned int BUS_END_TIME_HOUR = 20;
	static const unsigned int BUS_END_TIME_MINUTE = 0;
	//To better describe a stop schedule
	struct schedule {
		unsigned int lineID; //The id of the line that the schedule is for
		//The times at which the bus from a certain line passes through the stop
		vector<string> positiveBusTimes; //In the positive direction (start to finish)
		vector <string> negativeBusTimes; //In the negative direction (finish to start)
	};
	//Resets internal class data
	void Reset();

	//Internal class data handling - searches for ID and whatnot
	//Searches for a certain stop in all of the lines and returns a vector of line IDs to which the given stop belongs
	vector<unsigned int> findLinesinStop(string stopname);
	//Generating schedules
	//Generates the schedule for a stop for the specified lines
	vector<schedule> generateStopSchedules(string stop, vector<unsigned int> lineIDs);
	//Generates the schedule for a stop for the given lineID
	schedule generateStopSchedules(string stop, unsigned int lineID);


	//Other (TODO: Later on sort these into other categories if possible)

	//Many of these are private because there is no need to access them externally

	//Modify and print without parameters should be used for modification and printing and nothing else
	//Modify line helper, takes in the choice and position of the line in the lines vector and modifies the selected attribute
	bool modifyLine(unsigned int choice, int pos);
	//Modify driver helper, takes in the choice and position of the line in the lines vector and modifies the selected attribute
	bool modifyDriver(unsigned int choice, int pos);

	//Calculates the number of stops between two stops for each direction for a vector of lines
	vector<route> calculateRouteSameLine(string startStop, string endStop, vector<unsigned int> commonLines);
	//Calculates the number of stops in the best direction ([0] is direction - -1 or 1, [1] is length of travel)
	route calculateRouteSameLine(string startStop, string endStop, unsigned int commonLine);
	//Calculates the routes when switching lines - will be empty if it is not possible
	vector<route> calculateRouteSwitch(string stop1, string stop2, const vector<unsigned int> &foundLinesStop1, const vector<unsigned int> &foundLinesStop2);
	//Helper for vector overload, when a common stop is found creates a route representing the route found
	route calculateRouteSwitch(string stop1, string stop2, string commonstop, unsigned int stop1line, unsigned int stop2line);

	//Listing bus unassigned periods for a specific line - helper function with only direct printing
	void listBusUnassignedPeriodsByLine(unsigned int lineID);
	//Listing bus unassigned periods for a specific line and weekday - helper function with only direct printing
	void listBusUnassignedPeriodsByLineAndWeekday(unsigned int lineID, unsigned int desiredWeekday);
	//Listing bus unassigned periods for a specific line and weekday - helper function with direct printing and that returns the possible shifts to attribute for input checking
	vector<Shift> listBusUnassignedPeriodsByLineWeekdayAndBusOrderNumber(unsigned int lineID, unsigned int desiredWeekday, unsigned int busOrderNumber);

	//Prints a driver's shifts based on its ID
	void printDriverShifts(unsigned int driverID);

	//Gets the last or first stop of certain line (direction)
	string getDirection(unsigned int lineID, short int direction);

	//Data ouput helpers - private because they only need to be accessed by Save()
	//Path from where the drivers were loaded - used to save
	string driversFilePath;
	//Path from where the lines were loaded - used to save
	string linesFilePath;
	//Saves the updated list of drivers to the given file.
	void saveDriverstoFile(ostream &file);
	//Saves the updated list of lines to the given file path.
	void saveLinestoFile(ostream &file);
	//Also for data output but more of a Quality of Life tweak
	//Registers if the user has unsaved changes: to warn when opening a new file or exiting the program without saving before
	bool hasUnsavedChanges = false;
};


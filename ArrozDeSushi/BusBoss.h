#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Utilities.h"
#include "Line.h"
#include "Driver.h"

using namespace std;

class BusBoss {
public:
	BusBoss();
	~BusBoss();
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
	//Gets the amount of drivers needed for a specific line (assuming fixed shift sizes)
	bool getDriversNeeded();

private:
	//Internal class data
	//Describing a distance - using a struct instead of an int vector because when nested it would be confusing
	struct distance {
		int lineID; //ID of the line that is being taken
		short int direction; //direction of the shortest distance, -1 for negative and 1 for positive
		unsigned int nStops; //number of stops to go through
	};
	//Vector to give a string that represents the week day from the weekday variable in a shift
	const vector<string> weekdays = { "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado", "Domingo" };
	//Schedule constants
	//Service starts at 8:00
	const unsigned int BUS_START_TIME_HOUR = 8;
	const unsigned int BUS_START_TIME_MINUTE = 00;
	//Service ends at 20:00
	const unsigned int BUS_END_TIME_HOUR = 20;
	const unsigned int BUS_END_TIME_MINUTE = 0;
	//To better describe a stop schedule
	struct schedule {
		int lineID; //The id of the line that the schedule is for
		//The times at which the bus from a certain line passes through the stop
		vector<string> positiveBusTimes; //In the positive direction (start to finish)
		vector <string> negativeBusTimes; //In the negative direction (finish to start)
	};
	//Resets internal class data
	void Reset();

	//Input data treatment
	//Generate driver from a line of text
	driver createDriverFromString(string rawline);
	//Generate line from a line of text
	line createLineFromString(string rawline);

	//Internal class data handling - searches for ID and whatnot
	//Searches for a certain stop, by name. Returns the vector of all the lines it belongs to
	vector<line> findStopinLines(string stopname);
	//Searches for a line by its ID, returns the index of the line in the "lines" vector. If not found returns -1
	int findLineByID(int lineID);
	//Searches for a driver by its ID, returns the index of the driver in the "drivers" vector. If not found returns -1
	int findDriverByID(int driverID);
	//Searches for a certain stop in all of the lines and returns a vector of line IDs to which the given stop belongs
	vector<int> findLinesinStop(string stopname);
	//Generating schedules
	//Generates the schedule for a stop for the specified lines
	vector<schedule> generateStopSchedules(string stop, vector<int> lineIDs);
	//Generates the schedule for a stop for the given lineID
	schedule generateStopSchedules(string stop, int lineID);


	//Other (TODO: Later on sort these into other categories if possible)

	//These seven are private because there is no need to access them externally

	//Modify and print without parameters should be used for modification and printing and nothing else
	//Modify line helper, takes in the choice and position of the line in the lines vector and modifies the selected attribute
	bool modifyLine(unsigned int choice, int pos);
	//Modify driver helper, takes in the choice and position of the line in the lines vector and modifies the selected attribute
	bool modifyDriver(unsigned int choice, int pos);
	//Prints the driver with the given position in its vector onto the screen
	void printDriver(unsigned int pos);
	//Prints the line with the given position in its vector onto the screen
	void printLine(unsigned int pos);
	//Calculates the number of stops between two stops for each direction for a vector of lines
	vector<distance> calculateStopsForEachDirection(string startStop, string endStop, vector<int> commonLines);
	//Calculates the number of stops in the best direction ([0] is direction - -1 or 1, [1] is length of travel)
	distance calculateStopsForEachDirection(string startStop, string endStop, int commonLine);
	//Calculates the amount of drivers needed for a specific line - represented by its travel times (passed directly to avoid having to call findLinesByID) (assuming fixed shift size)
	int calculateDriversNeeded(const vector<int> &travelTimes, int frequency, int shiftsize);

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
private:
	string name;
	map<int, Driver> drivers;
	map<int, Line> lines;
};


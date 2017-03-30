#include "BusManager.h"

BusManager::BusManager() {
	ifstream inputDrivers, inputLines;
	string inputpath = "";

	//Drivers file input
	cout << "Insira o nome do ficheiro a usar para os condutores: (exemplo: \"condutores_test.txt\")" << endl;
	//Using getline because the path can contain spaces
	getline(cin, inputpath);
	//Opening the file with the given path
	inputDrivers.open(inputpath);

	//Testing if the path was invalid
	while (!inputDrivers.is_open()) {
		cout << "Nome do ficheiro inválido!" << endl;
		cout << "Insira o nome do ficheiro a usar para os condutores: (exemplo: \"condutores_test.txt\")" << endl;
		getline(cin, inputpath);
		inputDrivers.open(inputpath);
	}

	//Success
	cout << "\nFicheiro de condutores aberto com sucesso!\n\n\n";

	//Lines file input - same idea as above
	cout << "Insira o nome do ficheiro a usar para as linhas: (exemplo: \"linhas_test.txt\")" << endl;
	//Using getline because the path can contain spaces
	getline(cin, inputpath);
	//Opening the file with the given path
	inputLines.open(inputpath);

	//Testing if the path was invalid
	while (!inputLines.is_open()) {
		cout << "Nome do ficheiro inválido!" << endl;
		cout << "Insira o nome do ficheiro a usar para as linhas: (exemplo: \"linhas_test.txt\")" << endl;
		getline(cin, inputpath);
		inputLines.open(inputpath);
	}

	//Success
	cout << "\nFicheiro de linhas aberto com sucesso!\n\n\n";

	//Passing the contents of the text files to a string vector where each index is a line in the file
	vector<string> RawDrivers = Utilities::ReadFile(inputDrivers);
	vector<string> RawLines = Utilities::ReadFile(inputLines);

	//Closing ifstreams
	inputDrivers.close();
	inputLines.close();

	//Debugging printing raw file vector
	/*
	cout << "Conteúdo do ficheiro dos condutores:" << endl;
	Utilities::printVector(RawDrivers);
	cout << "Conteúdo do ficheiro das linhas:" << endl;
	Utilities::printVector(RawLines);
	*/

	//Populating data structures

	//Populating drivers vector
	for (int i = 0; i < RawDrivers.size(); i++) {
		drivers.push_back(createDriverFromString(RawDrivers[i]));
	}

	/*
	//Debug testing if drivers populated correctly
	cout << "Finished populating drivers, now printing" << endl;
	for (int i = 0; i < drivers.size(); i++) {
		cout << "ID: " << drivers[i].ID << "\tName: " << drivers[i].name;
		cout << "\tShift size: " << drivers[i].shiftsize << "\tWeekly hour limit: " << drivers[i].weeklyhourlimit;
		cout << "\tMin rest time: " << drivers[i].minresttime << endl;
	}
	*/

	//Populating lines vector ( TODO )
	for (int i = 0; i < RawLines.size(); i++) {
		lines.push_back(createLineFromString(RawLines[i]));
	}

	/*
	//Debug testing if lines populated correctly
	cout << "Finished populating lines, now printing" << endl;
	for (int i = 0; i < lines.size(); i++) {
		cout << "ID: " << lines[i].ID << "\tFrequency: " << lines[i].frequency;
		cout << "Stops for this line:\n";
		Utilities::printVector(lines[i].stops);
		cout << "Delays between these stops:\n";
		Utilities::printVector(lines[i].delaybetweenstops);
	}
	*/

	//Sorting drivers into lines
	
}

BusManager::~BusManager() {

}

BusManager::driver BusManager::createDriverFromString(string rawline) {
	driver newDriver;

	//Splitting the information by ";" - which is the information splitter
	vector<string> info = Utilities::splitString(rawline, ";");

	//Trimming the info to remove excess spaces
	for (int i = 0; i < info.size(); i++) {
		Utilities::trimString(info[i]);
	}

	//vector organization
	// 0 - ID
	// 1 - Name
	// 2 - Shift size
	// 3 - Weekly hour limit
	// 4 - Minimum rest time between shifts

	int ID = stoi(info[0]);
	string name = info[1]; //the driver's name
	int shiftsize = stoi(info[2]); //shift size - number of hours the driver can work per day
	int weeklyhourlimit = stoi(info[3]); //number of hours the driver can work per day
	int minresttime = stoi(info[4]); //minimum rest time between shifts (hours)

	//Assigning values to driver
	newDriver.ID = ID;
	newDriver.name = name;
	newDriver.shiftsize = shiftsize;
	newDriver.weeklyhourlimit = weeklyhourlimit;
	newDriver.minresttime = minresttime;

	return newDriver;
}

BusManager::line BusManager::createLineFromString(string rawline) {
	line newLine;

	//Splitting the information by ";" - which is the information splitter
	vector<string> info = Utilities::splitString(rawline, ";");

	//Trimming the info to remove excess spaces
	for (int i = 0; i < info.size(); i++) {
		Utilities::trimString(info[i]);
	}

	//vector organization
	// 0 - ID
	// 1 - Frequency of bus stops for each stop in the line (minutes)
	// 2 - List of stop names
	// 3 - times (int minutes) of travel between stops

	int ID = stoi(info[0]); //line ID
	int frequency = stoi(info[1]); //frequency of buses in the line (minutes)
	vector<string> stops; //list of stop names
	vector<int> delaybetweenstops; //Times (in minutes) of travel between stops

	//Filling in the data vectors

	//Stops vector
	stops = Utilities::splitString(info[2], ","); //each stop is separated by a comma
	for (int i = 0; i < stops.size(); i++) {
		//Trimming the extra whitespace
		Utilities::trimString(stops[i]);
	}

	//Temporary string vector because we need the string to be trimmed to be able to "stoi" it
	vector<string> tempintodelays = Utilities::splitString(info[3], ",");
	for (int i = 0; i < tempintodelays.size(); i++) {
		//Trimming the string for stoi
		Utilities::trimString(tempintodelays[i]);
	}

	for (int i = 0; i < tempintodelays.size(); i++)	{
		//Filling in the delay vector with stoi
		delaybetweenstops.push_back(stoi(tempintodelays[i]));
	}

	//Assigning values to line
	newLine.ID = ID;
	newLine.frequency = frequency;
	newLine.stops = stops;
	newLine.delaybetweenstops = delaybetweenstops;

	return newLine;
}

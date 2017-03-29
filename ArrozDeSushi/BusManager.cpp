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

	//Debug testing if populated correctly
	cout << "Finished populating drivers, now printing" << endl;
	for (int i = 0; i < drivers.size(); i++) {
		cout << "ID: " << drivers[i].ID << "\tName: " << drivers[i].name;
		cout << "\tShift size: " << drivers[i].shiftsize << "\tWeekly hour limit: " << drivers[i].weeklyhourlimit;
		cout << "\tMin rest time: " << drivers[i].minresttime << endl;
	}

	//Populating lines vector ( TODO )

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

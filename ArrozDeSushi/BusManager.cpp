#include "BusManager.h"

BusManager::BusManager() {

}

BusManager::~BusManager() {

}

bool BusManager::createNewLine() {
	int newID;

	cout << "Introduza o ID da nova linha: ";

	while (true) {
		cin >> newID;
		if (cin.fail()) {
			cout << "ID inválido, por favor introduza um ID válido (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//If the given line ID results in a match from the line vector by searching by ID, then that line already exists
	//There are no duplicate IDs so we stop the line creation
	if (findLineByID(newID) != -1) {
		cout << "O ID dado já existe. Duas linhas diferentes não podem ter o mesmo ID.\nAbortando o processo de adição de linha..." << endl;
		cout << "Pressione enter para continuar...";
		cin.get();
		return false;
	}

	//Creating the line we will add
	line newLine;

	//Getting input from user about the line

	int frequency; //frequency of buses in the line (minutes)
	cout << "Qual a frequência de passagem de autocarros na linha (em minutos)?" << endl;
	while (true) {
		cin >> frequency;
		if (cin.fail()) {
			cout << "Frequência inválida, por favor introduza um número válido (inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	vector<string> stops; //list of stop names
	string rawstops;
	cout << "Qual a sequência de paragens da linha? (Introduzir os nomes separados por vírgulas, exemplo \"Paragem1, Paragem2, Paragem3\")" << endl;
	getline(cin, rawstops); //Receiving whole line and not only the text until the next space

	//the stops vector is populated by splitting the line when a ',' is found
	stops = Utilities::splitString(rawstops, ",");

	//trimmming unnecessary whitespace from the stop name
	for (int i = 0; i < stops.size(); i++) {
		Utilities::trimString(stops[i]);
	}

	vector<int> delaybetweenstops; //times (in minutes) of travel between stops
	int tempdelay; //Temporary variable to hold the input to later on push back
	cout << "Introduza os tempos de viagem entre as paragens (em minutos):";
	//We are going to go through the stops vector because the delaybetweenstops vector can only, at most, have its size-1
	//This loop is also useful to display the information request
	for (int i = 0; i < stops.size() - 1; i++) {
		cout << "Tempo " << i + 1 << " de " << stops.size() - 1 << ", qual o tempo de viagem entre " << stops[i] << " e " << stops[i + 1] << "?" << endl;
		while (true) {
			cin >> tempdelay;
			if (cin.fail()) {
				cout << "Tempo de viagem inválido, por favor introduza um número válido (inteiro)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}
		//when input is an int, input is successful and is now pushed back into the vector
		delaybetweenstops.push_back(tempdelay);
	}

	//Assingning values to the line
	newLine.ID = newID;
	newLine.frequency = frequency;
	newLine.stops = stops;
	newLine.delaybetweenstops;

	//Pushing the newly created line into the lines vector
	lines.push_back(newLine);

	//returning true since the line was successfully added
	return true;
}

bool BusManager::createNewDriver() {
	int newID;

	cout << "Introduza o ID do novo condutor: ";

	while (true) {
		cin >> newID;
		if (cin.fail()) {
			cout << "ID inválido, por favor introduza um ID válido (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//If the given driver ID results in a match from the drivers vector by searching by ID, then that driver already exists
	//There are no duplicate IDs so we stop the driver creation
	if (findDriverByID(newID) != -1) {
		cout << "O ID dado já existe. Dois condutores diferentes nï¿½o podem ter o mesmo ID.\nAbortando o processo de adição de condutor..." << endl;
		cout << "Pressione enter para continuar...";
		cin.get();
		return false;
	}

	//Creating the driver we will add
	driver newDriver;

	//Getting input from user about the driver

	string name; //the driver's name

	cout << "Qual o nome do condutor?" << endl;
	getline(cin, name); //using getline because the driver's name can have spaces
	Utilities::trimString(name); //trimming unnecessary whitespace from the driver name

	int shiftsize; //the size of the driver's shift - number of hours he can work per day
	cout << "Qual o número máximo de horas que o condutor pode trabalhar por dia?" << endl;

	while (true) {
		cin >> shiftsize;
		if (cin.fail()) {
			cout << "Tamanho de turno inválido, por favor introduza um tamanho válido em horas (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	int weeklyhourlimit; //number of hours the driver can work per day
	cout << "Qual o número máximo de horas que o condutor pode trabalhar por semana?" << endl;

	while (true) {
		cin >> weeklyhourlimit;
		if (cin.fail()) {
			cout << "Input inválido, por favor introduza um input válido em horas (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	int minresttime; //minimum rest time between shifts (hours)
	cout << "Qual o tempo mínimo de descanso entre turnos para o condutor?" << endl;

	while (true) {
		cin >> minresttime;
		if (cin.fail()) {
			cout << "Número de horas de descanso inválido, por favor introduza um input válido em horas (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Assigning values to driver
	newDriver.ID = newID;
	newDriver.name = name;
	newDriver.shiftsize = shiftsize;
	newDriver.weeklyhourlimit = weeklyhourlimit;
	newDriver.minresttime = minresttime;

	//Pushing the newly created driver into the drivers vector
	drivers.push_back(newDriver);

	//returning true since the driver was successfully added
	return true;
}

bool BusManager::deleteLine() {
	int IDtodel;
	cout << "Qual o ID da linha a apagar?" << endl;
	while (true) {
		cin >> IDtodel;
		if (cin.fail()) {
			cout << "ID inválido, por favor introduza um ID válido (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Finding the position of the line in the lines vector
	int foundpos = findLineByID(IDtodel);
	//If foundpos is -1 it is because the given ID did not match any stored line
	if (foundpos == -1) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de eliminação de linha..." << endl;
		cout << "Pressione enter para continuar...";
		cin.get();
		return false; //returning false since the process was not concluded successfully
	}

	cout << "Linha encontrada, eliminando..." << endl;
	lines.erase(lines.begin() + IDtodel); //deleting the position of the vector results in deleting the line

	//process was concluded successfully, returning true
	return true;
}

bool BusManager::deleteDriver() {
	int IDtodel;
	cout << "Qual o ID do condutor a apagar?" << endl;
	while (true) {
		cin >> IDtodel;
		if (cin.fail()) {
			cout << "ID inválido, por favor introduza um ID válido (número inteiro)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Finding the position of the driver in the drivers vector
	int foundpos = findDriverByID(IDtodel);
	//If foundpos is -1 it is because the given ID did not match any stored driver
	if (foundpos == -1) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de eliminação de condutor..." << endl;
		cout << "Pressione enter para continuar...";
		cin.get();
		return false; //returning false since the process was not concluded successfully
	}

	cout << "Condutor encontrado, eliminando..." << endl;
	drivers.erase(drivers.begin() + IDtodel); //deleting the position of the vector results in deleting the line

	//process was concluded successfully, returning true
	return true;
}

void BusManager::displayDrivers() {
	for (int i = 0; i < drivers.size(); i++) {
		cout << "ID: " << drivers[i].ID << " Nome: " << drivers[i].name << endl;
	}
}

void BusManager::displayDrivers(bool available) {
	//WIP
}

void BusManager::displayLines() {
	for (int i = 0; i < lines.size(); i++) {
		cout << "ID: " << lines[i].ID << " Primeira e última paragem: ";
		cout << lines[i].stops.at(0) << " ... " << lines[i].stops.at(lines[i].stops.size());
		cout << endl;
	}
}

bool BusManager::Load() {

	//Internal data is reset. For the first load this does nothing but for the next ones this will clear internal data
	Reset();

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
		cout << "(Ctrl+Z para abortar o processo)" << endl;
		cout << ">> ";
		getline(cin, inputpath);
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
			/*cout << "Pressione enter para continuar..." << endl; //Pause is in main
			cin.get();*/
			return false;
		}
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
		cout << "(Ctrl+Z para abortar o processo)" << endl;
		cout << ">> ";
		getline(cin, inputpath);
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
			cout << "Pressione enter para continuar..." << endl;
			cin.get();
			return false;
		}
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
	//sortData();
	//distributeDrivers();
	//etc

	//After everything was successful
	return true;
}

void BusManager::Reset() {
	//Deleting drivers
	drivers.erase(drivers.begin(), drivers.end());
	//Deleting lines
	lines.erase(lines.begin(), lines.end());

	//If more internal data is added, update this
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
	// 3 - Times (in minutes) of travel between stops

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

	for (int i = 0; i < tempintodelays.size(); i++) {
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

int BusManager::findLineByID(int lineID) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].ID == lineID) {
			return i;
		}
	}

	return -1;
}

int BusManager::findDriverByID(int driverID) {
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i].ID == driverID) {
			return i;
		}
	}

	return -1;
}

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
		return false;
	}

	//Creating the line we will add
	line newLine;

	//Getting input from user about the line

	int frequency; //frequency of buses in the line (minutes)
	cout << "Qual a frequência de passagem de autocarros na linha (em minutos)? ";
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
	//With the testing done, this is needed if we are to use getline after using cin as a stream
	cin.ignore(10000, '\n');
	getline(cin, rawstops); //Receiving whole line and not only the text until the next space

	//the stops vector is populated by splitting the line when a ',' is found
	stops = Utilities::splitString(rawstops, ",");

	//trimmming unnecessary whitespace from the stop name
	for (int i = 0; i < stops.size(); i++) {
		Utilities::trimString(stops[i]);
	}

	vector<int> delaybetweenstops; //times (in minutes) of travel between stops
	int tempdelay; //Temporary variable to hold the input to later on push back
	cout << "Introduza os tempos de viagem entre as paragens (em minutos):" << endl;
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
		cout << "O ID dado já existe. Dois condutores diferentes não podem ter o mesmo ID.\nAbortando o processo de adição de condutor..." << endl;
		return false;
	}

	//Creating the driver we will add
	driver newDriver;

	//Getting input from user about the driver

	string name; //the driver's name

	cout << "Qual o nome do condutor?" << endl;
	//With the testing done, this is needed if we are to use getline after using cin as a stream
	cin.ignore(10000, '\n');
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

bool BusManager::modifyLine() {
	int IDtomodify;

	cout << "Qual o ID da linha a alterar? ";
	while (true) {
		cin >> IDtomodify;
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
	int foundpos = findLineByID(IDtomodify);
	//If foundpos is -1 it is because the given ID did not match any stored line
	if (foundpos == -1) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de modificação de linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Clearing screen
	Utilities::clearScreen();

	cout << "Linha encontrada." << endl;
	cout << "Qual das informações da linha quer alterar? (Ctrl + Z para abortar o processo)" << endl;

	unsigned int choice = 0; //holds the user selection of the attribute to modify

	cout << "1 - Frequência de passagem de autocarros na linha\n";
	cout << "2 - Lista de paragens\n";
	cout << "3 - Lista de tempos de viagem entre paragens\n";
	cout << ">> ";

	//This also has to be outside the loop to make sure that the check is ran before the function crashes
	if (cin.eof()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "EOF detetado, abortando processo de modificação de linha..." << endl;
		return false;
	}

	//Ask for choice again if it was invalid
	while (true) {
		cin >> choice;
		if (choice >= 1 && choice <= 3) {
			//if the choice is between 1 and 3 the input is valid so the loop is exited
			break;
		}
		else {
			//Clearing screen before re-printing
			Utilities::clearScreen();
			cout << "Escolha inválida, por favor introduza uma opção válida (número inteiro entre 1 e 3)." << endl;
			cout << "Qual das informações da linha quer alterar? (Ctrl + Z para abortar o processo)" << endl;
			cout << "1 - Frequência de passagem de autocarros na linha\n";
			cout << "2 - Lista de paragens\n";
			cout << "3 - Lista de tempos de viagem entre paragens\n";
			cout << ">> ";
			//Clearing error flag and cin buffer in case that this was due to cin.fail() - if it wasn't this has no effect so there is no problem in doing it like this
			cin.clear();
			cin.ignore(100000, '\n');
		}
	}

	//Calling modifier function based on choice
	modifyLine(choice, foundpos);

	//process was concluded successfully, returning true
	return true;
}

bool BusManager::modifyLine(unsigned int choice, int pos) {

	switch (choice) {
	case 1:
	{
		//Changing bus frequency
		unsigned int newFreq;
		cout << "Qual a nova frequência de passagem de autocarros nas linhas (em minutos)? ";
		while (true) {
			cin >> newFreq;
			if (cin.fail()) {
				cout << "Frequência inválida, por favor introduza um número válido (inteiro positivo)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}
		//Changing frequency
		lines[pos].frequency = newFreq;
		break;
	}
	case 2:
	{
		//Changing the list of stops - only altering one stop at a time because otherwise the delay vector is no longer correct relative to the stops
		unsigned int posToChange;
		string newStopName = "";

		cout << "Qual a paragem a alterar?" << endl;
		//Printing options
		Utilities::printVector(lines[pos].stops);
		cout << ">> ";
		while (true) {
			cin >> posToChange;
			if (cin.fail() || posToChange >= lines[pos].stops.size()) {
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
				//Clearing screen and reprinting with warning
				Utilities::clearScreen();
				cout << "Opção inválida, por favor introduza um número válido (inteiro positivo menor que " << lines[pos].stops.size() - 1 << ")." << endl;
				cout << "Qual a paragem a alterar?" << endl;
				//Printing options
				Utilities::printVector(lines[pos].stops);
				cout << ">> ";
			}
			else {
				//if cin didn't fail and the input is a good position we have a good input so we break the loop
				break;
			}
		}

		//Now asking for the new name
		cout << "Qual o novo nome para a paragem a alterar?" << endl;
		cout << ">> ";
		//With the testing done, this is needed if we are to use getline after using cin as a stream
		cin.ignore(10000, '\n');
		getline(cin, newStopName); //using getline instead of cin because a stop name can have spaces
		Utilities::trimString(newStopName); //trimming unnecessary whitespace

		//Changing the stop name
		lines[pos].stops[posToChange] = newStopName;
		break;
	}
	case 3:
	{
		//Changing the list of travel delays - only altering one delay at a time because otherwise the delay vector is no longer correct relative to the stops
		unsigned int posToChange;
		unsigned int newDelay = 0;

		cout << "Qual o tempo de viagem a alterar?" << endl;
		//Printing options
		for (int i = 0; i < lines[pos].stops.size() - 1; i++) {
			cout << i << ": " << "Tempo de viagem entre " << lines[pos].stops[i] << " e " << lines[pos].stops[i + 1] << ": " << lines[pos].delaybetweenstops[i] << " minutos." << endl;
		}
		cout << ">> ";

		while (true) {
			cin >> posToChange;
			if (cin.fail() || posToChange >= lines[pos].delaybetweenstops.size()) {
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
				//Clearing screen and reprinting with warning
				Utilities::clearScreen();
				cout << "Opção inválida, por favor introduza um número válido (inteiro positivo menor que " << lines[pos].delaybetweenstops.size() - 1 << ")." << endl;
				cout << "Qual o tempo de viagem a alterar?" << endl;
				//Printing options
				for (int i = 0; i < lines[pos].stops.size() - 1; i++) {
					cout << i << ": " << "Tempo de viagem entre " << lines[pos].stops[i] << " e " << lines[pos].stops[i + 1] << ": " << lines[pos].delaybetweenstops[i] << " minutos." << endl;
				}
				cout << ">> ";
			}
			else {
				//if cin didn't fail and the input is a good position we have a good input so we break the loop
				break;
			}
		}

		//Now asking for the new delay
		cout << "Qual o novo tempo de viagem (em minutos)? ";
		while (true) {
			cin >> newDelay;
			if (cin.fail()) {
				cout << "Tempo de viagem inválido, por favor introduza um tempo válido (número inteiro positivo)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		lines[pos].delaybetweenstops[posToChange] = newDelay;
		break;
	}
	default:
		//The choice should never be invalid but if it is return false (error has ocurred)
		return false;
		break;
	}

	return true;
}

bool BusManager::modifyDriver() {


	return true;
}

bool BusManager::deleteLine() {
	int IDtodel;

	cout << "Qual o ID da linha a apagar? ";
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
		return false; //returning false since the process was not concluded successfully
	}

	cout << "Linha encontrada, eliminando..." << endl;
	lines.erase(lines.begin() + foundpos); //deleting the position of the vector results in deleting the line

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
		return false; //returning false since the process was not concluded successfully
	}

	cout << "Condutor encontrado, eliminando..." << endl;
	drivers.erase(drivers.begin() + foundpos); //deleting the position of the vector results in deleting the line

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
		cout << lines[i].stops.at(0) << " ... " << lines[i].stops.at(lines[i].stops.size() - 1);
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
	cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
	cout << ">> ";
	//Using getline because the path can contain spaces
	getline(cin, inputpath);

	//This also has to be outside the loop to make sure that the check is ran before the function crashes
	//It seems to not be possible to avoid having to press enter twice for this to work, must be because getline needs an enter and then cin.eof wants cin to be populated and so requires another enter
	if (cin.eof()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
		return false;
	}

	//Opening the file with the given path
	inputDrivers.open(inputpath);

	//Testing if the path was invalid
	while (!inputDrivers.is_open()) {
		//Clears screen before re-writing
		Utilities::clearScreen();
		cout << "Nome do ficheiro inválido!" << endl;
		cout << "Insira o nome do ficheiro a usar para os condutores: (exemplo: \"condutores_test.txt\")" << endl;
		cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
		cout << ">> ";
		getline(cin, inputpath);
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
			return false;
		}
		else
			inputDrivers.open(inputpath);
	}

	//Success
	cout << "\nFicheiro de condutores aberto com sucesso!\n\n\n";

	//Lines file input - same idea as above
	cout << "Insira o nome do ficheiro a usar para as linhas: (exemplo: \"linhas_test.txt\")" << endl;
	cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
	cout << ">> ";
	//Using getline because the path can contain spaces
	getline(cin, inputpath);

	//This also has to be outside the loop to make sure that the check is ran before the function crashes
	if (cin.eof()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
		return false;
	}


	//Opening the file with the given path
	inputLines.open(inputpath);

	//Testing if the path was invalid
	while (!inputLines.is_open()) {
		//Clears screen before re-writing
		Utilities::clearScreen();
		cout << "Nome do ficheiro inválido!" << endl;
		cout << "Insira o nome do ficheiro a usar para as linhas: (exemplo: \"linhas_test.txt\")" << endl;
		cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
		cout << ">> ";
		getline(cin, inputpath);
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
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

bool BusManager::printDriver() {
	unsigned int IDtoprint = 0;

	cout << "Qual o ID do condutor a imprimir?" << endl;
	while (true) {
		cin >> IDtoprint;
		if (cin.fail()) {
			cout << "ID inválido, por favor introduza um ID válido (número inteiro positivo)." << endl;
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
	unsigned int foundpos = findDriverByID(IDtoprint);
	//If foundpos is -1 it is because the given ID did not match any stored driver
	if (foundpos == -1) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de impressão de informação detalhada de um condutor..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Driver found, printing detailed info
	cout << "\n";
	printDriver(foundpos);

	//Process concluded successfully
	return true;
}

void BusManager::printDriver(unsigned int pos) {

	cout << "ID: " << drivers[pos].ID << "\nNome: " << drivers[pos].name;
	cout << "\nTamanho de turno: " << drivers[pos].shiftsize << "\nLimite de horas de trabalho semanal: " << drivers[pos].weeklyhourlimit;
	cout << "\nTempo mínimo de descanso: " << drivers[pos].minresttime << endl;

}

void BusManager::printLine(unsigned int pos) {

	cout << "ID: " << lines[pos].ID << "\nFrequência de passagem de autocarros: " << lines[pos].frequency;
	cout << "Paragens desta linha:\n";
	Utilities::printVector(lines[pos].stops);
	cout << "Tempos de viagem entre estas paragens:\n";
	Utilities::printVector(lines[pos].delaybetweenstops);

}

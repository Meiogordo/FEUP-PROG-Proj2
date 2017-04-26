#include "BusBoss.h"

BusBoss::BusBoss() {

}

BusBoss::~BusBoss() {

}

bool BusBoss::createNewLine() {
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

	//Checking if a line with the given ID already exists (number of elements bigger than 0)
	//Because we are using a map .count will always be either 0 or 1
	bool lineExists = (lines.count(newID) > 0);

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

	//Creating the line we will add
	Line newLine(newID, frequency, stops, delaybetweenstops);

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//returning true since the line was successfully added
	return true;
}

bool BusBoss::createNewDriver() {
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
	//Data not gotten from string from user input
	newDriver.shifts = vector<shift>(); //Empty vector of shifts
	newDriver.available = true; //All drivers are available at first

								//Pushing the newly created driver into the drivers vector
	drivers.push_back(newDriver);

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//returning true since the driver was successfully added
	return true;
}

bool BusBoss::modifyLine() {
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
			if (cin.eof()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "EOF detetado, abortando processo de modificação de linha..." << endl;
				return false;
			}
			else {
				//Due to choice out of bounds or cin.fail()

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
	}

	//Calling modifier function based on choice
	modifyLine(choice, foundpos);

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//process was concluded successfully, returning true
	return true;
}

bool BusBoss::modifyLine(unsigned int choice, int pos) {

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

bool BusBoss::modifyDriver() {
	int IDtomodify;

	cout << "Qual o ID do condutor a alterar? ";
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

	//Finding the position of the driver in the drivers vector
	int foundpos = findDriverByID(IDtomodify);
	//If foundpos is -1 it is because the given ID did not match any stored driver
	if (foundpos == -1) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de modificação de condutor..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Clearing screen
	Utilities::clearScreen();

	cout << "Condutor encontrado." << endl;
	cout << "Qual das informações do condutor quer alterar? (Ctrl + Z para abortar o processo)" << endl;

	unsigned int choice = 0; //holds the user selection of the attribute to modify

	cout << "1 - Nome\n";
	cout << "2 - Tamanho de turno em horas\n";
	cout << "3 - Limite de horas de trabalho semanal\n";
	cout << "4 - Tempo mínimo de descanso entre turnos\n";
	cout << ">> ";

	//This also has to be outside the loop to make sure that the check is ran before the function crashes
	if (cin.eof()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "EOF detetado, abortando processo de modificação de condutor..." << endl;
		return false;
	}

	//Ask for choice again if it was invalid
	while (true) {
		cin >> choice;
		if (choice >= 1 && choice <= 4) {
			//if the choice is between 1 and 4 the input is valid so the loop is exited
			break;
		}
		else {
			if (cin.eof()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "EOF detetado, abortando processo de modificação de linha..." << endl;
				return false;
			}
			else {
				//Due to choice out of bounds or cin.fail()

				//Clearing screen before re-printing
				Utilities::clearScreen();
				cout << "Escolha inválida, por favor introduza uma opção válida (número inteiro entre 1 e 4)." << endl;
				cout << "Qual das informações do condutor quer alterar? (Ctrl + Z para abortar o processo)" << endl;
				cout << "1 - Nome\n";
				cout << "2 - Tamanho de turno em horas\n";
				cout << "3 - Limite de horas de trabalho semanal\n";
				cout << "4 - Tempo mínimo de descanso entre turnos\n";
				cout << ">> ";
				//Clearing error flag and cin buffer in case that this was due to cin.fail() - if it wasn't this has no effect so there is no problem in doing it like this
				cin.clear();
				cin.ignore(100000, '\n');
			}
		}
	}

	//Calling modifier function based on choice
	modifyDriver(choice, foundpos);

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//process was concluded successfully, returning true
	return true;
}

bool BusBoss::modifyDriver(unsigned int choice, int pos) {

	switch (choice) {
	case 1:
	{
		//Changing driver name
		string newName;
		cout << "Qual o novo nome do condutor? ";
		//With the testing done, this is needed if we are to use getline after using cin as a stream
		cin.ignore(10000, '\n');
		getline(cin, newName);

		//Changing name
		drivers[pos].name = newName;
		break;
	}
	case 2:
	{
		//Changing the shift size
		unsigned int newShiftSize;

		cout << "Qual o novo tamanho de turno (em horas)? ";
		while (true) {
			cin >> newShiftSize;
			if (cin.fail()) {
				cout << "Tamanho de turno inválido, por favor introduza um número válido (inteiro positivo)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		//Changing shiftsize
		drivers[pos].shiftsize = newShiftSize;
		break;
	}
	case 3:
	{
		//Changing the number of hours the driver can work per week
		unsigned int newWeeklyhourlimit;

		cout << "Qual o novo limite de horas de trabalho semanal? ";
		while (true) {
			cin >> newWeeklyhourlimit;
			if (cin.fail()) {
				cout << "Limite inválido, por favor introduza um número válido (inteiro positivo)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		//Changing weeklyhourlimit
		drivers[pos].weeklyhourlimit = newWeeklyhourlimit;
		break;
	}
	case 4:
	{
		//Changing the minimum rest time between shifts (hours)
		unsigned int newMinresttime;

		cout << "Qual o novo tempo mínimo de descanso entre turnos? ";
		while (true) {
			cin >> newMinresttime;
			if (cin.fail()) {
				cout << "Tempo inválido, por favor introduza um número válido (inteiro positivo)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		//Changing shiftsize
		drivers[pos].minresttime = newMinresttime;
		break;
	}
	default:
		//The choice should never be invalid but if it is return false (error has ocurred)
		return false;
		break;
	}

	return true;
}

bool BusBoss::deleteLine() {
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

										   //Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//process was concluded successfully, returning true
	return true;
}

bool BusBoss::deleteDriver() {
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

											   //Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//process was concluded successfully, returning true
	return true;
}

void BusBoss::displayDrivers() {
	for (int i = 0; i < drivers.size(); i++) {
		cout << "ID: " << drivers[i].ID << " Nome: " << drivers[i].name << endl;
	}
}

void BusBoss::displayDrivers(bool availability) {
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i].available == availability) //If the driver has the same availability as the one given as parameters, print him
			cout << "ID: " << drivers[i].ID << " Nome: " << drivers[i].name << endl;
	}
}

void BusBoss::displayLines() {
	for (int i = 0; i < lines.size(); i++) {
		cout << "ID: " << lines[i].ID << " Primeira e última paragem: ";
		cout << lines[i].stops.at(0) << " ... " << lines[i].stops.at(lines[i].stops.size() - 1);
		cout << endl;
	}
}

bool BusBoss::printDriver() {
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

bool BusBoss::printLine() {
	unsigned int IDtoprint = 0;

	cout << "Qual o ID da linha a imprimir?" << endl;
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
	unsigned int foundpos = findLineByID(IDtoprint);
	//If foundpos is -1 it is because the given ID did not match any stored driver
	if (foundpos == -1) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão de informação detalhada de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Driver found, printing detailed info
	cout << "\n";
	printLine(foundpos);

	//Process concluded successfully
	return true;
}

bool BusBoss::printDriverShifts() {
	unsigned int IDtoprint = 0;

	cout << "Qual o ID do condutor para o qual se irá imprimir o trabalho atribuído?" << endl;
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

	//Driver found, printing shifts
	cout << "\n";
	if (drivers[foundpos].shifts.empty()) {
		cout << "O condutor em questão não tem trabalho atribuído." << endl;
		return true;
	}
	else {
		cout << "O condutor tem " << drivers[foundpos].shifts.size() << " turnos atribuídos." << endl;
		for (int i = 0; i < drivers[foundpos].shifts.size(); i++) {
			cout << "O turno nº " << i << " decorrerá ao " << weekdays.at(drivers[foundpos].shifts[i].weekday);
			cout << " começará às " << setw(2) << drivers[foundpos].shifts[i].startHour << ":" << setw(2) << drivers[foundpos].shifts[i].startMinute;
			cout << " e terminará às " << setw(2) << drivers[foundpos].shifts[i].endHour << ":" << setw(2) << drivers[foundpos].shifts[i].endMinute;
			cout << ", sendo que o condutor irá trabalhar na linha " << drivers[foundpos].shifts[i].lineID << "." << endl;
		}
	}

	//Process concluded successfully
	return true;
}

void BusBoss::printDriver(unsigned int pos) {

	cout << "ID: " << drivers[pos].ID << "\nNome: " << drivers[pos].name;
	cout << "\nTamanho de turno: " << drivers[pos].shiftsize << "\nLimite de horas de trabalho semanal: " << drivers[pos].weeklyhourlimit;
	cout << "\nTempo mínimo de descanso: " << drivers[pos].minresttime << endl;

}

void BusBoss::printLine(unsigned int pos) {

	cout << "ID: " << lines[pos].ID << "\nFrequência de passagem de autocarros: " << lines[pos].frequency;
	cout << "\nParagens desta linha:\n";
	Utilities::printVector(lines[pos].stops);
	cout << "Tempos de viagem entre estas paragens:\n";
	Utilities::printVector(lines[pos].delaybetweenstops);

}

bool BusBoss::Load() {

	//Check to see if the user has unsaved changes before loading a new file
	if (getIfHasUnsavedChanges()) {
		string option;
		cout << "Tem alterações não gravadas, deseja prosseguir com o carregamento de um novo ficheiro? (S/N)" << endl;
		cout << ">> ";
		while (true) {
			cin >> option;
			if (cin.fail() || (option != "S" && option != "N")) {
				//Clearing error flags and buffer
				cin.clear();
				cin.ignore(10000, '\n');
				//Clearing screen to display input prompt again
				cout << "Opção inválida." << endl;
				cout << "Tem alterações não gravadas, deseja prosseguir com o carregamento de um novo ficheiro? (S/N)" << endl;
				cout << ">> ";
			}
			else {
				//input is valid so we break the loop
				break;
			}
		}

		//If the user specifies that he does not want to continue because he has unsaved progress we quit the file loading
		if (option == "N") {
			cout << "Abortando processo de carregamento de ficheiros..." << endl;
			return false;
		}
		else {
			//Otherwise, the user specified that he does want to continue so we simply clear the screen to make space for the following output
			Utilities::clearScreen();
		}
	}

	ifstream inputDrivers, inputLines;
	//string for the path for the drivers and lines files. Separate variables are used to be able to save the path to internal variables if the process is not aborted
	string  inputpathDrivers = "", inputpathLines = "";

	//Clearing the cin stream - might get unwanted input in if not cleared before using getline
	//If there are more than 0 characters in the cin buffer, clear them, otherwise getline will get that input
	if (cin.rdbuf()->in_avail() > 0) {
		cin.ignore(10000, '\n');
	}

	//Drivers file input
	cout << "Insira o nome do ficheiro a usar para os condutores: (exemplo: \"condutores_test.txt\")" << endl;
	cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
	cout << ">> ";
	//Using getline because the path can contain spaces
	getline(cin, inputpathDrivers);

	//This also has to be outside the loop to make sure that the check is ran before the function crashes
	//It seems to not be possible to avoid having to press enter twice for this to work, must be because getline needs an enter and then cin.eof wants cin to be populated and so requires another enter
	if (cin.eof()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
		return false;
	}

	//Opening the file with the given path
	inputDrivers.open(inputpathDrivers);

	//Testing if the path was invalid
	while (!inputDrivers.is_open()) {
		//Clears screen before re-writing
		Utilities::clearScreen();
		cout << "Nome do ficheiro inválido!" << endl;
		cout << "Insira o nome do ficheiro a usar para os condutores: (exemplo: \"condutores_test.txt\")" << endl;
		cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
		cout << ">> ";
		getline(cin, inputpathDrivers);
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
			return false;
		}
		else
			inputDrivers.open(inputpathDrivers);
	}

	//Success
	cout << "\nFicheiro de condutores aberto com sucesso!\n\n\n";

	//Lines file input - same idea as above
	cout << "Insira o nome do ficheiro a usar para as linhas: (exemplo: \"linhas_test.txt\")" << endl;
	cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
	cout << ">> ";
	//Using getline because the path can contain spaces
	getline(cin, inputpathLines);

	//This also has to be outside the loop to make sure that the check is ran before the function crashes
	if (cin.eof()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
		return false;
	}


	//Opening the file with the given path
	inputLines.open(inputpathLines);

	//Testing if the path was invalid
	while (!inputLines.is_open()) {
		//Clears screen before re-writing
		Utilities::clearScreen();
		cout << "Nome do ficheiro inválido!" << endl;
		cout << "Insira o nome do ficheiro a usar para as linhas: (exemplo: \"linhas_test.txt\")" << endl;
		cout << "(Ctrl+Z para abortar o processo - a informação interna estará vazia e a maior parte das funcionalidades não irão funcionar corretamente)" << endl;
		cout << ">> ";
		getline(cin, inputpathLines);
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de criação de gestor de empresa de autocarros..." << endl;
			return false;
		}
		inputLines.open(inputpathLines);
	}

	//Success
	cout << "\nFicheiro de linhas aberto com sucesso!\n\n\n";

	//Both files were opened successfully, resetting internal data to replace it with new one:
	//Internal data is reset. For the first load this does nothing but for the next ones this will clear internal data (drivers, lines, etc)
	Reset();

	//From now on the files are loaded into memory so it is safe to save the path from which they were gotten
	driversFilePath = inputpathDrivers;
	linesFilePath = inputpathLines;
	//The save is only done now because if the process was aborted before this the internal memory would be unchanged and thus still linked to the file that was opened before

	//Updating hasUnsavedChanges - if we are loading from a file we do not have unsaved changes
	hasUnsavedChanges = false;

	//Passing the contents of the text files to a string vector where each index is a line in the file
	vector<string> RawDrivers = Utilities::ReadFile(inputDrivers);
	vector<string> RawLines = Utilities::ReadFile(inputLines);

	//Closing ifstreams
	inputDrivers.close();
	inputLines.close();

	//Populating data structures

	//Populating drivers vector
	for (int i = 0; i < RawDrivers.size(); i++) {
		drivers.push_back(createDriverFromString(RawDrivers[i]));
	}

	//Populating lines vector
	for (int i = 0; i < RawLines.size(); i++) {
		lines.push_back(createLineFromString(RawLines[i]));
	}

	//Sorting drivers into lines
	//sortData();
	//distributeDrivers();
	//etc

	//After everything was successful
	return true;
}

bool BusBoss::Save() {
	//File output streams
	ofstream outputDrivers, outputLines;

	//temporary variables for file path in case the internal variables do not work - they start as the internal paths because if the paths open straight away they are not changed so the internal vars are not reset accidentally
	string tempLinesFilePath = linesFilePath, tempDriversFilePath = driversFilePath;

	//Attempting to open files
	outputDrivers.open(driversFilePath);
	outputLines.open(linesFilePath);

	if (!outputDrivers.is_open()) {

		//Clearing the cin stream - might get unwanted input in if not cleared before using getline
		//If there are more than 0 characters in the cin buffer, clear them, otherwise getline will get that input
		if (cin.rdbuf()->in_avail() > 0) {
			cin.ignore(10000, '\n');
		}

		cout << "Ainda não foi carregada informação de um ficheiro de condutores ou o ficheiro já não existe." << endl;
		cout << "Por favor introduza o nome do ficheiro a usar para guardar os condutores: (exemplo: \"condutores_test.txt\")" << endl;
		cout << "(Ctrl+Z para abortar o processo - a informação interna não será gravada)" << endl;
		cout << ">> ";

		//Using getline because the path can contain spaces
		getline(cin, tempDriversFilePath);

		//This also has to be outside the loop to make sure that the check is ran before the function crashes
		//It seems to not be possible to avoid having to press enter twice for this to work, must be because getline needs an enter and then cin.eof wants cin to be populated and so requires another enter
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de gravação de ficheiros..." << endl;
			return false;
		}

		//Opening the file with the given path
		outputDrivers.open(tempDriversFilePath);

		//Testing if the path was invalid
		while (!outputDrivers.is_open()) {
			//Clears screen before re-writing
			Utilities::clearScreen();
			cout << "Nome do ficheiro inválido!" << endl;
			cout << "Por favor introduza o nome do ficheiro a usar para guardar os condutores: (exemplo: \"condutores_test.txt\")" << endl;
			cout << "(Ctrl+Z para abortar o processo - a informação interna não será gravada)" << endl;
			cout << ">> ";
			getline(cin, tempDriversFilePath);
			if (cin.eof()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "EOF detetado, abortando processo de gravação de ficheiros..." << endl;
				return false;
			}
			else
				outputDrivers.open(tempDriversFilePath);
		}
	}

	//outputDrivers is ready

	if (!outputLines.is_open()) {
		cout << "Ainda não foi carregada informação de um ficheiro de linhas ou o ficheiro já não existe." << endl;
		cout << "Por favor introduza o nome do ficheiro a usar para guardar os linhas: (exemplo: \"linhas_test.txt\")" << endl;
		cout << "(Ctrl+Z para abortar o processo - a informação interna não será gravada)" << endl;
		cout << ">> ";

		//Using getline because the path can contain spaces
		getline(cin, tempLinesFilePath);

		//This also has to be outside the loop to make sure that the check is ran before the function crashes
		//It seems to not be possible to avoid having to press enter twice for this to work, must be because getline needs an enter and then cin.eof wants cin to be populated and so requires another enter
		if (cin.eof()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "EOF detetado, abortando processo de gravação de ficheiros..." << endl;
			return false;
		}

		//Opening the file with the given path
		outputLines.open(tempLinesFilePath);

		//Testing if the path was invalid
		while (!outputLines.is_open()) {
			//Clears screen before re-writing
			Utilities::clearScreen();
			cout << "Nome do ficheiro inválido!" << endl;
			cout << "Por favor introduza o nome do ficheiro a usar para guardar os linhas: (exemplo: \"linhas_test.txt\")" << endl;
			cout << "(Ctrl+Z para abortar o processo - a informação interna não será gravada)" << endl;
			cout << ">> ";
			getline(cin, tempLinesFilePath);
			if (cin.eof()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "EOF detetado, abortando processo de gravação de ficheiros..." << endl;
				return false;
			}
			else
				outputLines.open(tempLinesFilePath);
		}
	}

	//outputLines is ready

	//From now on the process can't aborted so the internal file paths are updated with the new filepaths and hasUnsavedChanges is updated
	driversFilePath = tempDriversFilePath;
	linesFilePath = tempLinesFilePath;
	hasUnsavedChanges = false;

	//Calling save functions
	saveDriverstoFile(outputDrivers);
	saveLinestoFile(outputLines);

	//Function successful
	outputDrivers.close();
	outputLines.close();
	cout << "Ficheiros guardados com sucesso." << endl;
	return true;
}

void BusBoss::findLinesinStop() {
	string stopname;

	//Clearing the cin stream - might get unwanted input in if not cleared before using getline
	//If there are more than 0 characters in the cin buffer, clear them, otherwise getline will get that input
	if (cin.rdbuf()->in_avail() > 0) {
		cin.ignore(10000, '\n');
	}

	cout << "Qual a paragem que deseja procurar?" << endl;
	getline(cin, stopname); //getline is used because the stop name can have spaces in it

							//Searching for the stop in lines using findLinesinStop's overload
	vector<int> foundLines = findLinesinStop(stopname);

	//Outputting result based on foundLines being empty or not
	if (foundLines.empty()) {
		cout << "A paragem dada não pertence a nenhuma linha guardada." << endl;
	}
	else {
		cout << "A paragem dada pertence às seguintes linhas: ";
		cout << foundLines[0];
		for (int i = 1; i < foundLines.size(); i++) {
			cout << ", " << foundLines[i];
		}
		cout << endl;
	}
}

bool BusBoss::routeBetweenTwoStops() {
	//CASES:
	//0: One of them has no lines
	//1: No common lines - impossible with what we know at least for now
	//2: One common line - check best direction in the line
	//3: Several common lines - check best direction in each line.. 
	//Ideas - function to check best direction in line

	string stop1, stop2; //variables to hold stop names

						 //Clearing the cin stream - might get unwanted input in if not cleared before using getline
						 //If there are more than 0 characters in the cin buffer, clear them, otherwise getline will get that input
	if (cin.rdbuf()->in_avail() > 0) {
		cin.ignore(10000, '\n');
	}

	cout << "Qual a paragem de início do percurso?" << endl;
	getline(cin, stop1); //getline is used because the stop name can have spaces in it

						 //Checking to which lines stop1 belongs
	vector<int> foundLinesStop1 = findLinesinStop(stop1);

	//Case 0.1
	if (foundLinesStop1.empty()) {
		cout << "A primeira paragem não pertence a nenhuma das linhas guardadas.\nAbortando o processo de cálculo de percurso entre duas paragens..." << endl;
		return false;
	}

	cout << "Qual a paragem de final do percurso?" << endl;
	getline(cin, stop2); //getline is used because the stop name can have spaces in it

						 //Searching for the stop in lines using findLinesinStop
	vector<int> foundLinesStop2 = findLinesinStop(stop2);

	//Case 0.2
	if (foundLinesStop2.empty()) {
		cout << "A segunda paragem não pertence a nenhuma das linhas guardadas.\nAbortando o processo de cálculo de percurso entre duas paragens..." << endl;
		return false;
	}

	//Check lines in common between the two stops
	vector<int> intersection = Utilities::intersectVectors(foundLinesStop1, foundLinesStop2);

	//Case 1
	if (intersection.empty()) {
		cout << "As duas paragens dadas não têm nenhuma linha em comum.\nAbortando o processo de cálculo de percurso entre duas paragens..." << endl;
		return false;
	}

	//Case 2 & 3 - can be handled together due to how things were structured

	//Distances holds the distances in stops and best direction between stop1 and stop2 for each line in intersection
	vector<vector<int>> distances = calculateStopsForEachDirection(stop1, stop2, intersection);

	//Determining the smallest distance
	int smallestDistIndex = 0;
	for (int i = 0; i < distances.size(); i++) {
		//if the distance at this index is smaller then that is the new index for the smallest distance
		if (distances[i][1] < distances[smallestDistIndex][1])
			smallestDistIndex = i;
	}

	//Getting direction for the smallest distance
	int lineindex = findLineByID(intersection[smallestDistIndex]); //finds the index of the line that allows for the shortest route using findLineByID in the lines vector
	string direction;
	if (distances[smallestDistIndex][0] == 1) {
		//Positive direction - direction given by last stop in the stops vector
		direction = lines[lineindex].stops[lines[lineindex].stops.size() - 1];
	}
	else {
		//Negative direction - direction given by first stop in the stops vector
		direction = lines[lineindex].stops[0];
	}

	//The smallest distance was found
	cout << "Para percorrer o menor número de paragens entre " << stop1 << " e " << stop2 << ", deve-se apanhar a linha " << intersection[smallestDistIndex] << ", com direção a ";
	cout << direction << ", andando " << distances[smallestDistIndex][1] << " paragens.";
	cout << endl;

	//Process was successful
	return true;
}

bool BusBoss::getIfHasUnsavedChanges() {
	return hasUnsavedChanges;
}

bool BusBoss::showStopSchedule() {
	string stop;

	//Clearing the cin stream - might get unwanted input in if not cleared before using getline
	//If there are more than 0 characters in the cin buffer, clear them, otherwise getline will get that input
	if (cin.rdbuf()->in_avail() > 0) {
		cin.ignore(10000, '\n');
	}

	cout << "Qual a paragem cujo horário se irá imprimir?" << endl;
	getline(cin, stop); //getline is used because the stop name can have spaces in it

						//Checking to which lines the given stop belongs
	vector<int> foundLinesStop = findLinesinStop(stop);

	//Checking if the stop is in no line
	if (foundLinesStop.empty()) {
		cout << "A paragem dada não pertence a nenhuma das linhas guardadas.\nAbortando o processo de impressão de horário para uma paragem..." << endl;
		return false;
	}

	//Getting schedules for the stop given and all the lines it belongs to
	vector<schedule> schedules = generateStopSchedules(stop, foundLinesStop);


	//Variables for inside the loop (preventing redeclaring)
	string direction;
	string fulldirection;
	int spaces, spacesdiv4, middlespace, spacediff;

	cout << "\n\n\n";

	cout << "Horário na paragem " << stop << ":" << "\n\n";

	for (int i = 0; i < schedules.size(); i++) {

		//Positive direction - start to finish

		//If the schedule for this direction is empty it means that the stop is one of the endings in this certain line and thus it makes no sense to display the schedule
		//So, only display it if the schedule isn't empty

		if (!schedules[i].positiveBusTimes.empty()) {

			//Gets the last stop name for the direction
			direction = lines[findLineByID(schedules[i].lineID)].stops[lines[findLineByID(schedules[i].lineID)].stops.size() - 1];

			fulldirection = "Sentido em direção a " + direction;

			//Spacing definitions
			spaces = fulldirection.length();
			//Fixing the formatting because of uneven divisions
			spacesdiv4 = Utilities::roundToInt((double)spaces / 4);
			spacediff = Utilities::roundToInt((double)spacesdiv4 * 0.2);
			if (spaces % 2 == 0)
				middlespace = spacesdiv4 + 1;
			else
				middlespace = spacesdiv4 + 2;

			//Table formatting with |---|

			//Spacer header top
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;

			//Line and direction print
			cout << "|" << setfill(' ') << left << setw(spaces) << "Linha " + to_string(schedules[i].lineID) << "|" << endl;
			cout << "|" << setw(spaces) << fulldirection << "|" << endl;

			cout << right;

			//Spacer header bottom
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;


			//Times print
			for (int j = 0; j < schedules[i].positiveBusTimes.size() - 1; j += 2) {
				cout << setfill(' ') << "|" << setw(spacesdiv4 + spacediff) << schedules[i].positiveBusTimes[j]
					<< setw(middlespace - spacediff) << "!"
					<< setw(spacesdiv4 + spacediff) << schedules[i].positiveBusTimes[j + 1]
					<< setw(spacesdiv4 - spacediff) << "|" << endl;
			}

			//Space between directions
			cout << "\n";
		}

		//Negative direction - finish to start

		//If the schedule for this direction is empty it means that the stop is one of the endings in this certain line and thus it makes no sense to display the schedule
		//So, only display it if the schedule isn't empty

		if (!schedules[i].negativeBusTimes.empty()) {
			//Gets the first stop name for the direction
			direction = lines[findLineByID(schedules[i].lineID)].stops[0];

			fulldirection = "Sentido em direção a " + direction;

			//Spacing definitions
			spaces = fulldirection.length();
			//Fixing the formatting because of uneven divisions
			spacesdiv4 = Utilities::roundToInt((double)spaces / 4);
			spacediff = Utilities::roundToInt((double)spacesdiv4 * 0.2);
			if (spaces % 2 == 0)
				middlespace = spacesdiv4 + 1;
			else
				middlespace = spacesdiv4 + 2;

			//Table formatting with |---|

			//Spacer header top
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;

			//Line and direction print
			cout << "|" << setfill(' ') << left << setw(spaces) << "Linha " + to_string(schedules[i].lineID) << "|" << endl;
			cout << "|" << setw(spaces) << fulldirection << "|" << endl;

			cout << right;

			//Spacer header bottom
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;


			//Times print
			for (int j = 0; j < schedules[i].negativeBusTimes.size() - 1; j += 2) {
				cout << setfill(' ') << "|" << setw(spacesdiv4 + spacediff) << schedules[i].negativeBusTimes[j]
					<< setw(middlespace - spacediff) << "!"
					<< setw(spacesdiv4 + spacediff) << schedules[i].negativeBusTimes[j + 1]
					<< setw(spacesdiv4 - spacediff) << "|" << endl;
			}

			//Spacer between lines
			cout << "\n";
		}


	}

	return true;
}

bool BusBoss::showLineSchedule() {
	int lineIDtoprint;

	cout << "Qual o ID da linha cujo horário se irá imprimir? ";
	while (true) {
		cin >> lineIDtoprint;
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

	//Getting the index in the lines vector from the ID
	int lineIndex = findLineByID(lineIDtoprint);

	//If the result from findLineByID is -1 it is because the given ID did not match any stored line
	if (lineIndex == -1) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão do horário de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Getting schedules for each stop - each index will be the schedule for the stop in the same index as the stops vector
	vector<schedule> schedules;

	//Filling the schedules vector
	for (int i = 0; i < lines[lineIndex].stops.size(); i++) {
		schedules.push_back(generateStopSchedules(lines[lineIndex].stops[i], lineIDtoprint));
	}

	cout << "\n\n\n";

	//Printing schedules

	//Because this is always the same line, the directions are always the same
	string positivedirection = lines[lineIndex].stops[lines[lineIndex].stops.size() - 1]; //Last stop is the positive direction
	string negativedirection = lines[lineIndex].stops[0]; //First stop is the negative direction
	string positivefulldirection = "Sentido em direção a " + positivedirection;
	string negativefulldirection = "Sentido em direção a " + negativedirection;
	// to use inside the loop - preventing redeclaring
	int spaces;
	int spacesdiv4;
	int middlespace;
	int spacediff;

	cout << "Horário para a linha " << lineIDtoprint << ":" << "\n\n";

	for (int i = 0; i < schedules.size(); i++) {

		//Positive direction - start to finish

		//If the schedule for this direction is empty it means that the stop is one of the endings and thus it makes no sense to display the schedule
		//So, only display it if the schedule isn't empty

		if (!schedules[i].positiveBusTimes.empty()) {

			//Spacing definitions
			spaces = positivefulldirection.length();
			//Fixing the formatting because of uneven divisions
			spacesdiv4 = Utilities::roundToInt((double)spaces / 4);
			spacediff = Utilities::roundToInt((double)spacesdiv4 * 0.2);
			if (spaces % 2 == 0)
				middlespace = spacesdiv4 + 1;
			else
				middlespace = spacesdiv4 + 2;


			//Table formatting with |---|

			//Spacer header top
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;

			//Stop and direction print
			cout << "|" << setfill(' ') << left << setw(spaces) << "Paragem " + lines[lineIndex].stops[i] << "|" << endl;
			cout << "|" << setw(spaces) << positivefulldirection << "|" << endl;

			cout << right;

			//Spacer header bottom
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;

			//Times print
			for (int j = 0; j < schedules[i].positiveBusTimes.size() - 1; j += 2) {
				cout << setfill(' ') << "|" << setw(spacesdiv4 + spacediff) << schedules[i].positiveBusTimes[j]
					<< setw(middlespace - spacediff) << "!"
					<< setw(spacesdiv4 + spacediff) << schedules[i].positiveBusTimes[j + 1]
					<< setw(spacesdiv4 - spacediff) << "|" << endl;
			}

			//Space between directions
			cout << "\n";
		}

		//Negative direction - finish to start

		//If the schedule for this direction is empty it means that the stop is one of the endings and thus it makes no sense to display the schedule
		//So, only display it if the schedule isn't empty
		if (!schedules[i].negativeBusTimes.empty()) {

			//Spacing definitions
			spaces = negativefulldirection.length();
			//Fixing the formatting because of uneven divisions
			spacesdiv4 = Utilities::roundToInt((double)spaces / 4);
			spacediff = Utilities::roundToInt((double)spacesdiv4 * 0.2);
			if (spaces % 2 == 0)
				middlespace = spacesdiv4 + 1;
			else
				middlespace = spacesdiv4 + 2;

			//Table formatting with |---|

			//Spacer header top
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;

			//Line and direction print
			cout << "|" << setfill(' ') << left << setw(spaces) << "Paragem " + lines[lineIndex].stops[i] << "|" << endl;
			cout << "|" << setw(spaces) << negativefulldirection << "|" << endl;

			cout << right;

			//Spacer header bottom
			cout << "|" << setfill('-') << setw(spaces + 1) << "|" << endl;


			//Times print
			for (int j = 0; j < schedules[i].negativeBusTimes.size() - 1; j += 2) {
				cout << setfill(' ') << "|" << setw(spacesdiv4 + spacediff) << schedules[i].negativeBusTimes[j]
					<< setw(middlespace - spacediff) << "!"
					<< setw(spacesdiv4 + spacediff) << schedules[i].negativeBusTimes[j + 1]
					<< setw(spacesdiv4 - spacediff) << "|" << endl;
			}


			//Spacer between stops
			cout << "\n";
		}


	}

	return true;
}

bool BusBoss::getDriversNeeded() {
	unsigned int lineID = 0;

	cout << "Qual o ID da linha para a qual se irá calcular o número de condutores necessários? ";
	while (true) {
		cin >> lineID;
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

	//Getting the index in the lines vector from the ID
	int lineIndex = findLineByID(lineID);

	//If the result from findLineByID is -1 it is because the given ID did not match any stored line
	if (lineIndex == -1) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de cálculo do número de condutores necessários para uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	unsigned int drivershiftsize = 0;

	cout << "Qual o tamanho do turno dos condutores que irão trabalhar nesta linha (em horas)? ";
	while (true) {
		cin >> drivershiftsize;
		if (cin.fail()) {
			cout << "Tamanho de turno inválido, por favor introduza um tamanho de turno válido (número inteiro positivo)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Calculating the number of drivers
	int ndriversneeded = calculateDriversNeeded(lines[lineIndex].delaybetweenstops, lines[lineIndex].frequency, drivershiftsize);

	//Output
	cout << "\n\n";
	cout << "O número de condutores necessários para assegurar o serviço na linha " << lineID
		<< ", considerando condutores com turnos fixos de " << drivershiftsize << " horas é " << ndriversneeded << endl;

	return true;
}

void BusBoss::Reset() {
	//Deleting drivers
	drivers.erase(drivers.begin(), drivers.end());
	//Deleting lines
	lines.erase(lines.begin(), lines.end());

	//If more internal data is added, update this
}

BusBoss::driver BusBoss::createDriverFromString(string rawline) {
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
	int weeklyhourlimit = stoi(info[3]); //number of hours the driver can work per week
	int minresttime = stoi(info[4]); //minimum rest time between shifts (hours)

									 //Assigning values to driver
	newDriver.ID = ID;
	newDriver.name = name;
	newDriver.shiftsize = shiftsize;
	newDriver.weeklyhourlimit = weeklyhourlimit;
	newDriver.minresttime = minresttime;
	//Data not gotten from string from text file
	newDriver.shifts = vector<shift>(); //Empty vector of shifts
	newDriver.available = true; //All drivers are available at first

	return newDriver;
}

BusBoss::line BusBoss::createLineFromString(string rawline) {
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

int BusBoss::findLineByID(int lineID) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].ID == lineID) {
			return i;
		}
	}

	return -1;
}

int BusBoss::findDriverByID(int driverID) {
	for (int i = 0; i < drivers.size(); i++) {
		if (drivers[i].ID == driverID) {
			return i;
		}
	}

	return -1;
}

vector<int> BusBoss::findLinesinStop(string stopname) {
	vector<int> output;

	//outer loop goes through all the lines
	for (int i = 0; i < lines.size(); i++) {
		//inner loop goes through the list of stops for each line
		for (int j = 0; j < lines[i].stops.size(); j++) {
			if (lines[i].stops[j] == stopname) {
				//If the given stop is in the list of stops, the ID of the line is pushed back into the output and the inner loop is broken (a stop cannot appear two times in the same line)
				output.push_back(lines[i].ID);
				break;
			}
		}
	}

	//returning the matches found
	return output;
}

vector<BusBoss::schedule> BusBoss::generateStopSchedules(string stop, vector<int> lineIDs) {
	vector<schedule> output;

	for (int i = 0; i < lineIDs.size(); i++) {
		output.push_back(generateStopSchedules(stop, lineIDs[i]));
	}

	return output;
}

BusBoss::schedule BusBoss::generateStopSchedules(string stop, int lineID) {
	//Function note: to simplify the math here everything is done as minutes and in the end it is converted to strings

	schedule output;

	//Get access to line from the line id
	int lineIndex = findLineByID(lineID);

	//Store the frequency to not have to keep accessing array memory
	int frequency = lines[lineIndex].frequency;

	//Get start and end times in minutes
	unsigned int startTime = BUS_START_TIME_HOUR * 60 + BUS_START_TIME_MINUTE;
	unsigned int endTime = BUS_END_TIME_HOUR * 60 + BUS_END_TIME_MINUTE;

	//Get travel duration to the given stop from the start and from end
	unsigned int travelTimeFromStart = 0;
	for (int i = 0; i < lines[lineIndex].stops.size(); i++) {
		if (lines[lineIndex].stops[i] == stop) {
			//The stop was found
			break;
		}
		else {
			//Add travel time from this stop to the next one because this is not the one we want
			travelTimeFromStart += lines[lineIndex].delaybetweenstops[i];
			//There is no problem with getting out of bounds because at most the loop will break at stops.size which is one more than delaybetweenstops.size
		}
	}

	unsigned int travelTimeFromEnd = 0;
	for (int i = lines[lineIndex].stops.size() - 1; i >= 0; i--) {
		if (lines[lineIndex].stops[i] == stop) {
			//The stop was found
			break;
		}
		else {
			//Add travel time from this stop to the next one because this is not the one we want
			travelTimeFromEnd += lines[lineIndex].delaybetweenstops[i - 1]; //-1 because delays have 1 less index than stops
		}
	}

	//Complete travel time for the whole line - used to know if a bus will depart (has to arrive at one of the line endings before the endTime)
	unsigned int fullTravelTime = 0;

	for (int i = 0; i < lines[lineIndex].delaybetweenstops.size(); i++) {
		fullTravelTime += lines[lineIndex].delaybetweenstops[i];
	}

	//Times at which the buses start the line (direction does not matter for this because we are considering that buses depart from start and end simultaneously)
	vector<int> busDepartures;

	//Filling the vector 
	// Discarded: the stop condition is if the bus cannot make it to one of the endings of the line, he does not depart
	// Now using pure "if before the time of end of service" as a stop condition due to teacher suggestion
	for (int currentTime = startTime; currentTime < endTime; currentTime += frequency) {
		busDepartures.push_back(currentTime);
	}

	//Times at which the bus passes at the given stop
	vector<int> positiveBusPassagesAtStop; //In the positive direction (start to finish)
	vector<int> negativeBusPassagesAtStop; //In the negative direction (finish to start)

										   //Filling bus passages at the stop vector
	for (int i = 0; i < busDepartures.size(); i++) {
		positiveBusPassagesAtStop.push_back(busDepartures[i] + travelTimeFromStart);
		negativeBusPassagesAtStop.push_back(busDepartures[i] + travelTimeFromEnd);
	}

	//Setting output schedule values
	output.lineID = lineID;

	//Dealing with the stop being the end or the beginning of the line

	//If the stop is the end, it makes no sense to show the positive timetable

	if (stop == lines[lineIndex].stops[lines[lineIndex].stops.size() - 1])
		output.positiveBusTimes = vector<string>();
	else
		output.positiveBusTimes = Utilities::minutesToHHMM(positiveBusPassagesAtStop);

	//Likewise, if the stop is the beginning, it makes no sense to show the negative timetable

	if (stop == lines[lineIndex].stops[0])
		output.negativeBusTimes = vector<string>();
	else
		output.negativeBusTimes = Utilities::minutesToHHMM(negativeBusPassagesAtStop);

	//TODO remove from calculation if it is meaningless as well

	return output;
}

vector<vector<int>> BusBoss::calculateStopsForEachDirection(string startStop, string endStop, vector<int> commonLines) {
	//each outer position is the match for each line, with 0 on the inner being the direction (-1 or 1) and 1 being the number of stops to go through
	vector<vector<int>> output(commonLines.size(), vector<int>(2));

	for (int i = 0; i < commonLines.size(); i++) {
		//output was already with the correct dimensions so there is no need to use push_back
		output[i] = calculateStopsForEachDirection(startStop, endStop, commonLines[i]);
	}

	return output;
}

vector<int> BusBoss::calculateStopsForEachDirection(string startStop, string endStop, int commonLine) {
	vector<int> output(2);
	//0: Direction - -1 is negative (index gets smaller), 1 is positive (index gets bigger)

	//getting the line index from the line ID
	int lineIndex = findLineByID(commonLine);

	//finding the startStop position in the given line
	int startpos;
	for (startpos = 0; startpos < lines[lineIndex].stops.size(); startpos++) {
		if (lines[lineIndex].stops[startpos] == startStop) {
			break; //if we find the stop we break the loop and now have successfully got the start position
		}
	}

	//finding the endStop position in the given line
	int endpos;
	for (endpos = 0; endpos < lines[lineIndex].stops.size(); endpos++) {
		if (lines[lineIndex].stops[endpos] == endStop) {
			break; //if we find the stop we break the loop and now have successfully got the end position
		}
	}

	//start is left of end - positive direction
	if (startpos < endpos) {
		output[0] = 1;
		output[1] = endpos - startpos;
	}
	else {
		//start is right of end - negative direction
		output[0] = -1;
		output[1] = startpos - endpos;
	}

	return output;
}

int BusBoss::calculateDriversNeeded(const vector<int>& travelTimes, int frequency, int shiftsize) {

	//Note: To simplify internal calculations everything is done in minutes
	//As such, converting shiftsize to minutes by multiplying by 60
	shiftsize *= 60;

	//number of drivers needed
	unsigned int ndrivers = 0;

	//total travel time for the line in minutes (one iteration of the line, start to end with no reverse trip)
	unsigned int totalTravelTimeOneWay = 0;

	for (int i = 0; i < travelTimes.size(); i++) {
		totalTravelTimeOneWay += travelTimes[i];
	}

	//Calculating number of times that the line is traveled in one day

	//Start time of the service in minutes
	unsigned int startTime = BUS_START_TIME_HOUR * 60 + BUS_START_TIME_MINUTE;
	//End time of the service in minutes
	unsigned int endTime = BUS_END_TIME_HOUR * 60 + BUS_END_TIME_MINUTE;

	unsigned int nTravels = 0;

	//Runs through the schedule by summing frequency to determine number of buses that will start the line
	for (int currentTime = startTime; currentTime < endTime; currentTime += frequency) {
		nTravels++;
	}

	//Since the line has 2 directions and they are being run simultaneously
	nTravels *= 2;

	//Total minutes of travelling in one day - long to make sure that it is big enough, just in case
	long int totalTravelTimeDay = nTravels * totalTravelTimeOneWay;

	//Calculating the number of drivers needed

	//The time that the driver is available to work for
	int currentDriverTime = shiftsize;

	//The remaining line time (if last driver did not finish at the end of the line)
	unsigned int remainingLineTime = 0;

	//We will be subtracting from totalTravelTimeDay
	while (totalTravelTimeDay > 0) {

		//Resetting remaining line time because we now have a new driver
		remainingLineTime = 0;

		while (currentDriverTime > 0) {

			//Going through the line
			for (int i = 0; i < travelTimes.size(); i++) {
				//If the driver can go until the next stop then we substract the time (if a > b means if a - b > 0)
				if (currentDriverTime > travelTimes[i]) {
					currentDriverTime -= travelTimes[i]; //Subtracting from the driver time
					totalTravelTimeDay -= travelTimes[i]; //Subtracting from the day total
				}
				else {
					//If the driver cannot go until the next stop then a switch has happened and we will save the time to subtract from the next driver
					remainingLineTime += travelTimes[i];
					//In case the driver has some time left over, to break the while loop when the for loop ends and to make sure that the driver really stops driving
					//Otherwise the driver might've not gone between two stops very far apart but might've gone between two stops very close, straight after...
					currentDriverTime = 0;
				}
			}

		}

		//This driver is done
		//Add one to the counter of drivers needed
		ndrivers++;
		//Reset driver time because a new driver is taking over
		currentDriverTime = shiftsize;

		//Subtracts remaining line time (last driver did not finish at the end of the line)
		currentDriverTime -= remainingLineTime;
		totalTravelTimeDay -= remainingLineTime;
	}

	return ndrivers;
}

void BusBoss::saveDriverstoFile(ostream &file) {

	//Text lines are supposed to be in the following format:
	// ID ; Name ; Shift size ; Weekly hour limit ; Minimum rest time
	// (With a new line between each line)

	//First index done outside so that the newline can be appended before to cause for no newline at the end of the file
	file << drivers[0].ID << " ; " << drivers[0].name << " ; " << drivers[0].shiftsize << " ; " << drivers[0].weeklyhourlimit << " ; " << drivers[0].minresttime;

	//Starts at 1 because 0 was already done outside
	for (int i = 1; i < drivers.size(); i++) {
		file << "\n" << drivers[i].ID << " ; " << drivers[i].name << " ; " << drivers[i].shiftsize << " ; " << drivers[i].weeklyhourlimit << " ; " << drivers[i].minresttime;
	}

	//Driver file updated.
}

void BusBoss::saveLinestoFile(ostream &file) {

	//Text lines are supposed to be in the following format
	// ID ; bus frequency ; stops list separated by ',' ; delays list separated by ','
	// (With a new line between each line)

	//First index done outside so that the newline can be appended before to cause for no newline at the end of the file
	file << lines[0].ID << " ; " << lines[0].frequency << " ; ";

	//First index of stops list also done outside so ',' can be appended to the left
	file << lines[0].stops[0];

	//Stops list separated by ','
	for (int j = 1; j < lines[0].stops.size(); j++) {
		file << ", " << lines[0].stops[j];
	}

	//Separator between stops list and delays list
	file << "; ";

	//First index of delays list also done outside so ',' can be appended to the left
	file << lines[0].delaybetweenstops[0];

	//Delays list separated by ','
	for (int k = 1; k < lines[0].delaybetweenstops.size(); k++) {
		file << ", " << lines[0].delaybetweenstops[k];
	}


	//Starts at 1 because 0 was already done outside
	for (int i = 1; i < lines.size(); i++) {
		file << "\n" << lines[i].ID << " ; " << lines[i].frequency << " ; ";

		//First index of stops list also done outside so ',' can be appended to the left
		file << lines[i].stops[0];

		//Stops list separated by ','
		for (int j = 1; j < lines[i].stops.size(); j++) {
			file << ", " << lines[i].stops[j];
		}

		//Separator between stops list and delays list
		file << "; ";

		//First index of delays list also done outside so ',' can be appended to the left
		file << lines[i].delaybetweenstops[0];

		//Delays list separated by ','
		for (int k = 1; k < lines[i].delaybetweenstops.size(); k++) {
			file << ", " << lines[i].delaybetweenstops[k];
		}

	}

	//Lines file updated.
}
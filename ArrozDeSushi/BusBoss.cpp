#include "BusBoss.h"

BusBoss::BusBoss() {

}

BusBoss::~BusBoss() {

}

bool BusBoss::createNewDriver() {
	unsigned int newID;

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

	//Checking if a driver with the given ID already exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool driverExists = (drivers.count(newID) > 0);
	if (driverExists) {
		cout << "O ID dado já existe. Dois condutores diferentes não podem ter o mesmo ID.\nAbortando o processo de adição de condutor..." << endl;
		return false;
	}

	//Getting input from user about the driver

	string name; //the driver's name

	cout << "Qual o nome do condutor?" << endl;
	//With the testing done, this is needed if we are to use getline after using cin as a stream
	cin.ignore(10000, '\n');
	getline(cin, name); //using getline because the driver's name can have spaces
	Utilities::trimString(name); //trimming unnecessary whitespace from the driver name

	unsigned int shiftsize; //the size of the driver's shift - number of hours he can work per day
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

	unsigned int weeklyhourlimit; //number of hours the driver can work per day
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

	unsigned int minresttime; //minimum rest time between shifts (hours)
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


	//Using emplace to avoid unnecessary copy or move operations by calling the constructor in place (where the element will be inserted)
	//Arguments are forwarded to the object constructor
	//shifts vector is added as empty
	drivers.emplace(piecewise_construct, forward_as_tuple(newID), forward_as_tuple(newID, name, shiftsize, weeklyhourlimit, minresttime, vector<Shift>()));

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//returning true since the driver was successfully added
	return true;
}

bool BusBoss::modifyLine(unsigned int choice, int IDtomodify) {

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
		lines[IDtomodify].setFrequency(newFreq);
		break;
	}
	case 2:
	{
		//Changing the list of stops - only altering one stop at a time because otherwise the delay vector is no longer correct relative to the stops
		unsigned int posToChange;
		string newStopName = "";

		//Getting stops vector
		vector<string> stops = lines[IDtomodify].getStops();

		cout << "Qual a paragem a alterar?" << endl;
		//Printing options
		Utilities::printVector(stops);
		cout << ">> ";
		while (true) {
			cin >> posToChange;
			if (cin.fail() || posToChange >= stops.size()) {
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
				//Clearing screen and reprinting with warning
				Utilities::clearScreen();
				cout << "Opção inválida, por favor introduza um número válido (inteiro positivo menor que " << stops.size() - 1 << ")." << endl;
				cout << "Qual a paragem a alterar?" << endl;
				//Printing options
				Utilities::printVector(stops);
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

		//Changing the stop name in local vector
		stops[posToChange] = newStopName;

		//Changing the line object
		lines[IDtomodify].setStops(stops);

		break;
	}
	case 3:
	{
		//Changing the list of travel delays - only altering one delay at a time because otherwise the delay vector is no longer correct relative to the stops
		unsigned int posToChange;
		unsigned int newDelay = 0;

		//Getting times vector
		vector<unsigned int> times = lines[IDtomodify].getTravelTimesBetweenStops();
		//Getting stops vector
		vector<string> stops = lines[IDtomodify].getStops();

		cout << "Qual o tempo de viagem a alterar?" << endl;
		//Printing options
		for (int i = 0; i < stops.size() - 1; i++) {
			cout << i << ": " << "Tempo de viagem entre " << stops[i] << " e " << stops[i + 1] << ": " << times[i] << " minutos." << endl;
		}
		cout << ">> ";

		while (true) {
			cin >> posToChange;
			if (cin.fail() || posToChange >= times.size()) {
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
				//Clearing screen and reprinting with warning
				Utilities::clearScreen();
				cout << "Opção inválida, por favor introduza um número válido (inteiro positivo menor que " << times.size() - 1 << ")." << endl;
				cout << "Qual o tempo de viagem a alterar?" << endl;
				//Printing options
				for (int i = 0; i < stops.size() - 1; i++) {
					cout << i << ": " << "Tempo de viagem entre " << stops[i] << " e " << stops[i + 1] << ": " << times[i] << " minutos." << endl;
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

		//Changing time vector locally
		times[posToChange] = newDelay;

		//Changing times in object
		lines[IDtomodify].setTravelTimesBetweenStops(times);

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

	//Checking if a driver with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool driverExists = (drivers.count(IDtomodify) > 0);
	if (!driverExists) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de modificação de condutor..." << endl;
		return false;
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
	modifyDriver(choice, IDtomodify);

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//process was concluded successfully, returning true
	return true;
}

bool BusBoss::modifyDriver(unsigned int choice, int IDtomodify) {

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
		drivers[IDtomodify].setName(newName);
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
		drivers[IDtomodify].setShiftSize(newShiftSize);
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
		drivers[IDtomodify].setWeeklyHourLimit(newWeeklyhourlimit);
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
		drivers[IDtomodify].setMinRestTime(newMinresttime);
		break;
	}
	default:
		//The choice should never be invalid but if it is return false (error has ocurred)
		return false;
		break;
	}

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

	//Checking if a driver with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool driverExists = (drivers.count(IDtodel) > 0);
	if (!driverExists) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de eliminação de condutor..." << endl;
		return false;
	}

	cout << "Condutor encontrado, eliminando..." << endl;
	drivers.erase(IDtodel); //deleting the position of the map results in deleting the driver

	//Updating hasUnsavedChanges
	hasUnsavedChanges = true;

	//process was concluded successfully, returning true
	return true;
}

void BusBoss::displayDrivers() {

	//for that goes through all elements of map aka all drivers
	for (auto const &it : drivers) {
		//.second gets data, .first is key
		cout << "ID: " << it.second.getID() << " Nome: " << it.second.getName() << endl;
	}

}

void BusBoss::displayDrivers(bool availability) {
	//Using range based for loop to iterate throught the drivers map
	for (auto const &it : drivers) {
		//If the driver has the same availability as the one given as parameters, then print
		if (it.second.isAvailable() == availability) {
			cout << "ID: " << it.second.getID() << " Nome: " << it.second.getName() << endl;
		}
	}
}

void BusBoss::displayLines() {

	//for to go through all elements of map aka all lines
	for (auto const &it : lines) {
		//.second gets data, .first is key

		cout << "ID: " << it.second.getID() << " Primeira e última paragem: ";
		cout << it.second.getFirstStop() << " ... " << it.second.getLastStop();
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

	//Checking if a driver with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool driverExists = (drivers.count(IDtoprint) > 0);
	if (!driverExists) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de impressão de informação detalhada de um condutor..." << endl;
		return false;
	}

	//Driver found, printing detailed info
	cout << "\n";
	cout << drivers[IDtoprint];

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

	//Checking if a line with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool lineExists = (lines.count(IDtoprint) > 0);
	if (!lineExists) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão de informação detalhada de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Line found, printing detailed info
	cout << "\n";
	cout << lines[IDtoprint];

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

	//Checking if a driver with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool driverExists = (drivers.count(IDtoprint) > 0);
	if (!driverExists) {
		cout << "O ID dado não corresponde a nenhum dos condutores guardados.\nAbortando o processo de impressão de informação detalhada de um condutor..." << endl;
		return false;
	}

	//Clearing screen for output
	Utilities::clearScreen();

	//Driver found, printing shifts

	//Getting shifts vector
	vector<Shift> shifts = drivers[IDtoprint].getShifts();

	cout << "\n";
	if (shifts.empty()) {
		cout << "O condutor em questão não tem trabalho atribuído." << endl;
		return true;
	}
	else {
		cout << "O condutor tem " << shifts.size() << " turnos atribuídos." << endl;
		for (int i = 0; i < shifts.size(); i++) {
			cout << "Turno nº " << i + 1 << ":\n";
			cout << shifts[i] << endl;
		}
	}

	//Process concluded successfully
	return true;
}

bool BusBoss::printBusInfo() {
	unsigned int lineID = 0;

	cout << "Qual o ID da linha a imprimir?" << endl;
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

	//Checking if a line with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool lineExists = (lines.count(lineID) > 0);
	if (!lineExists) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão de informação detalhada de um autocarro..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Line found, asking for bus order number

	unsigned int busOrderNumber = 0;

	cout << "\n";
	cout << "Qual o número de ordem do autocarro a imprimir?";
	while (true) {
		cin >> lineID;
		if (cin.fail()) {
			cout << "Número de ordem inválido, por favor introduza um número de ordem válido (número inteiro positivo)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Checking if the bus in that order exists

	//Getting bus fleet
	vector<Bus> busFleet = lines[lineID].getBusFleet();

	//Pointer to the found object - const means not that the pointer is constant and will only point to one thing but that the object it points to is constant!
	const Bus *busToPrint = nullptr;

	//for each bus in busFleet
	for (auto const &bus : busFleet) {
		if (bus.getBusOrderInLine() == busOrderNumber) {
			//If the bus is found then the object pointer is set and the loop is broken
			busToPrint = &bus;
			break;
		}
	}

	//If the bus was found, print it, otherwise print error message
	//(If the bus was found then the pointer was set, which means it is not nullptr
	if (busToPrint != nullptr) {
		cout << "Autocarro especificado com sucesso!" << endl;
		cout << "Imprimindo informações sobre o autocarro:\n";

		cout << *busToPrint;

		//Process concluded successfully
		return true;
	}
	else {
		cout << "O autocarro com o número de ordem especificado não foi encontrado..." << endl;
		cout << "Abortando o processo de impressão de informação sobre um autocarro..." << endl;

		//Process was unsuccessful
		return false;
	}

}

bool BusBoss::listBusesInLine() {
	unsigned int lineID = 0;

	cout << "Qual o ID da linha a imprimir?" << endl;
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

	//Checking if a line with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool lineExists = (lines.count(lineID) > 0);
	if (!lineExists) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão de informação detalhada de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Line found, printing info of the busFleet

	cout << endl;

	vector<Bus> busFleet = lines[lineID].getBusFleet();

	cout << "A frota da linha pedida tem " << busFleet.size() << " autocarros." << endl;

	for (int i = 0; i < busFleet.size(); ++i) {
		cout << "Informação do autocarro nº " << i + 1 << ":" << endl;
		cout << busFleet[i] << endl;
	}

	return true;
}

bool BusBoss::listAllBusUnassignedPeriods() {

	vector<Bus> tempBuses;
	vector<Shift> tempBusRemainingShifts;

	//for each line, we are going to be listing each bus's unassigned period
	for (auto const &line : lines) {

		tempBuses = line.second.getBusFleet();

		cout << "Linha " << line.second.getID() << ":" << endl;

		//for each bus in the line
		for (auto const &bus : tempBuses) {
			cout << "Autocarro nº " << bus.getBusOrderInLine() << " de " << tempBuses.size() << ":" << endl;
			tempBusRemainingShifts = bus.getRemainingWork();

			if (tempBusRemainingShifts.empty()) {
				cout << "Este autocarro já tem todo o seu trabalho atribuído." << endl;
			}
			else {
				cout << "Trabalho que ainda falta atribuir condutor a:" << endl;

				//for each remaining shift in the bus - printing the times that are missing a driver
				for (auto const &shift : tempBusRemainingShifts) {
					auto startTime = Utilities::minutesToTime(shift.getStartTime());
					auto endTime = Utilities::minutesToTime(shift.getEndTime());
					cout << "Início do turno: " << startTime << "\t";
					cout << "Fim do turno: " << endTime << endl;
				}
			}
		}

	}

	cout << endl;

	//Process was concluded successfully
	return true;
}

bool BusBoss::listBusUnassignedPeriodsByLine() {
	unsigned int lineID = 0;

	cout << "Qual o ID da linha cujos períodos de trabalho disponíveis nos autocarros se irá imprimir?" << endl;
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

	//Checking if a line with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool lineExists = (lines.count(lineID) > 0);
	if (!lineExists) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão de períodos de trabalho disponíveis nos autocarros de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Printing based on given lineID
	listBusUnassignedPeriodsByLine(lineID);

	//Process concluded successfully
	return true;
}

bool BusBoss::listBusUnassignedPeriodsByLineAndWeekday() {
	unsigned int lineID = 0;

	cout << "Qual o ID da linha cujos períodos de trabalho disponíveis nos autocarros se irá imprimir?" << endl;
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

	//Checking if a line with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool lineExists = (lines.count(lineID) > 0);
	if (!lineExists) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão de períodos de trabalho disponíveis nos autocarros de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	unsigned int desiredWeekday = 0; //weekdays as according to Utilities::weekdays, [0,6]

	cout << "Qual o dia da semana para o qual mostrar os turnos disponíveis?" << endl;
	Utilities::printVector(Utilities::weekdays);
	while (true) {
		cin >> desiredWeekday;
		if (cin.fail() || (desiredWeekday > 6 || desiredWeekday < 0)) {
			//Clearing screen
			Utilities::clearScreen();
			//Displaying error message and repeating input asking
			cout << "Dia da semana inválido, por favor introduza um dia da semana válido (número inteiro positivo entre 0 e 6)." << endl;
			cout << "Qual o dia da semana para o qual mostrar os turnos disponíveis?" << endl;
			Utilities::printVector(Utilities::weekdays);
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Printing based on user input
	listBusUnassignedPeriodsByLineAndWeekday(lineID, desiredWeekday);

	//Process concluded successfully
	return true;
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
	this->driversFilePath = inputpathDrivers;
	this->linesFilePath = inputpathLines;
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

	string rawtempid = "";
	//Populating drivers map
	for (int i = 0; i < RawDrivers.size(); i++) {
		//Getting the raw id string to use when creating the map element
		rawtempid = RawDrivers[i].substr(0, RawDrivers[i].find(";"));
		//Trimming the string to remove unnecessary spaces
		Utilities::trimString(rawtempid);

		//Using emplace to avoid unnecessary copy or move operations by calling the constructor in place (where the element will be inserted)
		drivers.emplace(piecewise_construct, forward_as_tuple(stoi(rawtempid)), forward_as_tuple(RawDrivers[i]));
	}

	rawtempid = "";
	//Populating lines map
	for (int i = 0; i < RawLines.size(); i++) {
		//Getting the raw id string to use when creating the map element
		rawtempid = RawLines[i].substr(0, RawLines[i].find(";"));
		//Trimming the string to remove unnecessary spaces
		Utilities::trimString(rawtempid);

		//Using emplace to avoid unnecessary copy or move operations by calling the constructor in place (where the element will be inserted)
		lines.emplace(piecewise_construct, forward_as_tuple(stoi(rawtempid)), forward_as_tuple(RawLines[i]));
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

	//Closing streams
	outputDrivers.close();
	outputLines.close();

	//Function successful
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
	vector<unsigned int> foundLines = findLinesinStop(stopname);

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
	//1: No common lines - we consider only one line change for now, otherwise it is impossible
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
	vector<unsigned int> foundLinesStop1 = findLinesinStop(stop1);

	//Case 0.1
	if (foundLinesStop1.empty()) {
		cout << "A primeira paragem não pertence a nenhuma das linhas guardadas.\nAbortando o processo de cálculo de percurso entre duas paragens..." << endl;
		return false;
	}

	cout << "Qual a paragem de final do percurso?" << endl;
	getline(cin, stop2); //getline is used because the stop name can have spaces in it

	//Searching for the stop in lines using findLinesinStop
	vector<unsigned int> foundLinesStop2 = findLinesinStop(stop2);

	//Case 0.2
	if (foundLinesStop2.empty()) {
		cout << "A segunda paragem não pertence a nenhuma das linhas guardadas.\nAbortando o processo de cálculo de percurso entre duas paragens..." << endl;
		return false;
	}

	//Case 1
	vector<route> routesSwitch = calculateRouteSwitch(stop1, stop2, foundLinesStop1, foundLinesStop2);

	//Case 2 & 3 - can be handled together due to how things were structured

	//Check lines in common between the two stops
	vector<unsigned int> intersection = Utilities::intersectVectors(foundLinesStop1, foundLinesStop2);

	//Calculating the routes that use the same line
	vector<route> routesSame = calculateRouteSameLine(stop1, stop2, intersection);

	//Joining the routes using same line and 1 line switch
	vector<route> routes = Utilities::joinVectors(routesSwitch, routesSame);

	//Sorting results - comparison function/functor is not necessary since < operator was defined for route
	sort(routes.begin(), routes.end());

	//Printing results

	//Clearing screen
	Utilities::clearScreen();

	//Only print routes if the routes vector isn't empty
	if (!routes.empty()) {

		//"Header"
		cout << "Ponto de Partida: " << stop1 << endl;
		cout << "Destino: " << stop2 << endl;
		cout << "\nCaminhos possíveis:";


		//Printing results (all available routes)
		for (int i = 0; i < routes.size(); i++) {
			cout << "\n" << i + 1 << ":\n";

			//If there is a line switch we have to print the information differently
			if (routes[i].switchesline) {
				cout << "Apanhar a linha " << routes[i].lineIDs.first << " em direção a " << getDirection(routes[i].lineIDs.first, routes[i].directions.first);
				cout << ", durante " << routes[i].nStops.first << (routes[i].nStops.first > 1 ? " paragens." : " paragem.") << endl;
				cout << "Trocar para a linha " << routes[i].lineIDs.second << " em direção a " << getDirection(routes[i].lineIDs.second, routes[i].directions.second);
				cout << ", durante " << routes[i].nStops.second << (routes[i].nStops.second > 1 ? " paragens." : " paragem.") << endl;

				cout << "Tempo total de viagem (em minutos): " << routes[i].totalTimeinMinutes << endl;
			}
			else {
				cout << "Apanhar a linha " << routes[i].lineIDs.first << " em direção a " << getDirection(routes[i].lineIDs.first, routes[i].directions.first);
				cout << ", durante " << routes[i].nStops.first << (routes[i].nStops.first > 1 ? " paragens." : " paragem.") << endl;

				cout << "Tempo total de viagem (em minutos): " << routes[i].totalTimeinMinutes << endl;
			}
		}
	}
	//If the routes vector is empty no route was found
	else {
		cout << "Não foi encontrado nenhum percurso possível entre as duas paragens, considerando a possibilidade de 1 transbordo." << endl;
	}


	//Process was successful
	return true;
}

bool BusBoss::getIfHasUnsavedChanges() { return this->hasUnsavedChanges; }
//Refactored but need to improve the display quality really badly...
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
	vector<unsigned int> foundLinesStop = findLinesinStop(stop);

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

			//Getting the direction
			direction = getDirection(schedules[i].lineID, 1);

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

			//Getting the direction
			direction = getDirection(schedules[i].lineID, -1);

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
//(Same as above) Refactored but need to improve the display quality really badly...
bool BusBoss::showLineSchedule() {
	unsigned int lineIDtoprint;

	cout << "Qual o ID da linha cujo horário se irá imprimir? ";
	while (true) {
		cin >> lineIDtoprint;
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

	//Checking if a line with the given ID exists (number of elements bigger than 0)
	//Because we are using a map and not multimap .count will always be either 0 or 1 but > 0 is used for clarity
	bool lineExists = (lines.count(lineIDtoprint) > 0);
	if (!lineExists) {
		cout << "O ID dado não corresponde a nenhuma das linhas guardadas.\nAbortando o processo de impressão do horário de uma linha..." << endl;
		return false; //returning false since the process was not concluded successfully
	}

	//Getting schedules for each stop - each index will be the schedule for the stop in the same index as the stops vector
	vector<schedule> schedules;

	//Getting stops vector to pass each stop into the generateStopSchedules function
	vector<string> stops = lines[lineIDtoprint].getStops();

	//Filling the schedules vector
	for (int i = 0; i < stops.size(); i++) {
		schedules.push_back(generateStopSchedules(stops[i], lineIDtoprint));
	}

	cout << "\n\n\n";

	//Printing schedules

	//Because this is always the same line, the directions are always the same
	string positivedirection = stops[stops.size() - 1]; //Last stop is the positive direction
	string negativedirection = stops[0]; //First stop is the negative direction
	//Note: getDirection could be used as well, but since the vector was already used before, it is needed anyway, so there is no problem in using it here
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
			cout << "|" << setfill(' ') << left << setw(spaces) << "Paragem " + stops[i] << "|" << endl;
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
			cout << "|" << setfill(' ') << left << setw(spaces) << "Paragem " + stops[i] << "|" << endl;
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

unsigned int BusBoss::getStartTime() {
	return BUS_START_TIME_HOUR * 60 + BUS_START_TIME_MINUTE;
}

unsigned int BusBoss::getEndTime() {
	return BUS_END_TIME_HOUR * 60 + BUS_END_TIME_MINUTE;
}

void BusBoss::Reset() {
	//Deleting drivers
	drivers.clear();
	//Deleting lines
	lines.clear();

	//If more internal data is added, update this
}

vector<unsigned int> BusBoss::findLinesinStop(string stopname) {
	vector<unsigned int> output;

	//loop goes through all the lines in the map
	//(works like a for each in which each it is an iterator but can be used to directly access the map element, kind of)
	for (auto const &it : lines) {
		//If the given stop is in the list of stops, the ID of the line is pushed back into the output
		if (it.second.hasStop(stopname)) {
			output.push_back(it.second.getID()); //.first gets key, .second gets data in key
		}
	}

	//returning the matches found
	return output;
}

vector<BusBoss::schedule> BusBoss::generateStopSchedules(string stop, vector<unsigned int> lineIDs) {
	vector<schedule> output;

	for (int i = 0; i < lineIDs.size(); i++) {
		output.push_back(generateStopSchedules(stop, lineIDs[i]));
	}

	return output;
}

BusBoss::schedule BusBoss::generateStopSchedules(string stop, unsigned int lineID) {
	//Function note: to simplify the math here everything is done as minutes and in the end it is converted to strings

	schedule output;

	//Store the frequency to not have to keep getting the frequency
	int frequency = lines[lineID].getFrequency();

	//Same for stops and travel times
	vector<string> stops = lines[lineID].getStops();
	vector<unsigned int> times = lines[lineID].getTravelTimesBetweenStops();

	//Get start and end times in minutes
	unsigned int startTime = BUS_START_TIME_HOUR * 60 + BUS_START_TIME_MINUTE;
	unsigned int endTime = BUS_END_TIME_HOUR * 60 + BUS_END_TIME_MINUTE;

	//Get travel duration to the given stop from the start and from end
	unsigned int travelTimeFromStart = 0;
	for (int i = 0; i < stops.size(); i++) {
		if (stops[i] == stop) {
			//The stop was found
			break;
		}
		else {
			//Add travel time from this stop to the next one because this is not the one we want
			travelTimeFromStart += times[i];
			//There is no problem with getting out of bounds because at most the loop will break at stops.size which is one more than delaybetweenstops.size
		}
	}

	unsigned int travelTimeFromEnd = 0;
	for (int i = stops.size() - 1; i >= 0; i--) {
		if (stops[i] == stop) {
			//The stop was found
			break;
		}
		else {
			//Add travel time from this stop to the next one because this is not the one we want
			travelTimeFromEnd += times[i - 1]; //-1 because delays have 1 less index than stops
		}
	}

	//Times at which the buses start the line (direction does not matter for this because we are considering that buses depart from start and end simultaneously)
	vector<unsigned int> busDepartures;

	//Filling the vector 
	// Discarded: the stop condition is if the bus cannot make it to one of the endings of the line, he does not depart
	// Now using pure "if before the time of end of service" as a stop condition due to teacher suggestion
	for (int currentTime = startTime; currentTime < endTime; currentTime += frequency) {
		busDepartures.push_back(currentTime);
	}

	//Times at which the bus passes at the given stop
	vector<int> positiveBusPassagesAtStop; //In the positive direction (start to finish)
	vector<int> negativeBusPassagesAtStop; //In the negative direction (finish to start)

	//Filling vector of bus passages at the given stop
	for (int i = 0; i < busDepartures.size(); i++) {
		positiveBusPassagesAtStop.push_back(busDepartures[i] + travelTimeFromStart);
		negativeBusPassagesAtStop.push_back(busDepartures[i] + travelTimeFromEnd);
	}

	//Setting output schedule values

	//Line ID for printing stop schedule
	output.lineID = lineID;

	//Dealing with the stop being the end or the beginning of the line

	//If the stop is the end, it makes no sense to show the positive timetable

	if (stop == stops[stops.size() - 1])
		output.positiveBusTimes = vector<string>();
	else
		output.positiveBusTimes = Utilities::minutesToHHMM(positiveBusPassagesAtStop);

	//Likewise, if the stop is the beginning, it makes no sense to show the negative timetable

	if (stop == stops[0])
		output.negativeBusTimes = vector<string>();
	else
		output.negativeBusTimes = Utilities::minutesToHHMM(negativeBusPassagesAtStop);

	return output;
}

vector<BusBoss::route> BusBoss::calculateRouteSameLine(string startStop, string endStop, vector<unsigned int> commonLines) {
	//vector of distances, distance has the ID for the line, the direction and the number of stops to go through (to compare each line)
	vector<route> output(commonLines.size());

	for (int i = 0; i < commonLines.size(); i++) {
		//output was already with the correct dimensions so there is no need to use push_back
		output[i] = calculateRouteSameLine(startStop, endStop, commonLines[i]);
	}

	return output;
}

BusBoss::route BusBoss::calculateRouteSameLine(string startStop, string endStop, unsigned int commonLineID) {
	route r;

	//This is in the same line so there are no switches
	r.switchesline = false;

	//Setting line ID to be able to know which line we are referring to in the future
	r.lineIDs.first = commonLineID;

	//Getting the stops vector for this line
	vector<string> stops = lines[commonLineID].getStops();

	//finding the startStop position in the given line
	int startpos = lines[commonLineID].findStop(startStop);

	//finding the endStop position in the given line
	int endpos = lines[commonLineID].findStop(endStop);

	//Getting the total time for comparison with other routes
	vector<unsigned int> times = lines[commonLineID].getTravelTimesBetweenStops();
	unsigned int totalTime = 0;

	//start is left of end - positive direction
	if (startpos < endpos) {
		r.directions.first = 1;
		r.nStops.first = endpos - startpos;

		//Calculating times based on direction
		for (int i = startpos; i < endpos; ++i) {
			totalTime += times[i];
		}
	}
	else {
		//start is right of end - negative direction
		r.directions.first = -1;
		r.nStops.first = startpos - endpos;

		//Calculating times based on direction
		for (int i = endpos; i < startpos; ++i) {
			totalTime += times[i];
		}
	}

	//Setting the total time
	r.totalTimeinMinutes = totalTime;

	return r;
}

vector<BusBoss::route> BusBoss::calculateRouteSwitch(string stop1, string stop2, const vector<unsigned int>& foundLinesStop1, const vector<unsigned int>& foundLinesStop2) {

	vector<route> output;

	//Vectors that hold the stops being compared
	vector<string> outerstops;
	vector<string> innerstops;

	//For each line of stop1
	for (unsigned int outerline : foundLinesStop1) {
		outerstops = lines[outerline].getStops();

		//Searching for each stop of the current line of stop1
		for (string outerstop : outerstops) {

			//Because we wouldn't switch the line at the first stop anyway, that would be going on the same line (I think)
			if (outerstop == stop1)
				continue;

			//For each line of stop2, 
			for (unsigned int innerline : foundLinesStop2) {
				//if the line is the same, then a "switch" would be possible on every stop, thus making the system not work, so if the line is the same, we skip the line
				if (innerline == outerline)
					continue;

				innerstops = lines[innerline].getStops();

				for (string innerstop : innerstops) {
					//Because we wouldn't switch the line at the last stop anyway, that would be going on the same line (I think)
					if (innerstop == stop2)
						continue;

					//If a common stop is found between the lines of stop1 and stop2, the route is generated and appended to the output
					if (innerstop == outerstop)
						output.push_back(calculateRouteSwitch(stop1, stop2, innerstop, outerline, innerline));
				}

			}

		}

	}

	return output;
}

BusBoss::route BusBoss::calculateRouteSwitch(string stop1, string stop2, string commonstop, unsigned int stop1line, unsigned int stop2line) {
	route r;

	//This function only calculates routes when switching lines
	r.switchesline = true;

	//Setting the line IDs
	r.lineIDs = { stop1line, stop2line };

	//Getting position of stops in their respective lines
	unsigned int stop1pos = lines[stop1line].findStop(stop1);
	unsigned int commonstopline1pos = lines[stop1line].findStop(commonstop);
	unsigned int commonstopline2pos = lines[stop2line].findStop(commonstop);
	unsigned int stop2pos = lines[stop2line].findStop(stop2);

	//Getting data depending on direction

	//Getting the time from stop1 to commonstop
	vector<unsigned int> times = lines[stop1line].getTravelTimesBetweenStops();
	unsigned int totalTime = 0;

	//stop1 to commonstop
	//stop1 is left of commonstop - positive direction
	if (stop1pos < commonstopline1pos) {
		r.directions.first = 1;
		r.nStops.first = commonstopline1pos - stop1pos;

		//Getting time based on direction
		for (int i = stop1pos; i < commonstopline1pos; ++i) {
			totalTime += times[i];
		}
	}
	else {
		//stop1 is right of commonstop - negative direction
		r.directions.first = -1;
		r.nStops.first = stop1pos - commonstopline1pos;

		//Getting time based on direction
		for (int i = commonstopline1pos; i < stop1pos; ++i) {
			totalTime += times[i];
		}
	}

	//Getting the time from commonstop to stop2
	times = lines[stop2line].getTravelTimesBetweenStops();

	//commonstop to stop2
	//commonstop is left of stop2 - positive direction
	if (commonstopline2pos < stop2pos) {
		r.directions.second = 1;
		r.nStops.second = stop2pos - commonstopline2pos;

		//Getting time based on direction
		for (int i = commonstopline2pos; i < stop2pos; ++i) {
			totalTime += times[i];
		}
	}
	else {
		//stop1 is right of commonstop - negative direction
		r.directions.second = -1;
		r.nStops.second = commonstopline2pos - stop2pos;

		//Getting time based on direction
		for (int i = stop2pos; i < commonstopline2pos; ++i) {
			totalTime += times[i];
		}
	}

	//Setting the total time
	r.totalTimeinMinutes = totalTime;

	return r;
}

void BusBoss::listBusUnassignedPeriodsByLine(unsigned int lineID) {

	//Getting bus fleet
	vector<Bus> busFleet = lines[lineID].getBusFleet();

	//Used to temporarily save the bus shifts
	vector<Shift> tempShifts;

	//for each bus in the line
	for (auto const &bus : busFleet) {
		cout << "Autocarro nº " << bus.getBusOrderInLine() << " de " << busFleet.size() << ":" << endl;
		tempShifts = bus.getRemainingWork();

		if (tempShifts.empty()) {
			cout << "Este autocarro já tem todo o seu trabalho atribuído." << endl;
		}
		else {
			cout << "Trabalho que ainda falta atribuir condutor a:" << endl;

			//for each remaining shift in the bus - printing the times that are missing a driver
			for (auto const &shift : tempShifts) {
				auto startTime = Utilities::minutesToTime(shift.getStartTime());
				auto endTime = Utilities::minutesToTime(shift.getEndTime());
				cout << "Início do turno: " << startTime << "\t";
				cout << "Fim do turno: " << endTime << endl;
			}
		}

		//Spacing
		cout << endl;
	}
}

void BusBoss::listBusUnassignedPeriodsByLineAndWeekday(unsigned int lineID, unsigned int desiredWeekday) {

	//Getting bus fleet
	vector<Bus> busFleet = lines[lineID].getBusFleet();

	//Used to temporarily save the bus shifts
	vector<Shift> tempShifts;

	//for each bus in the line
	for (auto const &bus : busFleet) {
		cout << "Autocarro nº " << bus.getBusOrderInLine() << " de " << busFleet.size() << ":" << endl;
		tempShifts = bus.getRemainingWork();

		if (tempShifts.empty()) {
			cout << "Este autocarro já tem todo o seu trabalho atribuído." << endl;
		}
		else {

			//Shifts to print (that are in the requested day)
			vector<Shift> shiftsToPrint;

			//Finding shifts to print
			for (const auto &shift : tempShifts) {
				auto startTime = Utilities::minutesToTime(shift.getStartTime());
				if (startTime.weekday == desiredWeekday)
					shiftsToPrint.push_back(shift);
			}

			//Checking if there are shifts to print (if shiftsToPrint is empty there are none)
			if (shiftsToPrint.empty()) {
				cout << "Este autocarro não tem turnos por atribuir no dia requesitado." << endl;
			}
			else {
				//else print

				//for each shift to print - printing the times that are missing a driver
				for (auto const &shift : shiftsToPrint) {
					auto startTime = Utilities::minutesToTime(shift.getStartTime());
					auto endTime = Utilities::minutesToTime(shift.getEndTime());
					cout << "Início do turno: " << startTime << "\t";
					cout << "Fim do turno: " << endTime << endl;
				}
			}
		}

		//Spacing
		cout << endl;
	}
}

string BusBoss::getDirection(unsigned int lineID, short int direction) {

	string output;

	//Positive direction
	if (direction == 1) {
		output = lines[lineID].getLastStop();
	}
	//Negative direction
	else {
		output = lines[lineID].getFirstStop();
	}

	return output;
}

void BusBoss::saveDriverstoFile(ostream &file) {

	//Text lines are supposed to be in the following format:
	// ID ; Name ; Shift size ; Weekly hour limit ; Minimum rest time
	// (With a new line between each line)

	//Getting an iterator to access all the elements in the drivers map (constant because there is no need to change)
	auto driverit = drivers.cbegin();

	//First item done outside so that the newline can be appended before to cause for no newline at the end or start of the file
	//(Also the reason to not use a range based for loop - accessing first item separately)
	file << driverit->second.getID() << " ; " << driverit->second.getName() << " ; "
		<< driverit->second.getShiftSize() << " ; " << driverit->second.getWeeklyHourLimit() << " ; " << driverit->second.getMinRestTime();

	//For loop with the iterator, incremented at the start because the first element was already saved
	//Note: ++it avoids extra copy operation (see code generated by pre-increment vs post-increment for iterators) 
	for (++driverit; driverit != drivers.cend(); ++driverit) {
		file << "\n" << driverit->second.getID() << " ; " << driverit->second.getName() << " ; "
			<< driverit->second.getShiftSize() << " ; " << driverit->second.getWeeklyHourLimit() << " ; " << driverit->second.getMinRestTime();
	}

	//Driver file updated.
}

void BusBoss::saveLinestoFile(ostream &file) {

	//Text lines are supposed to be in the following format
	// ID ; bus frequency ; stops list separated by ',' ; delays list separated by ','
	// (With a new line between each line)

	//Getting an iterator to access all the elements in the drivers map (constant because there is no need to change)
	auto lineit = lines.cbegin();

	//First item done outside so that the newline can be appended before to cause for no newline at the end or start of the file
	//(Also the reason to not use a range based for loop - accessing first item separately)
	file << lineit->second.getID() << " ; " << lineit->second.getFrequency() << " ; ";

	//Getting stops vector into a temporary vector (also used for the other lines)
	vector<string> stops = lineit->second.getStops();

	//First index of stops list also done outside so ',' can be appended to the left
	file << stops[0];

	//Stops list separated by ','
	for (int j = 1; j < stops.size(); j++) {
		file << ", " << stops[j];
	}

	//Separator between stops list and delays list
	file << "; ";

	//Getting time between stops vector into a temporary vector (also used for the other lines)
	vector<unsigned int> times = lineit->second.getTravelTimesBetweenStops();

	//First index of delays list also done outside so ',' can be appended to the left
	file << times[0];

	//Delays list separated by ','
	for (int k = 1; k < times.size(); k++) {
		file << ", " << times[k];
	}


	//For loop with the iterator, incremented at the start because the first element was already saved
	//Note: ++it avoids extra copy operation (see code generated by pre-increment vs post-increment for iterators)
	for (++lineit; lineit != lines.cend(); ++lineit) {
		file << "\n" << lineit->second.getID() << " ; " << lineit->second.getFrequency() << " ; ";

		//Getting stops vector
		stops = lineit->second.getStops();

		//First index of stops list also done outside so ',' can be appended to the left
		file << stops[0];

		//Stops list separated by ','
		for (int j = 1; j < stops.size(); j++) {
			file << ", " << stops[j];
		}

		//Separator between stops list and delays list
		file << "; ";

		//Getting time between stops vector
		times = lineit->second.getTravelTimesBetweenStops();

		//First index of delays list also done outside so ',' can be appended to the left
		file << times[0];

		//Delays list separated by ','
		for (int k = 1; k < times.size(); k++) {
			file << ", " << times[k];
		}

	}

	//Lines file updated.
}

ostream& operator<<(ostream &os, const Line &l) {
	os << "ID: " << l.getID() << "\nFrequência de passagem de autocarros: " << l.getFrequency();
	os << "\nParagens desta linha:\n";
	Utilities::printVector(l.getStops());
	os << "Tempos de viagem entre estas paragens:\n";
	Utilities::printVector(l.getTravelTimesBetweenStops());

	return os;
}

ostream& operator<<(ostream &os, const Driver &d) {
	cout << "ID: " << d.getID() << "\nNome: " << d.getName();
	cout << "\nTamanho de turno: " << d.getShiftSize() << "\nLimite de horas de trabalho semanal: " << d.getWeeklyHourLimit();
	cout << "\nTempo mínimo de descanso: " << d.getMinRestTime() << endl;

	return os;
}

ostream& operator<<(ostream &os, const Shift &s) {
	os << "ID da linha: " << s.getLineID() << "\nID do condutor: " << s.getDriverID();
	os << "\nNúmero de ordem do autocarro na linha: " << s.getBusOrderNumber() << endl;
	os << "Tempo de início(WIP): ";
	auto starttime = Utilities::minutesToTime(s.getStartTime());
	os << Utilities::weekdays[starttime.weekday] << ", " << starttime.hourAndMinutes << endl;
	os << "\nTempo de fim(WIP): ";
	auto endtime = Utilities::minutesToTime(s.getEndTime());
	os << Utilities::weekdays[endtime.weekday] << ", " << endtime.hourAndMinutes << endl;

	return os;
}

ostream& operator <<(ostream &os, const Bus &b) {
	os << "ID da linha: " << b.getLineID();

	os << "\nNúmero de ordem na linha: " << b.getBusOrderInLine();

	os << "\nHora de início do serviço do autocarro: " << Utilities::minutesToHHMM(b.getStartTime());

	os << "\nHora de fim de serviço do autocarro: " << Utilities::minutesToHHMM(b.getEndTime()) << endl;

	return os;
}

ostream& operator <<(ostream &os, const Utilities::time &t) {
	os << Utilities::weekdays[t.weekday] << " " << t.hourAndMinutes;
	return os;
}

bool BusBoss::route::operator<(const BusBoss::route &r) const {
	return totalTimeinMinutes < r.totalTimeinMinutes;
}
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
}


BusManager::~BusManager() {

}

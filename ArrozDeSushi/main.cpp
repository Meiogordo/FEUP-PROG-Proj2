#include <iostream>
#include "Menu.h"
using namespace std;

bool callFunctions(string &id);
void funcao2_1();

int main() {

	//Also TODO: Node endings always register as invalid options because there are no child options, deal with that
	//-> Can only be dealt with by calling functions from the ID because there being no ending nodes in fact means the option is incorrect
	//This will have to be done by calling functions by comparing the ID with a hardcoded list, then afterwards remove the last option ID

	Menu menumaozinhas("Menu.txt");
	string currentselection = "", tempinput;

	//Menu loop
	while (true) {
		menumaozinhas.DisplayByID(currentselection);
		cin >> tempinput;

		if (currentselection.empty() && tempinput == "0") {
			//This means we are at the main menu and the exit option was selected
			break;
		}
		else
			if (!currentselection.empty() && tempinput == "0") {
				//This means we are in a submen and want to go back to the main menu
				currentselection = "";
			}
			else {
				//in order to not append a dot to an empty string and get ".1" which wouldn't work
				if (currentselection.empty()) {
					currentselection = tempinput;
				}
				else {
					currentselection += "." + tempinput;
				}
			}

			if (callFunctions(currentselection)) {
				//if the function ran, clear the screen afterwards
				menumaozinhas.ClearScreen();
			}
			menumaozinhas.ClearScreen();
	}

	return 0;
}

//Function to call functions based on hardcoded ID, returns true if function found, false if not found
bool callFunctions(string &id) {
	if (id == "2.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		funcao2_1();
		system("pause");
		return true;
	}

	return false;
}

void funcao2_1() {
	cout << "\nEsta funcao correu\n";
}
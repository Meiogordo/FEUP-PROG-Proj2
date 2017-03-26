#include <iostream>
#include "Menu.h"
using namespace std;

//TODO:
//- Decide if menuRunner really needs to be an int - How can menu execution go wrong?
//- Maybe create menu object inside menu? If file not found then there is your error


bool callFunctions(string &id);
void funcao2_1();
int menuRunner();

int main() {

	int menureturn = menuRunner();

	if (menureturn == 0)
		// menu exited successfully with no errors
		return 0;
	else
		//maybe errors? don't know how menu can have error
		return 1;
}

//Most menu stuff
int menuRunner() {

	//Generating menu object with constructor pointing to menu txt file
	Menu menumaozinhas("Menu.txt");

	//Menu loop
	while (true) {

		string currentselection = ""; //current selection holds the menu state
		string tempinput; //temporary input holder

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

	//Menu execution exited successfully
	return 0;
}


//Function to call functions based on hardcoded ID (only way to do this), returns true if function found, false if not found
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
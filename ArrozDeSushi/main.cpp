#include <iostream>
#include "Menu.h"
#include "BusManager.h"
using namespace std;

//TODO:
//- Decide if menuRunner really needs to be an int - How can menu execution go wrong?
//- Maybe create menu object inside menu? If file not found then there is your error

//Prototypes
int menuRunner(BusManager &bm);
bool callFunctions(string &id, BusManager &bm);

int main() {

	//Init
	BusManager bm;
	bm.Load();

	/*
	try {
		bm.Load();
	}
	catch () {
		cout << "Load sem êxito." << endl;
	}
	*/

	//Main menu running
	int menureturn = menuRunner(bm);

	if (menureturn == 0)
		// menu exited successfully with no errors
		return 0;
	else
		//maybe errors? don't know how menu can have error - read error
		return 1;
}

//Most menu stuff
int menuRunner(BusManager &bm) {

	string currentselection = ""; //current selection holds the menu state
	string tempinput; //temporary input holder

	//Generating menu object with constructor pointing to menu txt file
	Menu menumaozinhas("Menu.txt");


	//clear screen of whatever was printed before, just in case with a pause before so all output is read with time
	cout << "Pressione enter para continuar...";
	cin.get();
	Utilities::clearScreen();

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

			if (callFunctions(currentselection, bm)) {
				//do something based on failed state maybe
			}

			Utilities::clearScreen();
	}

	//Menu execution exited successfully
	return 0;
}

//Function to call functions based on hardcoded ID (only way to do this), returns true if function found, false if not found
bool callFunctions(string &id, BusManager &bm) {

	//Debugging an idea, remove later - aka spaghetti if it works, bug if it doesn't
	cin.ignore(10000, '\n');

	//Template for function calling
	/* 
	if (id == "specify id here") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		//testfunction();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}
	*/

	//Displaying lines
	if (id == "2.1.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.displayLines();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//Adding lines
	if (id == "2.1.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.createNewLine();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//Modifying lines

	//Deleting lines
	if (id == "2.1.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.deleteLine();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//Displaying drivers
	if (id == "2.2.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.displayDrivers();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//Adding drivers
	if (id == "2.2.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.createNewDriver();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//Modifying drivers

	//Deleting drivers
	if (id == "2.2.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.deleteDriver();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//load
	if (id == "3.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.Load();
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	//Not yet implemented stuff
	if (id == "1.1" || id == "1.2" || id == "1.3" || id == "1.4" || id == "1.5" || id == "1.6" || id == "1.7" || id == "2.3" || id == "2.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		cout << "WIP, function not yet implemented" << endl;
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
		//function was found, return true
		return true;
	}

	return false;
}
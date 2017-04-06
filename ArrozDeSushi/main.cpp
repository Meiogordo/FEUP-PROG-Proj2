#include <iostream>
#include "Menu.h"
#include "BusManager.h"
using namespace std;

//TODO:
//- Decide if menuRunner really needs to be an int - How can menu execution go wrong?
//- Maybe create menu object inside menu? If file not found then there is your error


bool callFunctions(string &id);
int menuRunner();

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
				//if the function ran, clear the screen afterwards - isn't this useless? We clear the screen anyway
				menumaozinhas.ClearScreen();
			}

			menumaozinhas.ClearScreen();
	}

	//Menu execution exited successfully
	return 0;
}

//Function to call functions based on hardcoded ID (only way to do this), returns true if function found, false if not found
bool callFunctions(string &id, BusManager &bm) {

	//Template for function calling
	/* 
	if (id == "specify id here") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		//testfunction();
		//pause to see output
		system("pause");
		//function was found, return true
		return true;
	}
	*/

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

	return false;
}
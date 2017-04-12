#include <iostream>
#include <string>
#include <clocale>
#include "Menu.h"
#include "BusManager.h"
#include "Utilities.h"
using namespace std;

#ifdef _WIN32
#include "Windows.h"
#define enablePTcharacters() SetConsoleCP(1252); SetConsoleOutputCP(1252);
#else
#define enablePTcharacters() setlocale(LC_ALL, "Portuguese");
#endif

//Prototypes
int menuRunner(BusManager &bm);
bool callFunctions(string &id, BusManager &bm);

int main() {

	//Enabling portuguese characters on the console - for me this doesn't work so I just comment out and use locale for now
	//enablePTcharacters();
	setlocale(LC_ALL, "Portuguese");

	//Tests here

	//Init
	BusManager bm;
	bm.Load();

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
	unsigned int tempinput; //temporary input holder - unsigned int to make sure that only numbers are inputted

	//Generating menu object with constructor pointing to menu txt file
	Menu menumaozinhas("Menu.txt");


	//clear screen of whatever was printed before, just in case with a pause before so all output is read with time
	Utilities::pause();
	Utilities::clearScreen();

	//Menu loop
	while (true) {

		menumaozinhas.DisplayByID(currentselection);
		while (true) {
			cin >> tempinput;
			if (cin.fail()) {
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
				//Clearing screen and reprinting
				Utilities::clearScreen();
				cout << "Seleção inválida! Tente novamente!\n\n";
				menumaozinhas.DisplayByID(currentselection);
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		if (currentselection.empty() && tempinput == 0) {
			//This means we are at the main menu and the exit option was selected so we can exit the program by exiting the loop

			//But first, checking if there are unsaved changes
			if (bm.getIfHasUnsavedChanges()) {
				string option;
				cout << "Tem alterações não gravadas, deseja mesmo assim sair do programa? (S/N)" << endl;
				cout << ">> ";
				while (true) {
					cin >> option;
					if (cin.fail() || (option != "S" && option != "N")) {
						//Clearing error flags and buffer
						cin.clear();
						cin.ignore(10000, '\n');
						//Clearing screen to display input prompt again
						cout << "Opção inválida." << endl;
						cout << "Tem alterações não gravadas, deseja mesmo assim sair do programa? (S/N)" << endl;
						cout << ">> ";
					}
					else {
						//input is valid so we break the loop
						break;
					}
				}

				//If the user specifies that he does not want to exit the program because he has unsaved progress we do not exit the program
				if (option == "N") {
					//As such, we do nothing
				}
				else {
					//Otherwise, the user specified that he does want to exit so we break the loop to exit the program
					break;
				}
			}
			else {
				//If the user does not have unsaved changes we simply exit the program as usual
				break;
			}

		}
		else
			if (!currentselection.empty() && tempinput == 0) {
				//This means we are in a submenu and want to go back to the main menu
				currentselection = "";
			}
			else {
				//in order to not append a dot to an empty string and get ".1" which wouldn't work
				if (currentselection.empty()) {
					currentselection = to_string(tempinput);
				}
				else {
					currentselection += "." + to_string(tempinput);
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

	//before running any function, the screen is cleared
	Utilities::clearScreen();

	//Template for function calling
	/*
	if (id == "specify id here") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		//testfunction();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}
	*/

	//Printing the assigned work for a driver
	if (id == "1.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.printDriverShifts();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Which lines pass at a certain stop
	if (id == "1.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.findLinesinStop();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Listing available drivers
	if (id == "1.5") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.displayDrivers(true);
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	if (id == "1.6") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.routeBetweenTwoStops();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Displaying lines
	if (id == "2.1.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.displayLines();
		//pause to see output
		Utilities::pause();
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
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Modifying lines
	if (id == "2.1.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.modifyLine();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Deleting lines
	if (id == "2.1.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.deleteLine();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Printing detailed info about a line
	if (id == "2.1.5") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.printLine();
		//pause to see output
		Utilities::pause();
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
		Utilities::pause();
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
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Modifying drivers
	if (id == "2.2.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.modifyDriver();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Deleting drivers
	if (id == "2.2.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.deleteDriver();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Printing detailed info about a driver
	if (id == "2.2.5") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.printDriver();
		//pause to see output
		Utilities::pause();
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
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//save
	if (id == "3.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		bm.Save();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Not yet implemented stuff
	if (id == "1.1" || id == "1.2" || id == "1.3" || id == "1.7") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		cout << "WIP, function not yet implemented" << endl;
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	return false;
}
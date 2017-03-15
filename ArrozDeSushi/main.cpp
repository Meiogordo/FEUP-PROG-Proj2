#include <iostream>
#include "Menu.h"
using namespace std;

int main() {

	//TODO: Implement calling functions through currentselection id here in main
	//Also TODO: Node endings always register as invalid options because there are no child options, deal with that

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

			menumaozinhas.ClearScreen();
	}

	return 0;
}
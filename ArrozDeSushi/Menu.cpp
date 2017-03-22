#include "Menu.h"
#include <string>
#include <vector>
using namespace std;

bool Menu::compareDiffSizeStrings(string a, string b) {
	bool output = true;

	if (a.size() < b.size()) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) {
				output = false;
				break;
			}
		}
	}
	else {
		for (int i = 0; i < b.size(); i++) {
			if (b[i] != a[i]) {
				output = false;
				break;
			}
		}
	}

	return output;
}

int Menu::countCharInString(string input, char searchchar) {
	int counter = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == searchchar) {
			counter++;
		}
	}

	return counter;
}

vector<string> Menu::ReadFile(string path) {

	vector<string> inputstuff;

	//infile is path

	ifstream myfile;
	string line;

	myfile.open(path);

	//int counterRead = 0;
	while (getline(myfile, line)) {
		inputstuff.push_back(line);
		//counterRead++;
		//cout << "\na ler linha" << counterRead;
	}

	myfile.close();

	return inputstuff;
}

Menu::option Menu::createOptionFromString(string rawline) {
	option newOption;

	string id = rawline.substr(0, rawline.find_first_of(" "));
	string optiontext = rawline.substr(rawline.find_first_of(" ") + 1);
	int depth_level = countCharInString(id, '.');

	newOption.id = id;
	newOption.option_text = optiontext;
	newOption.depth_level = depth_level;

	return newOption;
}

Menu::Menu(string path) {
	vector<string> rawfile = ReadFile(path);
	for (int i = 0; i < rawfile.size(); i++) {
		menuOptions.push_back(createOptionFromString(rawfile[i]));
	}
}

void Menu::DisplayWholeMenu() {
	for (int i = 0; i < menuOptions.size(); i++) {
		cout << i << ": " << menuOptions[i].id << " " << menuOptions[i].option_text << "\t depth: " << menuOptions[i].depth_level << endl;
	}
}

void Menu::DisplayByID(string &id) {
	vector<option> display = FindOptionByID(id);

	//Dealing with invalid option -> empty vector
	if (display.empty()) {
		cout << "Invalid selection! Try again!\n\n";
		//Removing last selected option from ID
		if (id.size() == 1) {
			//First level selection, requested ID can be cleared with no problems to reset the menu
			id = "";
		}
		else {
			//More than first level selection, to clear the last selection from the requested ID we must remove the ".N"
			id = id.substr(0, id.find_last_of('.')); //Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		}
		//Displays the menu again with the new reverted ID
		(*this).DisplayByID(id);
	}
	else {
		for (int i = 0; i < display.size(); i++) {
			cout << display[i].id << " " << display[i].option_text << endl;
		}
		//Exit option and fancy last line for input
		if (id == "") {
			//If in main menu (string empty) show exit instead of back
			cout << "0 Exit" << endl;
		}
		else {
			cout << "0 Back" << endl;
		}
		cout << "\n>>> ";
	}

}

void Menu::ClearScreen() {
	/*
	//Inserting line breaks for now for debugging but afterwards it will be a true screen clearer
	cout << "\n\n\n";
	*/
	system("cls"); //temporary - will move to windows.h functions later on
}

//Probably will be unused now
vector<Menu::option> Menu::FindAllOptionsStartingWithID(string id) {
	vector<option> output;

	for (int i = 0; i < menuOptions.size(); i++) {
		//ugly code, maybe use temp var to store ID and treat it like that
		if (menuOptions[i].id.substr(0, menuOptions[i].id.find_first_of('.')) == id) {
			output.push_back(menuOptions[i]);
		}
	}

	return output;
}

//returns a vector of options based on the provided ID. If ID is empty, returns all options with 0 depth, otherwise with a matching ID and depth level
vector<Menu::option> Menu::FindOptionByID(string id) {
	vector<option> output;

	if (id == "") {
		//find all options with depth_level 0
		for (int i = 0; i < menuOptions.size(); i++) {
			if (menuOptions[i].depth_level == 0)
				output.push_back(menuOptions[i]);
		}
	}
	else {
		//Hardcoded dot at end to avoid printing parent options
		//Inside else because the string would never be empty otherwise
		id += ".";

		//finds depth level and also uses it as comparison to avoid "1.1" from getting "1" too, etc
		//another solution would be changing compareDiffSizeStrings to look at the size of either the first or second string, I guess
		int wanteddepth = countCharInString(id, '.');

		for (int i = 0; i < menuOptions.size(); i++) {
			if (compareDiffSizeStrings(menuOptions[i].id, id) && menuOptions[i].depth_level == wanteddepth) {
				output.push_back(menuOptions[i]);
			}
		}
	}

	return output;
}

Menu::~Menu() {}

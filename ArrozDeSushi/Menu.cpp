#include "Menu.h"
#include <string>
#include <vector>
using namespace std;

int countCharInString(string input, char searchchar) {
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

void Menu::DisplayByID(string id) {
	vector<option> display = FindAllOptionsStartingWithID(id);

	for (int i = 0; i < display.size(); i++) {
		cout << display[i].id << " " << display[i].option_text << endl;
	}
}

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

//TODO
//Exact ID only returns one option.
//Fix that. Maybe this can be a selector iterated when called (call with 1.1, 1.2, 1.3)

vector<Menu::option> Menu::FindExactOptionByID(string id) {
	vector<option> output;

	for (int i = 0; i < menuOptions.size(); i++) {
		//ugly code, maybe use temp var to store ID and treat it like that
		if (menuOptions[i].id == id) {
			output.push_back(menuOptions[i]);
		}
	}

	return output;
}

Menu::~Menu() {}

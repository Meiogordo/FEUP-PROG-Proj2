#include "Menu.h"
#include <string>
#include <vector>
using namespace std;

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
	// TODO: Implement counter of dots in id, that + 1 is the depth_level
	int depth_level = 420;

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
		cout << i << ": " << menuOptions[i].id << " " << menuOptions[i].option_text << endl;
	}
}

Menu::~Menu() {}

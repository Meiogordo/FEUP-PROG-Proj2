#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Menu {
public:
	//Constructor. Takes the path to the txt representing the menu and populates the options from it.
	Menu(string path);
	//Overload for the constructor to enable inputting the menu text directly
	Menu(vector<string> rawlines);
	//Displays the whole menu - useful for testing
	void DisplayWholeMenu();
	//Displays options based on ID, return all adjacent depths downwards (1 returns 1, 1.1, 1.2, etc)
	void DisplayByID(string &id);
	//Destructor, unused at the moment
	~Menu();
private:
	//option is a struct to hold the data for each menu option
	struct option {
		string id; //id such as 1.1, 2.5, 1
		int depth_level; //how deep the option is nested: 1 is at the 0 level, 1.1 is at level 1 and so on
		string option_text; //the text to display alongside the option id: 1.1 <option_text>
	};

	//vector containing all the options in the menu
	vector<option> menuOptions;

	//Interprets the line in format "<id> <text>"
	option createOptionFromString(string rawline);

	//Finds a set of options based on an exact ID, for example 1. matches 1.1, 1.2, 1.3, etc
	//If the id is empty ("") it finds all the options with depth_level = 0
	vector<option> FindOptionByID(string id);
};


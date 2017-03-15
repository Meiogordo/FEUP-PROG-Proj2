#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Menu {
public:
	//Constructor. Takes the path to the txt representing the menu and populates 
	Menu(string path);
	//Displays the whole menu
	void DisplayWholeMenu();
	//Displays options based on ID, return all depths (1 returns 1, 1.1, 1.2, etc)
	void DisplayByID(string id);
	void ClearScreen();
	~Menu();
private:
	//A struct must be created for each option
	struct option {
		string id; //id such as 1.1, 2.5, 1
		int depth_level; //how deep the option is nested: 1 is at the 0 level, 1.1 is at level 1 and so on
		string option_text; //the text to display alongside the option id: 1.1 <option_text>
	};
	//Compares two strings with different sizes by going through the smaller one until it ends,
	//if all the characters match until then, returns true
	bool compareDiffSizeStrings(string a, string b);
	//Counts the number of occurrences of a char in a string, useful for depth_level
	int countCharInString(string input, char searchchar);
	//Reads a file and returns a vector in which each position is a string representing a line in the file
	vector<string> ReadFile(string path);
	//Interprets the line in format "<id> <text>"
	option createOptionFromString(string rawline);
	//vector containing all the options in the menu
	vector<option> menuOptions;

	//TODO: Define how to get to the options and cleanup unnecessary stuff
	//Finds options based on parameters
	vector<option> FindAllOptionsStartingWithID(string id);
	//Finds a set of options based on an exact ID, for example 1. matches 1.1, 1.2, 1.3, etc
	//If the id is empty ("") it finds all the options with depth_level = 0
	vector<option> FindOptionByID(string id);
};


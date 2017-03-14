#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Menu
{
public:
	//Constructor. Takes the path to the txt representing the menu and populates 
	Menu(string path);
	//Displays the whole menu
	void DisplayWholeMenu();
	~Menu();
private:
	//A struct must be created for each option
	struct option {
		string id; //id such as 1.1, 2.5, 1
		int depth_level; //how deep the option is nested: 1 is at the 0 level, 1.1 is at level 1 and so on
		string option_text; //the text to display alongside the option id: 1.1 <option_text>
	};
	//Reads a file and returns a vector in which each position is a string representing a line in the file
	vector<string> ReadFile(string path);
	//Interprets the line in format "<id> <text>"
	option createOptionFromString(string rawline);
	//vector containing all the options in the menu
	vector<option> menuOptions;
};


#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <iostream>

using namespace std;

namespace Utilities {
	//Reads a file and returns a vector in which each position is a string representing a line in the file
	vector<string> ReadFile(string path);
	//Overload for ReadFile this time using an open ifstream
	vector<string> ReadFile(ifstream &input);
	//Counts the number of occurrences of a char in a string, useful for Menu's option.depth_level
	int countCharInString(string input, char searchchar);
	//Compares two strings with different sizes by going through the smaller one until it ends,
	//if all the characters match until then, returns true
	bool compareDiffSizeStrings(string a, string b);
	//Remove whitespace surrounding text  - "   aa  " -> "aa"
	void trimString(string &s);
	//Print vector of any kind of element
	template<typename T>
	void printVector(const vector<T> &v) {
		for (int i = 0; i < v.size(); i++) {
			cout << i << ": " << v[i] << endl;
		}
	}

	//Split a string into a string vector on each ocurrence of another string
	vector<string> splitString(string input, string splitter);
	//Overload for a single char - calls the string version
	vector<string> splitString(string input, char splitter);
	//Clears the screen - originally inside Menu
	void clearScreen();
	//Pauses the program until enter is pressed - displays informative message to prompt the user to press enter. Warning: to pause successfully this function must clear the whole cin buffer, make sure there is no important data there
	void pause();
}
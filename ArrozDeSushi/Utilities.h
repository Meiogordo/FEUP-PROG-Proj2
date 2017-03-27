#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

namespace Utilities {
	//Reads a file and returns a vector in which each position is a string representing a line in the file
	vector<string> ReadFile(string path);
	//Counts the number of occurrences of a char in a string, useful for Menu's option.depth_level
	int countCharInString(string input, char searchchar);
	//Compares two strings with different sizes by going through the smaller one until it ends,
	//if all the characters match until then, returns true
	bool compareDiffSizeStrings(string a, string b);
	//Remove whitespace surrounding text  - "   aa  " -> "aa"
	void trimString(string &s);
}
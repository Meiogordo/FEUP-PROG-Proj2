#include "Utilities.h"

namespace Utilities {
	vector<string> ReadFile(string path) {

		vector<string> inputstuff;

		ifstream myfile;
		string line;

		myfile.open(path);

		while (getline(myfile, line)) {
			inputstuff.push_back(line);
		}

		myfile.close();

		return inputstuff;
	}

	vector<string> ReadFile(ifstream &input) {
		vector<string> inputstuff;
		string line;

		while (getline(input, line)) {
			inputstuff.push_back(line);
		}

		return inputstuff;
	}

	int countCharInString(string input, char searchchar) {
		int counter = 0;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == searchchar) {
				counter++;
			}
		}

		return counter;
	}

	bool compareDiffSizeStrings(string a, string b) {
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

	void trimString(string &s){
		s = s.substr(s.find_first_not_of(' ')); // Cut spaces to the left
		s = s.substr(0, s.find_last_not_of(' ')); // Cut spaces to the right
	}

	vector<string> splitString(string input, string splitter) {
		vector<string> output;

		//while the splitter sequence exists in input
		while (input.find(splitter) != string::npos) {
			output.push_back(input.substr(0, input.find(splitter)));
			input = input.substr(input.find(splitter) + splitter.length() + 1);
		}

		//Push back the remainder, or the whole string if no ocurrence of splitter exists
		output.push_back(input);

		return output;
	}
}
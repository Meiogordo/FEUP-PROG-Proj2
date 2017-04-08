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

	void trimString(string &s) {
		if (s.find(' ') != string::npos) {
			s = s.substr(s.find_first_not_of(' ')); // Cut spaces to the left
			s = s.substr(0, s.find_last_not_of(' ') + 1); // Cut spaces to the right
		}
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

	vector<string> splitString(string input, char splitter) {
		return splitString(input, to_string(splitter));
	}

	void clearScreen() {
		//system("cls"); //temporary - will move to something else later on due to not being cross platform and having security issues
		cout << string(10000, '\n');
	}

	void pause() {
		//Legacy explanation comments, moved from where cin.get() was used to pause:
		//
		//This seems like it will be necessary before every cin.get() ... It looks like cin is getting trash stuck in it
		//Disregard, it is cin getting the "\n" from the enter press at the end of every input... So, cin.ignore before pause is mandatory!
		//

		//Ignores everything in the cin buffer
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		//pause to see output
		cout << "Pressione enter para continuar...";
		cin.get();
	}
}
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
}
#include <iostream>
using namespace std;

int main() {

	cout << "Hello Sushi!" << endl;

	return 0;
}

// a pôr noutro ficheiro
/*
vector<string> ReadFile(string path) {

	vector<string> inputstuff;

	//infile is path

	ifstream myfile;
	string line;

	myfile.open(path);

	int counterRead = 0;
	while (getline(myfile, line)) {
		inputstuff.push_back(line);
		counterRead++;
		cout << "\na ler linha" << counterRead;
	}

	myfile.close();

	return inputstuff;
}
*/
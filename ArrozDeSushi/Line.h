#pragma once

#include <vector>
#include <string>

using namespace std;

class Line {
public:
	Line(unsigned int ID, unsigned int frequency, vector<string> stops, vector<int> travelTimesBetweenStops);
	~Line();
private:
	//Missing frequency and travel times between stops???
	//do not understand what they want the int vector (times here, timesList there) to be...
	unsigned int ID;
	unsigned int frequency;
	vector<string> stops;
	vector<int> travelTimesBetweenStops;
};


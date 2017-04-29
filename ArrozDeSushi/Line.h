#pragma once

#include <vector>
#include <string>

using namespace std;

class Line {
public:
	Line(unsigned int ID, unsigned int frequency, vector<string> stops, vector<unsigned int> travelTimesBetweenStops);
	~Line();

	//setters
	unsigned int setID(unsigned int ID);
	unsigned int setFrequency(unsigned int frequency);
	vector<string> setStops(vector<string> stops);
	vector<int> setTravelTimesBetweenStops(vector<int> travelTimesBetweenStops);



	//getters

	unsigned int getID() const;
	unsigned int getFrequency() const;
	vector<string> getStops() const;
	vector<unsigned int> getTravelTimesBetweenStops() const;
private:
	//Missing frequency and travel times between stops???
	//do not understand what they want the int vector (times here, timesList there) to be...
	unsigned int ID;
	unsigned int frequency;
	vector<string> stops;
	vector<unsigned int> travelTimesBetweenStops;
};


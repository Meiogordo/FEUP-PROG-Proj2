#pragma once

#include <vector>
#include <string>

#include "Utilities.h"

using namespace std;

class Line {
public:
	//Constructors

	//Default constructor so that the lines map doesn't explode
	Line();
	//Constructor that can take in a raw line from a text file
	Line(string rawline);
	Line(unsigned int ID, unsigned int frequency, const vector<string> &stops, const vector<unsigned int> &travelTimesBetweenStops);
	~Line();

	//setters

	void setID(unsigned int ID);
	void setFrequency(unsigned int frequency);
	void setStops(const vector<string> &stops);
	void setTravelTimesBetweenStops(const vector<unsigned int> &travelTimesBetweenStops);


	//getters

	unsigned int getID() const;
	unsigned int getFrequency() const;
	vector<string> getStops() const;
	vector<unsigned int> getTravelTimesBetweenStops() const;
	string getFirstStop() const;
	string getLastStop() const;

	//other methods
	bool hasStop(string stopname) const;
	//Finds the stop index in the stops vector, returns -1 if not found
	int findStop(string stopname) const;
private:
	//Missing frequency and travel times between stops???
	//do not understand what they want the int vector (times here, timesList there) to be...
	unsigned int ID;
	unsigned int frequency;
	vector<string> stops;
	vector<unsigned int> travelTimesBetweenStops;
};


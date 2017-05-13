#include "Line.h"
#include "Bus.h"


Line::Line() {}

Line::Line(string rawline) {
	//Splitting the information by ";" - which is the information splitter
	vector<string> info = Utilities::splitString(rawline, ";");

	//Trimming the info to remove excess spaces
	for (int i = 0; i < info.size(); i++) {
		Utilities::trimString(info[i]);
	}

	//vector organization
	// 0 - ID
	// 1 - Frequency of bus stops for each stop in the line (minutes)
	// 2 - List of stop names
	// 3 - Times (in minutes) of travel between stops

	int ID = stoi(info[0]); //line ID
	int frequency = stoi(info[1]); //frequency of buses in the line (minutes)
	vector<string> stops; //list of stop names
	vector<unsigned int> travelTimesBetweenStops; //Times (in minutes) of travel between stops
	
	unsigned int totalTime = 0; //Total time of one full travel (in minutes) (only A to B / not B to A)
	int numberOfBuses; //number of Buses needed
	vector<Bus> busFleet; //vector of Buses

	//Filling in the data vectors

	//Stops vector
	stops = Utilities::splitString(info[2], ","); //each stop is separated by a comma
	for (int i = 0; i < stops.size(); i++) {
		//Trimming the extra whitespace
		Utilities::trimString(stops[i]);
	}

	//Temporary string vector because we need the string to be trimmed to be able to "stoi" it
	vector<string> tempintodelays = Utilities::splitString(info[3], ",");
	for (int i = 0; i < tempintodelays.size(); i++) {
		//Trimming the string for stoi
		Utilities::trimString(tempintodelays[i]);
	}

	for (int i = 0; i < tempintodelays.size(); i++) {
		//Filling in the delay vector with stoi
		travelTimesBetweenStops.push_back(stoi(tempintodelays[i]));
	}

	for (int i = 0; i < travelTimesBetweenStops.size(); i++) {
		totalTime += travelTimesBetweenStops[i];
	}
	
	numberOfBuses = ceil((double)2 * totalTime / frequency);
	
	//Resetting the totalBuses because this is another line (starts at 1)
	Bus::setTotalBuses(1);

	//Getting start and end times
	unsigned int busStartTime = BusBoss::getStartTime();
	unsigned int busEndTime = BusBoss::getEndTime();

	//Adding elements to busFleet
	for (int i = 0; i < numberOfBuses; ++i) {
		//Bus init
		busFleet.emplace_back(Bus(ID, busStartTime, busEndTime));
		//Incrementing start time
		busStartTime += frequency;
		busEndTime += frequency;
	}

	//Assigning values to line
	this->ID = ID;
	this->frequency = frequency;
	this->stops = stops;
	this->travelTimesBetweenStops = travelTimesBetweenStops;
	this->busFleet = busFleet;
	this->nrOfBuses = numberOfBuses;
}

Line::Line(unsigned int ID, unsigned int frequency, const vector<string> &stops, const vector<unsigned int> &travelTimesBetweenStops)
	: ID(ID), frequency(frequency), stops(stops), travelTimesBetweenStops(travelTimesBetweenStops) {

	unsigned int totalTime = 0;

	for (int i = 0; i < travelTimesBetweenStops.size(); i++) {
		totalTime += travelTimesBetweenStops[i];
	}

	unsigned int numberOfBuses = ceil((double)2 * totalTime / frequency);

	//Resetting the totalBuses because this is another line (starts at 1)
	Bus::setTotalBuses(1);

	//Getting start and end times
	unsigned int busStartTime = BusBoss::getStartTime();
	unsigned int busEndTime = BusBoss::getEndTime();

	//Adding elements to busFleet
	for (int i = 0; i < numberOfBuses; ++i) {
		//Bus init
		busFleet.emplace_back(Bus(ID, busStartTime, busEndTime));
		//Incrementing start time
		busStartTime += frequency;
		busEndTime += frequency;
	}

	this->nrOfBuses = numberOfBuses;
	this->busFleet = busFleet;
}

Line::~Line() {}

unsigned int Line::getID() const {
	return ID;
}

unsigned int Line::getFrequency() const {
	return frequency;
}

vector<string> Line::getStops() const {
	return stops;
}

vector<unsigned int> Line::getTravelTimesBetweenStops() const {
	return travelTimesBetweenStops;
}

string Line::getFirstStop() const {
	return stops[0];
}

string Line::getLastStop() const {
	return stops[stops.size() - 1];
}

vector<Bus> Line::getBusFleet() const {
	return busFleet;
}

unsigned int Line::getNrOfBuses() const {
	return nrOfBuses;
}

void Line::setID(unsigned int ID) {
	this->ID = ID;
}

void Line::setFrequency(unsigned int frequency) {
	this->frequency = frequency;
}

void Line::setStops(const vector<string> &stops) {
	this->stops = stops;
}

void Line::setTravelTimesBetweenStops(const vector<unsigned int> &travelTimesBetweenStops) {
	this->travelTimesBetweenStops = travelTimesBetweenStops;
}

bool Line::hasStop(string stopname) const {
	for (int i = 0; i < stops.size(); i++) {
		if (stopname == stops[i]) {
			return true;
		}
	}
	return false;
}

int Line::findStop(string stopname) const {

	for (int i = 0; i < stops.size(); ++i) {
		if (stops[i] == stopname)
			return i;
	}

	return -1;
}

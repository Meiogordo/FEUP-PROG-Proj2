#include "Line.h"



Line::Line(unsigned int ID, unsigned int frequency, vector<string> stops, vector<unsigned int> travelTimesBetweenStops)
	: ID(ID), frequency(frequency), stops(stops), travelTimesBetweenStops(travelTimesBetweenStops)
{}

Line::~Line()
{}

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


void Line::setID(unsigned int ID) {
	this->ID = ID;
}
void Line::setFrequency(unsigned int frequency) {
	this->frequency = frequency;
}
void Line::setStops(vector<string> stops) {
	this->stops = stops;
}
void Line::setTravelTimesBetweenStops(vector<int> travelTimesBetweenStops) {
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

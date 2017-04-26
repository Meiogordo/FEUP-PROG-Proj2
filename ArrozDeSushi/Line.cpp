#include "Line.h"



Line::Line(unsigned int ID, unsigned int frequency, vector<string> stops, vector<int> travelTimesBetweenStops)
	: ID(ID), frequency(frequency), stops(stops), travelTimesBetweenStops(travelTimesBetweenStops)
{}

Line::~Line()
{}

unsigned int Line::getID() {
	return ID;
}

unsigned int Line::getFrequency() {
	return frequency;
}

vector<string> Line::getStops() {
	return stops;
}

vector<int> Line::getTravelTimesBetweenStops() {
	return travelTimesBetweenStops;
}


unsigned int Line::setID(unsigned int ID) {
	this->ID = ID;
}
unsigned int Line::setFrequency(unsigned int frequency) {
	this->frequency = frequency;
}
vector<string> Line::setStops(vector<string> stops) {
	this->stops = stops;
}
vector<int> Line::setTravelTimesBetweenStops(vector<int> travelTimesBetweenStops) {
	this->travelTimesBetweenStops = travelTimesBetweenStops;
}


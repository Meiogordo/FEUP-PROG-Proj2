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


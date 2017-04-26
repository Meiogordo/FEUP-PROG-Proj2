#include "Line.h"



Line::Line(unsigned int ID, unsigned int frequency, vector<string> stops, vector<int> travelTimesBetweenStops)
	: ID(ID), frequency(frequency), stops(stops), travelTimesBetweenStops(travelTimesBetweenStops)
{}

Line::~Line()
{
}

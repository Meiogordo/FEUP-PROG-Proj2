#include "Shift.h"



Shift::Shift(unsigned int lineID, unsigned int driverID, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime)
	: lineID(lineID), driverID(driverID), busOrderNumber(busOrderNumber), startTime(startTime), endTime(endTime)
{}

Shift::~Shift()
{}

unsigned int Shift::getLineID() const {
	return lineID;
}

unsigned int Shift::getDriverID() const {
	return driverID;
}

unsigned int Shift::getBusOrderNumber() const {
	return busOrderNumber;
}

unsigned int Shift::getStartTime() const {
	return startTime;
}

unsigned int Shift::getEndTime() const {
	return endTime;
}

void Shift::setLineID(unsigned int busLineID){
	this->lineID = busLineID;
}

void Shift::setDriverID(unsigned int driverID){
	this->driverID = driverID;
}

void Shift::setBusOrderNumber(unsigned int busOrderNumber){
	this->busOrderNumber = busOrderNumber;
}

void Shift::setStartTime(unsigned int startTime){
	this->startTime = startTime;
}

void Shift::setEndTime(unsigned int endTime){
	this->endTime = endTime;
}

bool Shift::operator<(const Shift &s) const {
	return this->getStartTime() < s.getStartTime();
}

#include "Shift.h"



Shift::Shift(unsigned int busLineID, unsigned int driverID, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime) 
	: busLineID(busLineID),driverID(driverID),busOrderNumber(busOrderNumber),startTime(startTime),endTime(endTime)
{}

Shift::~Shift()
{}

unsigned int Shift::getBusLineId() const {
	return busLineID;
}

unsigned int Shift::getDriverId() const {
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

void Shift::setBusLineId(unsigned int busLineID){
	this->busLineID = busLineID;
}
void Shift::setDriverId(unsigned int driverID){
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
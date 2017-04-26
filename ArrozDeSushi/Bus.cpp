#include "Bus.h"

Bus::Bus(unsigned int ID, unsigned int driverID, unsigned int lineID)
	: ID(ID), driverID(driverID), lineID(lineID) 
{}

Bus::~Bus() {}

unsigned int Bus::getBusOrderInLine() const {
	return orderInLine;
}

unsigned int Bus::getDriverID() const {
	return driverID;
}

unsigned int Bus::getLineID() const {
	return lineID;
}

vector<Shift> Bus::getSchedule() const {
	return schedule;
}

unsigned int Bus::setDriverID(unsigned int driverID) {
	this->driverID = driverID;
}
unsigned int Bus::setLineID(unsigned int lineID) {
	this->lineID = lineID;
}
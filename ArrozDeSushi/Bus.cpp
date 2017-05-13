#include "Bus.h"

unsigned int Bus::totalBuses = 1;

Bus::Bus() {
	orderInLine = totalBuses++;
}

Bus::Bus(unsigned int lineID) : lineID(lineID)
{
	this->driverID = 0;
}

Bus::Bus(unsigned int driverID, unsigned int lineID, const vector<Shift> &shift)
	: driverID(driverID), lineID(lineID), schedule(shift) {
	orderInLine = totalBuses++;
}

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

int Bus::getTotalBuses() {
	return totalBuses;
}

bool Bus::getIsWorking() {
	return isWorking;
}

void Bus::setDriverID(unsigned int driverID) {
	this->driverID = driverID;
}

void Bus::setLineID(unsigned int lineID) {
	this->lineID = lineID;
}

void Bus::setIsWorking(bool isWorking) {
	this->isWorking = isWorking;
}

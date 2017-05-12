#include "Bus.h"

unsigned int Bus::totalBuses = 1;

Bus::Bus() {
	ID = totalBuses++;
}

Bus::Bus(unsigned int driverID, unsigned int lineID, unsigned int orderInLine, const vector<Shift> &shift)
	: driverID(driverID), lineID(lineID), orderInLine(orderInLine), schedule(shift) {
	ID = totalBuses++;
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

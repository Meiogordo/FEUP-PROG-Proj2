#include "Bus.h"

unsigned int Bus::totalBuses = 1;

Bus::Bus() {
	orderInLine = totalBuses++;
}

Bus::Bus(unsigned int lineID, unsigned int startTime, unsigned int endTime) : lineID(lineID), startTime(startTime), endTime(endTime) {
	orderInLine = totalBuses++;
}

Bus::~Bus() {}

unsigned int Bus::getBusOrderInLine() const {
	return orderInLine;
}

unsigned int Bus::getLineID() const {
	return lineID;
}

int Bus::getTotalBuses() {
	return totalBuses;
}

unsigned int Bus::getStartTime() const {
	return startTime;
}

unsigned int Bus::getEndTime() const {
	return endTime;
}

void Bus::setLineID(unsigned int lineID) {
	this->lineID = lineID;
}

void Bus::setStartTime(unsigned int startTime) {
	this->startTime = startTime;
}

void Bus::setEndTime(unsigned int endTime) {
	this->endTime = endTime;
}

void Bus::setTotalBuses(unsigned int totalBuses) {
	Bus::totalBuses = totalBuses;
}

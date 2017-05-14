#include "Bus.h"

unsigned int Bus::totalBuses = 1;

Bus::Bus() {
	orderInLine = totalBuses++;
}

Bus::Bus(unsigned int lineID, unsigned int startTime, unsigned int endTime) : lineID(lineID), startTime(startTime), endTime(endTime) {
	orderInLine = totalBuses++;

	unsigned int shiftStart = startTime;

	//Shifts are hourly, because that is the smallest time interval they can be

	while (shiftStart < endTime) {

		//Several Days of Week (each day is 1440 minutes, so that is added for each day)
		for (int i = 0; i < 6; ++i) {
			remainingWork.emplace_back(Shift(lineID, 0, orderInLine, shiftStart + 1440 * i, shiftStart + 60 + 1440 * i));
		}

		shiftStart += 60;

	}

	//sorting the remaining work vector to make sure it is sequential in terms of start time
	sort(remainingWork.begin(), remainingWork.end());

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

vector<Shift> Bus::getRemainingWork() const {
	return remainingWork;
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

bool Bus::removeWork(unsigned int startTime, unsigned int endTime) {

	//Determines if some work was removed
	bool someWorkWasRemoved = false;

	//We must remove all shifts that start in an hour contained in the interval
	//For example to remove from 2 to 4, we would have to remove 2 to 3, and 3 to 4, so remove starting with 2 and 3, which is adding 1 hour to starting time while it is < than end time
	for (unsigned int hourToDel = startTime; hourToDel < endTime; hourToDel += 60) {
		for (int i = 0; i < remainingWork.size(); ++i) {
			if (remainingWork[i].getStartTime() == hourToDel) {
				remainingWork.erase(remainingWork.begin() + i);
				someWorkWasRemoved = true;
				break;
			}
		}
	}

	//sorting the remaining work vector to make sure it is sequential in terms of start time
	sort(remainingWork.begin(), remainingWork.end());

	return someWorkWasRemoved;
}

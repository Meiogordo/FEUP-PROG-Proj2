#include "Driver.h"



Driver::Driver(unsigned int ID, string name, unsigned int shiftsize, unsigned int weeklyhourlimit, unsigned int minresttime, vector<Shift> shifts) 
	: ID(ID), name(name), shiftsize(shiftsize), weeklyhourlimit(weeklyhourlimit), minresttime(minresttime), shifts(shifts)
{}


Driver::~Driver() {}

unsigned int Driver::getID() {
	return ID;
}

string Driver::getName(){
	return name;
}

unsigned int Driver::getShiftSize() {
	return shiftsize;
}

unsigned int Driver::getWeeklyHourLimit() {
	return weeklyhourlimit;
}

unsigned int Driver::getMinRestTime() {
	return minresttime;
}

vector<Shift> Driver::getShifts() {
	return shifts;
}

unsigned int Driver::setID(unsigned int ID) {
	this->ID = ID;
}
string Driver::setName(string name) {
	this->name = name;
}
unsigned int Driver::setShiftSize(unsigned int shiftsize) {
	this->shiftsize = shiftsize;
}
unsigned int Driver::setWeeklyHourLimit(unsigned int weeklyhourlimit) {
	this->weeklyhourlimit;
}
unsigned int Driver::setMinRestTime(unsigned int minresttime) {
	this->minresttime;
}
vector<Shift> Driver::setShifts(vector<Shift> shifts) {
	this->shifts = shifts;
}

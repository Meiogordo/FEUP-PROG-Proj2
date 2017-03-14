#include <iostream>
#include "Menu.h"
using namespace std;

int main() {

	Menu test("Menu.txt");

	//test.DisplayWholeMenu();
	test.DisplayByID("1");

	return 0;
}
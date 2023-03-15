#pragma once
#define _HAS_STD_BYTE 0
#include "myexc.h"

class Validator
{
public:
	/*Validator();
	~Validator();*/

	bool checkMinute(int var) { return var < 60 && var > 0; };

	bool checkHour(int var) { return var > 0 && var < 25; };

	bool checkYear(int var) { return var >= 2022; };

	bool checkDay(int var) { return var > 0 && var < 32; };

	bool checkMonth(int var) { return var > 0 && var < 13; };

	bool checkNrOfPeople(int var) { return var >= 0; };
};


//Validator::Validator()
//{
//}
//
//Validator::~Validator()
//{
//}

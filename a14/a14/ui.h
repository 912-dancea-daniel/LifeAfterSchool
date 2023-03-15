#pragma once

#include "service.h"
#include "forCSV.h"


class ui 
{
public:
	ui();
	~ui();

	void printMenu();

	void printEvents();

	void printUserMenu();

	void printUserEvents(int opt);


public:
	Service serv;
};



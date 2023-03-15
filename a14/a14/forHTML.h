#pragma once
#include "repo.h"


class forHTML : public EventVector
{
public:
	forHTML();
	~forHTML();

	void writeToFile(std::string fileName = "outHTML.html");

	void openFile(std::string fileName = "outHTML.html");

private:

};



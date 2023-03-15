#pragma once
#include "repo.h"


class CSV : public EventVector
{
public:
	CSV();
	~CSV();

	void writeToFile(std::string fileName = "outCSV.csv");

	void openFile(std::string fileName = "outHTML.html");

private:

};


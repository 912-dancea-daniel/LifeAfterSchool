#include "forCSV.h"
#include <Windows.h>
#include <shellapi.h>
#include <WinUser.h>


CSV::CSV()
{
}

CSV::~CSV()
{
}


void CSV::writeToFile(std::string fileName)
{
    std::ofstream f(fileName);
    f << "sep=,"<<"\n";

    for (int i = 0; i < arr.size(); i++)
        f << arr[i].getTitle() << "," << arr[i].getDescription() << "," << arr[i].getNumberOfPeople() << "," << arr[i].getDate().getYear() << "-" << arr[i].getDate().getMonth() << "-" << arr[i].getDate().getDay() << " " << arr[i].getDate().getHour() << ":" << arr[i].getDate().getMinute() << "," << arr[i].getLink() << "\n";
    f.close();
}

void CSV::openFile(std::string fileName)
{
    ShellExecute(0, 0, L"outCSV.csv", 0, 0, SW_SHOW);
}




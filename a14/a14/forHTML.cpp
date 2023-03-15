#include "forHTML.h"

forHTML::forHTML()
{
}

forHTML::~forHTML()
{
}

void forHTML::writeToFile(std::string fileName)
{
    std::ofstream f(fileName);
    f << "<!DOCTYPE html><html><head>Events</head><body>"; //starting html
    f << "<table border = '1'><tr><td>Title</td><td>Desciption</td><td>Number of people </td><td>Date </td><td>Youtube link</td> </tr>";

    //add some html content
    //as an example: if you have array of objects featuring the properties name & value, you can print out a new line for each property pairs like this:
    for (int i = 0; i < arr.size(); i++)
        f << "<tr><td>" << arr[i].getTitle() << "</td><td>" << arr[i].getDescription() << "</td><td>" << arr[i].getNumberOfPeople() << "</td><td>" << arr[i].getDate().getDay() << "." << arr[i].getDate().getMonth() << "." << arr[i].getDate().getYear() << "  " << arr[i].getDate().getHour() << ":" << arr[i].getDate().getMinute() << "</td><td><a href = >" << arr[i].getLink() << "</td></tr>";

    //ending html
    f << "</table></body></html>";
    f.close();
}

void forHTML::openFile(std::string fileName)
{
    system(std::string("start " + fileName).c_str());
}

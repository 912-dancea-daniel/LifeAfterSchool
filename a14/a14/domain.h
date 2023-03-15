#pragma once
#include <string>
#include <iostream>


class Date
{
public:
	Date(int day = 0, int month = 0, int year = 0, int hour = 0, int minute = 0);
	~Date();

	//set Day
	void setDay(int newValue);

	//get day
	int getDay();

	//set Month
	void setMonth(int newValue);

	//get Month
	int getMonth();

	//set Year
	void setYear(int newValue);

	//get Year
	int getYear();

	//set Hour
	void setHour(int newValue);

	//get Hour
	int getHour();

	//set Minute
	void setMinute(int newValue);

	//get Minute
	int getMinute();

	//compare the date to another one
	bool SameDate(Date compare);


	friend std::ostream& operator<<(std::ostream& stream, const Date& d);


	friend std::istream& operator>>(std::istream& in, Date& d);


private:
	int day, month, year;
	int hour, minute;
};



class Event
{
public:
	Event(std::string title = "", std::string description = "", std::string link = "", int numberOfPeople = 0, Date d = 0);
	~Event();

	//Event operator+(Event e);

	//set number of people
	void setNumberOfPeople(int newValue);

	//get number of poeple
	int getNumberOfPeople();

	//set title
	void setTitle(std::string newValue);

	//get the title
	std::string getTitle();

	//set description
	void setDescription(std::string newValue);

	//get the description
	std::string getDescription();

	//set link
	void setLink(std::string newValue);

	//get the link
	std::string getLink();

	//set date
	void setDate(Date newValue);

	//get the date
	Date getDate();

	friend std::ostream& operator<<(std::ostream& stream, const Event& e);


	friend std::istream& operator>>(std::istream& stream, Event& e);

private:
	int numberOfPeople;
	std::string title, description, link;
	Date date;
};


inline std::ostream& operator<<(std::ostream& stream, const Date& d)
{
	stream << d.day << " " << d.month << " " << d.year << " " << d.hour << " " << d.minute;
	return stream;
}

inline std::istream& operator>>(std::istream& in, Date& d)
{
	int day, month, year, hour, minute;

	in >> day;
	d.setDay(day);

	in >> month;
	d.setMonth(month);

	in >> year;
	d.setYear(year);

	in >> hour;
	d.setHour(hour);

	in >> minute;
	d.setMinute(minute);


	//in.ignore(1024, '\n');
	return in;
}

inline std::ostream& operator<<(std::ostream& stream, const Event& e)
{

	stream << e.title << " " << e.description << " " << e.link << " " << e.date << " " << e.numberOfPeople << "\n";
	//stream << e.title << " " << e.description << " " << e.link << " " << e.numberOfPeople << "\n";
	return stream;
}

inline std::istream& operator>>(std::istream& in, Event& e)
{
	std::string title, description, link;
	int numberOfPeople;
	Date d;

	in >> title;
	e.setTitle(title);

	in >> description;
	e.setDescription(description);

	in >> link;
	e.setLink(link);

	in >> d;
	e.setDate(d);

	in >> numberOfPeople;
	e.setNumberOfPeople(numberOfPeople);
	//in.ignore(1024, '\n');
	return in;

}


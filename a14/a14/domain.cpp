#include "domain.h"

Date::Date(int day, int month, int year, int hour, int minute)
{
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->minute = minute;
}

Date::~Date()
{
	return;
}

void Date::setDay(int newValue)
{
	this->day = newValue;
}

int Date::getDay()
{
	return this->day;
}

void Date::setMonth(int newValue)
{
	this->month = newValue;
}

int Date::getMonth()
{
	return this->month;
}

void Date::setYear(int newValue)
{
	this->year = newValue;
}

int Date::getYear()
{
	return this->year;
}

void Date::setHour(int newValue)
{
	this->hour = newValue;
}

int Date::getHour()
{
	return this->hour;
}

void Date::setMinute(int newValue)
{
	this->minute = newValue;
}

int Date::getMinute()
{
	return this->minute;
}

bool Date::SameDate(Date compare)
{
	if (this->day == compare.day && this->month == compare.month && this->year == compare.year && this->hour == compare.hour && this->minute == compare.minute)
		return true;

	return false;
}


Event::Event(std::string title, std::string description, std::string link, int numberOfPeople, Date d)
{
	this->title = title;
	this->link = link;
	this->numberOfPeople = numberOfPeople;
	this->description = description;
	this->date = d;
}

Event::~Event()
{
	return;
}

//Event Event::operator+(Event e)
//{
//	Event* arr;
//	return Event();
//}

void Event::setNumberOfPeople(int newValue)
{
	this->numberOfPeople = newValue;
}

int Event::getNumberOfPeople()
{
	return this->numberOfPeople;
}

void Event::setTitle(std::string newValue)
{
	this->title = newValue;
}

std::string Event::getTitle()
{
	return this->title;
}

void Event::setDescription(std::string newValue)
{
	this->description = newValue;
}

std::string Event::getDescription()
{
	return this->description;
}

void Event::setLink(std::string newValue)
{
	this->link = newValue;
}

std::string Event::getLink()
{
	return this->link;
}

void Event::setDate(Date newValue)
{
	this->date = newValue;
}

Date Event::getDate()
{
	return this->date;
}


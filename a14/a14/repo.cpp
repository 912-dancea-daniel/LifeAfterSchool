#include "repo.h"
#include <exception>
#include <algorithm>
#include "myexc.h"

//using namespace std;

EventVector::EventVector(int capacity)
{
	this->arr = std::vector<Event>();
}

EventVector::~EventVector()
{
	return;
}

EventVector::EventVector(const EventVector& e)
{
	this->arr = e.arr;
}

void EventVector::addEvent(Event newEvent)
{
	Validator v{};
	
	if (!v.checkDay(newEvent.getDate().getDay()) || !v.checkMonth(newEvent.getDate().getMonth()) || !v.checkYear(newEvent.getDate().getYear()) || !v.checkMinute(newEvent.getDate().getMinute()) || !v.checkHour(newEvent.getDate().getHour()))
		throw Exception("Invalid date input\n");

	if(!v.checkNrOfPeople(newEvent.getNumberOfPeople()))
		throw Exception("Invalid number of people\n");

	if (this->arr.size() > this->arr.capacity())
	{
		this->arr.resize(this->arr.capacity() * 2);
	}

	for (auto i : this->arr)
	{
		if (i.getTitle() == newEvent.getTitle() && i.getDate().SameDate(newEvent.getDate()))
			throw Exception("Won't add because event already in the schedule\n");
	}

	this->arr.push_back(newEvent);

	//this->writeToFile("out.txt");


}

void EventVector::deleteEvent(std::string title, Date date)
{
	Validator v{};

	if (!v.checkDay(date.getDay()) || !v.checkMonth(date.getMonth()) || !v.checkYear(date.getYear()) || !v.checkMinute(date.getMinute()) || !v.checkHour(date.getHour()))
		throw Exception("Invalid date input\n");

	int counter = 0;
	for (auto i : this->arr)
	{
		if (i.getTitle() == title && i.getDate().SameDate(date))
		{
			this->arr.erase(this->arr.begin() + counter);
			return;
		}
		counter++;

	}
	throw Exception("Couldn't find the event\n");
}

Event EventVector::getEvent(int index)
{
	if (index > this->arr.size())
		throw Exception("Wrong index");

	return this->arr[index];
}

int EventVector::getEventLen()
{
	return this->arr.size();
}

void EventVector::updateEventTitle(std::string title, Date d, std::string newTitle)
{
	Validator v{};

	if (!v.checkDay(d.getDay()) || !v.checkMonth(d.getMonth()) || !v.checkYear(d.getYear()) || !v.checkMinute(d.getMinute()) || !v.checkHour(d.getHour()))
		throw Exception("Invalid date input\n");

	for (auto& i : this->arr)
	{
		if (i.getTitle() == title && i.getDate().SameDate(d))
		{
			i.setTitle(newTitle);
			return;
		}

	}

	throw Exception("Couldn't find the event");
}

void EventVector::updateEventDesc(std::string title, Date d, std::string newDesc)
{
	Validator v{};

	if (!v.checkDay(d.getDay()) || !v.checkMonth(d.getMonth()) || !v.checkYear(d.getYear()) || !v.checkMinute(d.getMinute()) || !v.checkHour(d.getHour()))
		throw Exception("Invalid date input\n");

	for (auto& i : this->arr)
	{
		if (i.getTitle() == title && i.getDate().SameDate(d))
		{
			i.setDescription(newDesc);
			return;
		}

	}

	throw Exception("Couldn't find the event");
}

void EventVector::updateEventLink(std::string title, Date d, std::string newLink)
{
	Validator v{};

	if (!v.checkDay(d.getDay()) || !v.checkMonth(d.getMonth()) || !v.checkYear(d.getYear()) || !v.checkMinute(d.getMinute()) || !v.checkHour(d.getHour()))
		throw Exception("Invalid date input\n");

	for (auto& i : this->arr)
	{
		if (i.getTitle() == title && i.getDate().SameDate(d))
		{
			i.setLink(newLink);
			return;
		}

	}

	throw Exception("Couldn't find the event");
}

void EventVector::updateEventNrOfPeople(std::string title, Date d, int newNrOfPeople)
{
	Validator v{};

	if (!v.checkDay(d.getDay()) || !v.checkMonth(d.getMonth()) || !v.checkYear(d.getYear()) || !v.checkMinute(d.getMinute()) || !v.checkHour(d.getHour()))
		throw Exception("Invalid date input\n");

	if (!v.checkNrOfPeople(newNrOfPeople))
		throw Exception("Invalid number of people\n");

	for (auto& i : this->arr)
	{
		if (i.getTitle() == title && i.getDate().SameDate(d))
		{
			i.setNumberOfPeople(newNrOfPeople);
			return;
		}

	}

	throw Exception("Couldn't find the event");
}

void EventVector::updateEventDate(std::string title, Date d, Date newDate)
{
	Validator v{};

	if (!v.checkDay(d.getDay()) || !v.checkMonth(d.getMonth()) || !v.checkYear(d.getYear()) || !v.checkMinute(d.getMinute()) || !v.checkHour(d.getHour()))
		throw Exception("Invalid date input\n");

	if (!v.checkDay(newDate.getDay()) || !v.checkMonth(newDate.getMonth()) || !v.checkYear(newDate.getYear()) || !v.checkMinute(newDate.getMinute()) || !v.checkHour(newDate.getHour()))
		throw Exception("Invalid date input\n");


	for (auto& i : this->arr)
	{
		if (i.getTitle() == title && i.getDate().SameDate(d))
		{
			i.setDate(newDate);
			return;
		}

	}

	throw Exception("Couldn't find the event");
}

void EventVector::loadRepo()
{
	Date d = Date{ 11,1,2022, 12,10 };
	Event tmp = Event{ "NewEvent", "desc", "https://weather.com/?Goto=Redirected", 4, d };
	this->addEvent(tmp);


	d = Date{ 9,1,2022, 12,10 };
	tmp = Event{ "Match", "today", "https://en.as.com/en/2022/03/20/soccer/1647799035_947636.html", 10, d };
	this->addEvent(tmp);


	d = Date{ 1,1,2022, 12,10 };
	tmp = Event{ "Tennis", "yesterday", "https://www.tennis.com/", 14, d };
	this->addEvent(tmp);


	d = Date{ 4,4,2022, 12,10 };
	tmp = Event{ "Basketball", "home", "https://www.livesport.com/en/basketball/", 22, d };
	this->addEvent(tmp);


	d = Date{ 5,5,2022, 12,10 };
	tmp = Event{ "Party", "ok", "https://allevents.in/cluj-napoca/parties", 11, d };
	this->addEvent(tmp);


	d = Date{ 6,6,2022, 12,10 };
	tmp = Event{ "Opera", "cult", "https://www.opera.hu/", 41, d };
	this->addEvent(tmp);


	d = Date{ 7,7,2022, 12,10 };
	tmp = Event{ "Bowling", "fun", "https://cluj.info/pages/centru-de-distractii/", 66, d };
	this->addEvent(tmp);


	d = Date{ 8,8,2022, 12,10 };
	tmp = Event{ "Football", "interesting", "https://www.skysports.com/football", 4, d };
	this->addEvent(tmp);


	d = Date{ 9,9,2022, 12,10 };
	tmp = Event{ "Movie", "best", "https://www.imdb.com/", 44, d };
	this->addEvent(tmp);


	d = Date{ 10,10,2022, 12,10 };
	tmp = Event{ "Pub", "okay", "https://irishmusicpub.ro/", 22, d };
	this->addEvent(tmp);
}

void EventVector::sortEvents()
{
	sort(this->arr.begin(), this->arr.end(), sortFunc);
}

bool EventVector::dateCmp(Date d1, Date d2)
{
	if (d1.getYear() < d2.getYear())
	{
		return true;
	}

	if (d1.getYear() > d2.getYear())
	{
		return false;
	}

	if (d1.getMonth() < d2.getMonth())
	{
		return true;
	}

	if (d1.getMonth() > d2.getMonth())
	{
		return false;
	}

	if (d1.getDay() < d2.getDay())
	{
		return true;
	}

	if (d1.getDay() > d2.getDay())
	{
		return false;
	}

	if (d1.getHour() < d2.getHour())
	{
		return true;
	}

	if (d1.getHour() > d2.getHour())
	{
		return false;
	}

	if (d1.getMinute() < d2.getMinute())
	{
		return true;
	}

	if (d1.getMinute() > d2.getMinute())
	{
		return false;
	}

	return false;
}

void EventVector::writeToFile(std::string fileName)
{
	std::ofstream f(fileName);
	for (auto i : this->arr)
	{
		f << i;
	}
}

void EventVector::setRepoToFile(std::string fileName)
{
	std::ifstream f(fileName);
	Event e;
	std::vector<Event> v = std::vector<Event>{};

	while (f >> e)
	{
		v.push_back(e);
	}

	this->arr = v;

}

bool EventVector::sortFunc(Event e1, Event e2)
{
	Date d1, d2;
	d1 = e1.getDate();
	d2 = e2.getDate();

	if (d1.getYear() < d2.getYear())
	{
		return true;
	}

	if (d1.getYear() > d2.getYear())
	{
		return false;
	}

	if (d1.getMonth() < d2.getMonth())
	{
		return true;
	}

	if (d1.getMonth() > d2.getMonth())
	{
		return false;
	}

	if (d1.getDay() < d2.getDay())
	{
		return true;
	}

	if (d1.getDay() > d2.getDay())
	{
		return false;
	}

	if (d1.getHour() < d2.getHour())
	{
		return true;
	}

	if (d1.getHour() > d2.getHour())
	{
		return false;
	}

	if (d1.getMinute() < d2.getMinute())
	{
		return true;
	}

	if (d1.getMinute() > d2.getMinute())
	{
		return false;
	}

	return false;
}

